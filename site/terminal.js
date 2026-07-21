// A small DOS-style console: a fixed grid of cells plus scrollback.
//
// A plain append-only log would not work here. These programs clear the
// screen and redraw in place (system("cls"), cursor moves), so the terminal
// has to model an actual screen the way cmd.exe did.
import { CP437 } from "./cp437.js";

const DEFAULT_COLS = 80;
const DEFAULT_ROWS = 25;
const MAX_SCROLLBACK = 3000;

const DEFAULT_ATTR = 0x07; // light grey on black, the DOS default
const LINE_HEIGHT = 1.32; // keep in step with .screen in style.css

export class Terminal {
  constructor(el) {
    this.el = el;
    this.screen = el.querySelector(".screen");
    this.onInput = null;
    this.onTitle = null;
    this.onBell = null;

    this.el.tabIndex = 0;
    this.el.addEventListener("keydown", (e) => this.handleKey(e));
    this.el.addEventListener("paste", (e) => this.handlePaste(e));

    this.reset();
  }

  reset() {
    this.cols = DEFAULT_COLS;
    this.rows = DEFAULT_ROWS;
    this.attr = DEFAULT_ATTR;
    this.cx = 0;
    this.cy = 0;
    this.scrollback = [];
    this.buf = Array.from({ length: this.rows }, () => this.blankRow());
    this.esc = null;
    this.inputMode = null;
    this.pending = "";
    this.dirty = true;
    this.fit();
    this.render();
  }

  blankRow(cols = this.cols) {
    return { ch: new Array(cols).fill(" "), at: new Uint8Array(cols).fill(this.attr) };
  }

  resize(cols, rows) {
    if (cols) this.cols = Math.max(20, Math.min(200, cols));
    if (rows) this.rows = Math.max(5, Math.min(60, rows));
    this.buf = Array.from({ length: this.rows }, () => this.blankRow());
    this.cx = this.cy = 0;
    this.dirty = true;
    this.fit();
  }

  /*
   * Scales the type so one full screen fits the pane, the way resizing a
   * console window would. Without this a program that asks for 90x50 spills
   * past the bottom and its board scrolls out of sight.
   */
  fit() {
    const box = this.el.getBoundingClientRect();
    if (!box.width) return;

    // Measure this font's character cell once.
    if (!Terminal.ratio) {
      const probe = document.createElement("span");
      probe.style.cssText = "position:absolute;visibility:hidden;font:100px/1.32 var(--mono);white-space:pre";
      probe.textContent = "M".repeat(50);
      document.body.append(probe);
      Terminal.ratio = probe.getBoundingClientRect().width / 50 / 100;
      probe.remove();
    }

    const padding = 24;
    const byWidth = (box.width - padding) / (this.cols * Terminal.ratio);
    const byHeight = (box.height - padding) / (this.rows * LINE_HEIGHT);
    const size = Math.max(6, Math.min(14, Math.floor(Math.min(byWidth, byHeight) * 10) / 10));
    this.screen.style.fontSize = `${size}px`;
  }

  // --- byte stream -----------------------------------------------------

  write(bytes) {
    for (const b of bytes) this.byte(b);
    this.dirty = true;
  }

  byte(b) {
    if (this.esc !== null) return this.escByte(b);

    switch (b) {
      case 0x1b: this.esc = ""; return;
      case 0x07: this.onBell?.(); return;
      case 0x0a: this.newline(); return;
      case 0x0d: this.cx = 0; return;
      case 0x08: this.cx = Math.max(0, this.cx - 1); return;
      case 0x09: this.cx = Math.min(this.cols - 1, (this.cx + 8) & ~7); return;
      default: this.put(CP437[b] ?? " ");
    }
  }

  put(ch) {
    if (this.cx >= this.cols) this.newline();
    const row = this.buf[this.cy];
    row.ch[this.cx] = ch;
    row.at[this.cx] = this.attr;
    this.cx++;
  }

  newline() {
    this.cx = 0;
    if (++this.cy >= this.rows) {
      this.scrollback.push(this.buf.shift());
      if (this.scrollback.length > MAX_SCROLLBACK) this.scrollback.shift();
      this.buf.push(this.blankRow());
      this.cy = this.rows - 1;
    }
  }

  // Collects the escape body, then dispatches on the final byte.
  escByte(b) {
    const c = String.fromCharCode(b);

    if (this.esc === "") {
      if (c === "[" || c === "]") {
        this.esc = c;
        return;
      }
      // 27 is also CP437's ← , which programs 64 and 65 print as a key hint.
      // Every sequence the shim emits continues with [ or ], so anything else
      // means this was a literal arrow.
      this.esc = null;
      this.put(CP437[27]);
      return this.byte(b);
    }
    if (this.esc.startsWith("]")) {
      // OSC runs until BEL
      if (b === 0x07) {
        this.osc(this.esc.slice(1));
        this.esc = null;
      } else {
        this.esc += c;
      }
      return;
    }
    if (this.esc.startsWith("[")) {
      if (b >= 0x40 && b <= 0x7e) {
        this.csi(this.esc.slice(1), c);
        this.esc = null;
      } else {
        this.esc += c;
      }
      return;
    }
    this.esc = null;
  }

  csi(params, final) {
    const n = params.split(";").map((p) => (p === "" ? 0 : parseInt(p, 10)));

    switch (final) {
      case "H": case "f": {
        this.cy = Math.min(this.rows - 1, Math.max(0, (n[0] || 1) - 1));
        this.cx = Math.min(this.cols - 1, Math.max(0, (n[1] || 1) - 1));
        break;
      }
      case "J": {
        // 2 clears the whole screen; the programs only ever use that one.
        if ((n[0] || 0) === 2) {
          this.buf = Array.from({ length: this.rows }, () => this.blankRow());
          this.cx = this.cy = 0;
        }
        break;
      }
      case "K": {
        const row = this.buf[this.cy];
        for (let x = this.cx; x < this.cols; x++) {
          row.ch[x] = " ";
          row.at[x] = this.attr;
        }
        break;
      }
      case "m": this.sgr(n); break;
      case "A": this.cy = Math.max(0, this.cy - (n[0] || 1)); break;
      case "B": this.cy = Math.min(this.rows - 1, this.cy + (n[0] || 1)); break;
      case "C": this.cx = Math.min(this.cols - 1, this.cx + (n[0] || 1)); break;
      case "D": this.cx = Math.max(0, this.cx - (n[0] || 1)); break;
    }
  }

  sgr(codes) {
    for (const c of codes) {
      if (c === 0) this.attr = DEFAULT_ATTR;
      else if (c === 1) this.attr |= 0x08;
      else if (c >= 30 && c <= 37) this.attr = (this.attr & 0xf8) | (c - 30);
      else if (c >= 90 && c <= 97) this.attr = (this.attr & 0xf0) | (c - 90) | 0x08;
      else if (c >= 40 && c <= 47) this.attr = (this.attr & 0x8f) | ((c - 40) << 4);
      else if (c >= 100 && c <= 107) this.attr = (this.attr & 0x0f) | ((c - 100) << 4) | 0x80;
    }
  }

  osc(body) {
    // 0;title  — set window title
    // 77;cols;lines — our own code for system("mode con ...")
    const [kind, ...rest] = body.split(";");
    if (kind === "0") this.onTitle?.(rest.join(";"));
    else if (kind === "77") this.resize(parseInt(rest[0], 10), parseInt(rest[1], 10));
  }

  // --- input -----------------------------------------------------------

  /** A trailing ESC with nothing after it was a literal ← after all. */
  settleEscape() {
    if (this.esc === "") {
      this.esc = null;
      this.put(CP437[27]);
      this.dirty = true;
    }
  }

  /** 'line' waits for Enter and echoes; 'raw' sends the next key immediately. */
  setInputMode(mode) {
    this.inputMode = mode;
    this.pending = "";
    this.dirty = true;
    this.render();
    if (mode) this.el.focus();
  }

  handleKey(e) {
    if (!this.inputMode) return;

    // Raw mode streams every keystroke to the running program (getch/kbhit),
    // which is how the interactive games are driven.
    if (this.inputMode === "raw") {
      if (e.metaKey) return; // leave Cmd-based copy/paste alone
      const bytes = rawKeyBytes(e);
      if (!bytes) return;
      e.preventDefault();
      this.onKey?.(bytes);
      return;
    }

    if (e.metaKey || e.ctrlKey || e.altKey) return; // leave copy/paste alone
    const key = e.key;
    e.preventDefault();

    if (key === "Enter") {
      const line = this.pending;
      this.pending = "";
      this.write(new Uint8Array([10]));
      this.submit(new TextEncoder().encode(line + "\n"));
    } else if (key === "Backspace") {
      if (this.pending) {
        this.pending = this.pending.slice(0, -1);
        this.write(new Uint8Array([8, 32, 8]));
      }
    } else if (key.length === 1) {
      this.pending += key;
      this.write(new Uint8Array([key.charCodeAt(0)]));
    }
    this.render();
  }

  handlePaste(e) {
    if (this.inputMode !== "line") return;
    e.preventDefault();
    const text = (e.clipboardData?.getData("text") ?? "").replace(/\r/g, "");
    const nl = text.indexOf("\n");
    const first = nl === -1 ? text : text.slice(0, nl);
    for (const ch of first) {
      this.pending += ch;
      this.write(new Uint8Array([ch.charCodeAt(0) & 0xff]));
    }
    this.render();
  }

  submit(bytes) {
    const fn = this.onInput;
    this.inputMode = null;
    this.render();
    fn?.(bytes);
  }

  // --- rendering -------------------------------------------------------

  render() {
    if (!this.dirty && !this.pendingRender) return;
    this.dirty = false;

    const rows = [...this.scrollback, ...this.buf];
    const cursorRow = this.scrollback.length + this.cy;
    let html = "";

    for (let y = 0; y < rows.length; y++) {
      const { ch, at } = rows[y];
      // Trailing blanks never need markup.
      let end = ch.length;
      while (end > 0 && ch[end - 1] === " " && at[end - 1] === DEFAULT_ATTR) end--;

      // Only line input shows a caret; raw-mode games position their own.
      const showCursor = this.inputMode === "line" && y === cursorRow;
      if (showCursor) end = Math.max(end, this.cx + 1);

      let line = "";
      let x = 0;
      while (x < end) {
        const a = at[x];
        let run = "";
        const start = x;
        while (x < end && at[x] === a && !(showCursor && x === this.cx)) {
          run += ch[x];
          x++;
        }
        if (run) line += `<span class="c${a >> 4}-${a & 15}">${esc(run)}</span>`;
        if (showCursor && x === this.cx && x < end) {
          line += `<span class="c${a >> 4}-${a & 15} caret">${esc(ch[x])}</span>`;
          x++;
        }
        if (x === start) x++; // never stall
      }
      html += line + "\n";
    }

    this.screen.innerHTML = html;
    this.screen.style.width = `${this.cols}ch`;
    // A program that redraws a whole screen has no scrollback; anchoring to
    // the top keeps its board in view. Anything else is a stream of output,
    // where the newest line is what matters.
    this.el.scrollTop = this.scrollback.length ? this.el.scrollHeight : 0;
  }
}

function esc(s) {
  return s.replace(/[&<>]/g, (c) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;" })[c]);
}

// Windows' conio delivered an arrow key as two reads: a 0xE0 lead byte then a
// scan code. Programs like Snake test the lead byte and then switch on the
// scan code, so the same pair is sent here. Ctrl+letter becomes a control code
// (Ctrl+A = 1) the way a console would, which Snake uses for faster/slower.
const ARROWS = {
  ArrowUp: [0xe0, 72],
  ArrowDown: [0xe0, 80],
  ArrowLeft: [0xe0, 75],
  ArrowRight: [0xe0, 77],
};

function rawKeyBytes(e) {
  if (ARROWS[e.key]) return ARROWS[e.key];
  switch (e.key) {
    case "Enter": return [13];
    case "Escape": return [27];
    case "Backspace": return [8];
    case "Tab": return [9];
  }
  if (e.key.length === 1) {
    if (e.ctrlKey) {
      const u = e.key.toUpperCase();
      if (u >= "A" && u <= "Z") return [u.charCodeAt(0) - 64];
      return null;
    }
    return [e.key.charCodeAt(0) & 0xff];
  }
  return null;
}
