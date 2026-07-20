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

let programs = [];
let current = null;
let worker = null;
let sab = null;
let ctl = null;
let inbox = null;
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
          num.textContent = p.num > 75 ? "★" : p.num;

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
  term.reset();
  els.termTitle.textContent = current.title;
  setStatus("running…", "running");
  els.run.disabled = true;
  els.stop.disabled = false;

  // 4 control ints + room for a generous pasted line.
  sab = new SharedArrayBuffer(16 + 4096);
  ctl = new Int32Array(sab, 0, 4);
  inbox = new Uint8Array(sab, 16);

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

function onWorker(msg) {
  if (msg.type === "out") {
    term.write(msg.bytes);
    term.render();
    return;
  }

  if (msg.type === "need-input") {
    term.settleEscape();
    term.setInputMode(msg.mode);
    setHint(
      msg.mode === "raw"
        ? `Waiting for a <b>single key</b> — click the console and press any key.`
        : `Waiting for input — type a value and press <span class="key">Enter</span>.`
    );
    term.onInput = (bytes) => {
      const n = Math.min(bytes.length, inbox.length);
      inbox.set(bytes.subarray(0, n));
      Atomics.store(ctl, 1, n);
      Atomics.store(ctl, 0, 1);
      Atomics.notify(ctl, 0);
      setHint("Running…");
    };
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
