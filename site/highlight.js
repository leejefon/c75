// Minimal C highlighter — enough for 2008-era coursework, no dependencies.
const KEYWORDS = new Set(
  `auto break case char const continue default do double else enum extern float
   for goto if inline int long register return short signed sizeof static struct
   switch typedef union unsigned void volatile while bool true false NULL`.split(/\s+/)
);

// Ordered: whatever matches first at a position wins.
const RULES = [
  ["comment", /\/\*[\s\S]*?\*\/|\/\/[^\n]*/y],
  ["pre", /#[ \t]*\w+/y],
  ["str", /"(?:\\.|[^"\\\n])*"?/y],
  ["chr", /'(?:\\.|[^'\\\n])*'?/y],
  ["num", /\b(?:0[xX][0-9a-fA-F]+|\d+\.?\d*(?:[eE][-+]?\d+)?)[uUlLfF]*\b/y],
  ["word", /[A-Za-z_]\w*/y],
  ["punct", /[{}()[\];,.]|[-+*/%=<>!&|^~?:]+/y],
];

const ESC = { "&": "&amp;", "<": "&lt;", ">": "&gt;" };
const escape = (s) => s.replace(/[&<>]/g, (c) => ESC[c]);

export function highlightC(code) {
  let out = "";
  let i = 0;

  while (i < code.length) {
    // Whitespace passes through untouched so indentation is preserved.
    const ws = /\s+/y;
    ws.lastIndex = i;
    const m = ws.exec(code);
    if (m) {
      out += escape(m[0]);
      i = ws.lastIndex;
      continue;
    }

    let matched = false;
    for (const [kind, re] of RULES) {
      re.lastIndex = i;
      const hit = re.exec(code);
      if (!hit) continue;

      const text = hit[0];
      let cls = kind;
      if (kind === "word") {
        // A word followed by "(" reads as a call; otherwise it is an identifier.
        cls = KEYWORDS.has(text) ? "kw" : /^\s*\(/.test(code.slice(re.lastIndex)) ? "fn" : null;
      }
      out += cls ? `<span class="t-${cls}">${escape(text)}</span>` : escape(text);
      i = re.lastIndex;
      matched = true;
      break;
    }
    if (!matched) {
      out += escape(code[i]);
      i++;
    }
  }
  return out;
}
