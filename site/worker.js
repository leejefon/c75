// Runs one compiled program. Lives on a worker thread so that scanf() and
// getch() can block the way they do in a real console: the C code calls into
// JS, and JS parks on Atomics.wait until the page hands over a keystroke.
// Doing this on the main thread would deadlock the UI that collects the input.

// SharedArrayBuffer layout: 4 control ints, then the input bytes.
const SIGNAL = 0;   // 0 = waiting, 1 = input ready
const LENGTH = 1;   // bytes written
const PARK = 2;     // never notified; used only for timed sleeps
const HEADER = 16;

let ctl, data;
let out = [];
let lastFlush = 0;

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

/** Blocks until the page sends input. mode: 'line' echoes, 'raw' is one key. */
function request(mode) {
  flush();
  Atomics.store(ctl, SIGNAL, 0);
  postMessage({ type: "need-input", mode });
  Atomics.wait(ctl, SIGNAL, 0);
  const n = Atomics.load(ctl, LENGTH);
  return data.slice(0, n);
}

// stdin is read a byte at a time, so a whole line is fetched per request.
//
// The read() that drives this keeps calling until the byte buffer is full or
// it gets a null, so returning null once the line runs out is what ends the
// read. Without it the program would sit waiting for a second line.
let queue = [];
let endOfLine = false;

function stdin() {
  if (queue.length) return queue.shift();
  if (endOfLine) {
    endOfLine = false;
    return null;
  }
  const bytes = request("line");
  if (!bytes.length) return null; // EOF
  queue = Array.from(bytes);
  endOfLine = true;
  return queue.shift();
}

// conio's getch() reads the console directly rather than stdin, so it
// deliberately ignores anything still sitting in the line buffer.
globalThis.C75 = {
  getch() {
    const b = request("raw");
    return b.length ? b[0] : 0;
  },
  kbhit() {
    return 0;
  },
  sleep(ms) {
    flush();
    Atomics.wait(ctl, PARK, 0, ms);
  },
};

onmessage = async (e) => {
  const { id, sab } = e.data;
  ctl = new Int32Array(sab, 0, 4);
  data = new Uint8Array(sab, HEADER);

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
