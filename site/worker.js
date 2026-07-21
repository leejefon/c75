// Runs one compiled program. Lives on a worker thread so its blocking calls —
// scanf(), getch(), sleep(), Beep() — can actually block on Atomics.wait
// without freezing the UI that feeds them.
//
// Input comes in two shapes, because the C programs use two different console
// facilities:
//
//   line  — stdin (scanf/gets). The page shows an editable, echoed line and
//           delivers it whole on Enter. The worker blocks on LINE_SIGNAL.
//   raw   — conio (getch/kbhit). The page streams every keystroke into a ring
//           buffer as it happens, so kbhit() can poll without blocking and a
//           real-time game (Snake) stays playable. getch() pops the ring,
//           blocking on the KB_WRITE counter only when it is empty.
//
// SharedArrayBuffer layout:
//   Int32[0] LINE_SIGNAL   0 = worker waiting, 1 = line ready
//   Int32[1] LINE_LEN      bytes in the line buffer
//   Int32[2] PARK          never notified; target for timed waits (sleep/beep)
//   Int32[3] KB_WRITE      total keys the page has pushed (monotonic)
//   Int32[4] KB_READ       total keys the worker has taken (monotonic)
//   bytes[32 ..]           line buffer (LINE_CAP)
//   bytes[32+LINE_CAP ..]  key ring (KB_CAP)
const LINE_SIGNAL = 0;
const LINE_LEN = 1;
const PARK = 2;
const KB_WRITE = 3;
const KB_READ = 4;

const HEADER = 32;
const LINE_CAP = 4096;
const KB_CAP = 256;

let ctl, lineBuf, keyRing;
let out = [];
let lastFlush = 0;

// The page only captures keystrokes once told to. rawArmed tracks whether that
// message has been sent; it is cleared whenever line input takes the keyboard
// back, so the next getch/kbhit re-arms raw capture.
let rawArmed = false;

function flush() {
  if (out.length) {
    postMessage({ type: "out", bytes: new Uint8Array(out) });
    out = [];
  }
  lastFlush = Date.now();
}

function emit(code) {
  if (code === null) return flush();
  out.push(code);
  // Flush on size, and on time so a slow-printing loop still animates.
  if (out.length >= 4096 || Date.now() - lastFlush > 16) flush();
}

function armRaw() {
  if (!rawArmed) {
    flush();
    postMessage({ type: "raw-arm" });
    rawArmed = true;
  }
}

// --- line input (stdin) ------------------------------------------------

function requestLine() {
  flush();
  rawArmed = false; // the page leaves raw capture to edit the line
  Atomics.store(ctl, LINE_SIGNAL, 0);
  postMessage({ type: "need-input", mode: "line" });
  Atomics.wait(ctl, LINE_SIGNAL, 0);
  return lineBuf.slice(0, Atomics.load(ctl, LINE_LEN));
}

// stdin is read a byte at a time, so a whole line is fetched per request. The
// read() driving this keeps calling until its buffer fills or it gets a null,
// so returning null at end-of-line is what ends the read.
let queue = [];
let endOfLine = false;

function stdin() {
  if (queue.length) return queue.shift();
  if (endOfLine) {
    endOfLine = false;
    return null;
  }
  const bytes = requestLine();
  if (!bytes.length) return null; // EOF
  queue = Array.from(bytes);
  endOfLine = true;
  return queue.shift();
}

// --- raw input (conio) -------------------------------------------------

function ringHasKey() {
  return Atomics.load(ctl, KB_WRITE) !== Atomics.load(ctl, KB_READ);
}

function ringPop() {
  const r = Atomics.load(ctl, KB_READ);
  const b = keyRing[r % KB_CAP];
  Atomics.store(ctl, KB_READ, r + 1);
  return b;
}

globalThis.C75 = {
  // getch() reads the console directly, ignoring the line buffer. It blocks
  // until a key is available, then returns it.
  getch() {
    armRaw();
    while (!ringHasKey()) {
      flush();
      Atomics.wait(ctl, KB_WRITE, Atomics.load(ctl, KB_READ));
    }
    return ringPop();
  },
  kbhit() {
    armRaw();
    return ringHasKey() ? 1 : 0;
  },
  sleep(ms) {
    flush();
    Atomics.wait(ctl, PARK, 0, ms);
  },
  beep(freq, dur) {
    flush();
    if (freq > 0) postMessage({ type: "beep", freq, dur });
    // Blocks for the note's duration exactly as Win32 Beep() does.
    if (dur > 0) Atomics.wait(ctl, PARK, 0, dur);
  },
};

onmessage = async (e) => {
  const { id, sab } = e.data;
  ctl = new Int32Array(sab, 0, 8);
  lineBuf = new Uint8Array(sab, HEADER, LINE_CAP);
  keyRing = new Uint8Array(sab, HEADER + LINE_CAP, KB_CAP);

  importScripts(`./wasm/${encodeURIComponent(id)}.js`);

  const cfg = {
    noInitialRun: true,
    // importScripts does not move the worker's base URL, so the generated
    // loader would look for the .wasm next to worker.js instead.
    locateFile: (f) => `./wasm/${f}`,
    preRun: [() => cfg.FS.init(stdin, emit, emit)],
    printErr: () => {},
  };

  try {
    await createProgram(cfg);
    cfg.callMain([]);
    flush();
    postMessage({ type: "exit", code: 0 });
  } catch (err) {
    flush();
    // exit() unwinds by throwing; that is a normal finish, not a crash.
    const code = err && err.name === "ExitStatus" ? err.status : null;
    postMessage({
      type: "exit",
      code: code ?? 1,
      error: code === null ? String(err && err.message ? err.message : err) : null,
    });
  }
};
