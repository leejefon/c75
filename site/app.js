import { Terminal } from "./terminal.js";
import { highlightC } from "./highlight.js";

const $ = (sel) => document.querySelector(sel);

const els = {
  list: $("#list"),
  search: $("#search"),
  filters: $("#filters"),
  count: $("#count"),
  code: $("#code code"),
  codeScroll: $("#code-scroll"),
  title: $("#prog-title"),
  meta: $("#prog-meta"),
  termTitle: $("#term-title"),
  status: $("#status"),
  hint: $("#hint"),
  run: $("#run"),
  stop: $("#stop"),
  clear: $("#clear"),
};

// The 16 DOS console colours, indexed the way the terminal packs them.
const PALETTE = [
  "#000000", "#aa0000", "#00aa00", "#aa5500", "#0000aa", "#aa00aa", "#00aaaa", "#aaaaaa",
  "#555555", "#ff5555", "#55ff55", "#ffff55", "#5555ff", "#ff55ff", "#55ffff", "#ffffff",
];

// 256 fg/bg pairs is more than is worth hand-writing in the stylesheet.
{
  const rules = [];
  for (let bg = 0; bg < 16; bg++)
    for (let fg = 0; fg < 16; fg++) {
      const base = `.c${bg}-${fg}{color:${PALETTE[fg]}`;
      rules.push(bg === 0 ? `${base}}` : `${base};background:${PALETTE[bg]}}`);
    }
  const style = document.createElement("style");
  style.textContent = rules.join("");
  document.head.append(style);
}

const term = new Terminal($("#terminal"));

// Win32 Beep() rendered through Web Audio — a square wave, like the PC speaker
// it originally drove. The worker blocks for the real duration; this just has
// to sound for it. The AudioContext is created on the first Run (a user
// gesture), which browsers require before audio may play.
let audio = null;

function playTone(freq, ms) {
  if (!audio) return;
  const now = audio.currentTime;
  const osc = audio.createOscillator();
  const gain = audio.createGain();
  osc.type = "square";
  osc.frequency.value = freq;
  // A short fade at each end keeps the notes from clicking.
  const dur = ms / 1000;
  gain.gain.setValueAtTime(0, now);
  gain.gain.linearRampToValueAtTime(0.12, now + 0.008);
  gain.gain.setValueAtTime(0.12, now + Math.max(0.008, dur - 0.02));
  gain.gain.linearRampToValueAtTime(0, now + dur);
  osc.connect(gain).connect(audio.destination);
  osc.start(now);
  osc.stop(now + dur + 0.02);
}

let programs = [];
let current = null;
let worker = null;
let sab = null;
let ctl = null;
let lineBuf = null;
let keyRing = null;

// Matches the SharedArrayBuffer layout documented in worker.js.
const HEADER = 32;
const LINE_CAP = 4096;
const KB_CAP = 256;
const LINE_SIGNAL = 0, LINE_LEN = 1, KB_WRITE = 3;
let filter = "";

// --- program list ------------------------------------------------------

const BANGS = { Good: "!!!", Useful: "!!", Special: "!" };

function visible() {
  const q = els.search.value.trim().toLowerCase();
  return programs.filter((p) => {
    if (filter && p.tag !== filter) return false;
    if (!q) return true;
    return `${p.num} ${p.title} ${p.ref ?? ""}`.toLowerCase().includes(q);
  });
}

function renderList() {
  const items = visible();
  els.list.replaceChildren(
    ...(items.length
      ? items.map((p) => {
          const li = document.createElement("li");
          li.dataset.id = p.id;
          li.classList.toggle("on", current?.id === p.id);
          li.title = p.file;

          const num = document.createElement("span");
          num.className = "num";
          num.textContent = p.extra || p.num > 75 ? "★" : p.num;

          const name = document.createElement("span");
          name.className = "name";
          name.textContent = p.title;

          li.append(num, name);
          if (p.tag) {
            const bang = document.createElement("span");
            bang.className = "bang";
            bang.textContent = BANGS[p.tag];
            bang.title = p.tag;
            li.append(bang);
          }
          li.onclick = () => select(p);
          return li;
        })
      : [Object.assign(document.createElement("li"), {
          className: "empty",
          textContent: "No programs match.",
        })])
  );
  els.count.textContent = `${items.length} of ${programs.length}`;
}

function select(p) {
  stop();
  current = p;

  const lines = p.source.replace(/\s+$/, "").split("\n");
  els.code.innerHTML = lines
    .map((l, i) => `<span class="ln">${i + 1}</span>${highlightC(l)}`)
    .join("\n");
  els.codeScroll.scrollTop = 0;

  els.title.textContent = p.title;
  els.meta.textContent = [p.ref, p.interactive ? "interactive" : null]
    .filter(Boolean)
    .concat(p.patched ? ["compat-patched"] : [])
    .join(" · ");

  // The source on screen is always the original, so say so when the build
  // needed a tweak to get through a modern compiler.
  els.meta.title = p.patched
    ? "Built with a small compatibility patch; the source shown is unchanged."
    : "";
  els.meta.classList.toggle("patched", Boolean(p.patched));
  els.run.disabled = false;
  els.termTitle.textContent = "Output";
  setStatus("");
  term.reset();
  setHint(`Press <span class="key">Run</span> to build output for <b>${p.title}</b>.`);
  renderList();

  location.hash = p.id;
}

// --- running -----------------------------------------------------------

function setStatus(text, cls = "") {
  els.status.textContent = text;
  els.status.className = cls;
}

function setHint(html) {
  els.hint.innerHTML = html;
}

function run() {
  if (!current) return;
  stop();

  // Run is a user gesture, so this is the moment audio is allowed to start.
  if (!audio) audio = new (window.AudioContext || window.webkitAudioContext)();
  audio.resume?.();

  term.reset();
  els.termTitle.textContent = current.title;
  setStatus("running…", "running");
  els.run.disabled = true;
  els.stop.disabled = false;

  sab = new SharedArrayBuffer(HEADER + LINE_CAP + KB_CAP);
  ctl = new Int32Array(sab, 0, 8);
  lineBuf = new Uint8Array(sab, HEADER, LINE_CAP);
  keyRing = new Uint8Array(sab, HEADER + LINE_CAP, KB_CAP);

  worker = new Worker("./worker.js");
  worker.onmessage = (e) => onWorker(e.data);
  worker.onerror = (e) => {
    setStatus("failed", "failed");
    setHint(`<b>Error:</b> ${e.message}`);
    finish();
  };
  worker.postMessage({ id: current.id, sab });
  term.el.focus();
}

// A redraw-heavy program (Snake repaints every cell each frame) emits output
// far faster than the DOM can repaint. Rendering on every message would back
// the main thread up by seconds and starve keyboard input. Instead we absorb
// the bytes immediately and repaint at most once per animation frame.
let renderQueued = false;
function scheduleRender() {
  if (renderQueued) return;
  renderQueued = true;
  requestAnimationFrame(() => {
    renderQueued = false;
    term.render();
  });
}

function onWorker(msg) {
  if (msg.type === "out") {
    term.write(msg.bytes);
    scheduleRender();
    return;
  }

  // conio input: the program is reading keys directly. Stream each keystroke
  // into the shared ring buffer so getch()/kbhit() see it.
  if (msg.type === "raw-arm") {
    term.settleEscape();
    term.setInputMode("raw");
    setHint(`Interactive — click the console and use your keyboard.`);
    term.onKey = (bytes) => {
      let w = Atomics.load(ctl, KB_WRITE);
      for (const b of bytes) keyRing[w++ % KB_CAP] = b & 0xff;
      Atomics.store(ctl, KB_WRITE, w);
      Atomics.notify(ctl, KB_WRITE);
    };
    return;
  }

  // stdin input: the program is reading a line. Collect an editable line and
  // hand it over on Enter.
  if (msg.type === "need-input") {
    term.settleEscape();
    term.setInputMode("line");
    setHint(`Waiting for input — type a value and press <span class="key">Enter</span>.`);
    term.onInput = (bytes) => {
      const n = Math.min(bytes.length, LINE_CAP);
      lineBuf.set(bytes.subarray(0, n));
      Atomics.store(ctl, LINE_LEN, n);
      Atomics.store(ctl, LINE_SIGNAL, 1);
      Atomics.notify(ctl, LINE_SIGNAL);
      setHint("Running…");
    };
    return;
  }

  if (msg.type === "beep") {
    playTone(msg.freq, msg.dur);
    return;
  }

  if (msg.type === "exit") {
    term.settleEscape();
    term.render();
    if (msg.error) {
      setStatus("failed", "failed");
      setHint(`<b>Stopped:</b> ${msg.error}`);
    } else {
      setStatus(`finished (exit ${msg.code})`);
      setHint("Program finished.");
    }
    finish();
  }
}

function finish() {
  term.setInputMode(null);
  term.onKey = null;
  worker?.terminate();
  worker = null;
  els.run.disabled = !current;
  els.stop.disabled = true;
}

function stop() {
  if (!worker) return;
  worker.terminate();
  worker = null;
  term.setInputMode(null);
  term.onKey = null;
  setStatus("stopped");
  setHint("Stopped.");
  els.run.disabled = !current;
  els.stop.disabled = true;
}

// --- wiring ------------------------------------------------------------

els.run.onclick = run;
els.stop.onclick = stop;
els.clear.onclick = () => {
  term.reset();
  setHint("");
};
els.search.oninput = renderList;

els.filters.onclick = (e) => {
  const chip = e.target.closest(".chip");
  if (!chip) return;
  filter = chip.dataset.tag;
  els.filters.querySelectorAll(".chip").forEach((c) => c.classList.toggle("on", c === chip));
  renderList();
};

// Ctrl/Cmd+Enter runs from anywhere.
addEventListener("keydown", (e) => {
  if ((e.metaKey || e.ctrlKey) && e.key === "Enter" && !els.run.disabled) {
    e.preventDefault();
    run();
  }
});

addEventListener("resize", () => term.fit());

term.onTitle = (t) => {
  if (t) els.termTitle.textContent = t;
};
term.onBell = () => {
  term.el.animate([{ filter: "invert(1)" }, { filter: "none" }], 110);
};

// Drag the divider between the code and the console.
{
  const splitter = $("#splitter");
  const pane = $("#term-pane");
  splitter.onpointerdown = (e) => {
    splitter.setPointerCapture(e.pointerId);
    const move = (ev) => {
      const main = $("main").getBoundingClientRect();
      const h = Math.min(Math.max(main.bottom - ev.clientY, 120), main.height - 120);
      pane.style.height = `${h}px`;
      term.fit();
    };
    const up = () => {
      splitter.removeEventListener("pointermove", move);
      splitter.removeEventListener("pointerup", up);
    };
    splitter.addEventListener("pointermove", move);
    splitter.addEventListener("pointerup", up);
  };
}

// --- boot --------------------------------------------------------------

if (!crossOriginIsolated) {
  setHint(
    `<b>Not cross-origin isolated.</b> Blocking input needs SharedArrayBuffer — ` +
      `serve this folder with <code>node serve.mjs</code>.`
  );
}

programs = await fetch("programs.json").then((r) => r.json());
renderList();

const fromHash = programs.find((p) => p.id === location.hash.slice(1));
select(fromHash ?? programs[0]);
