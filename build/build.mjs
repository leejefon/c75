#!/usr/bin/env node
/*
 * Compiles every program in first75/ to WebAssembly and writes the manifest
 * the site reads. Run: node build/build.mjs  (see build.sh for the env setup)
 */
import { execFile } from "node:child_process";
import { promisify } from "node:util";
import fs from "node:fs/promises";
import path from "node:path";
import os from "node:os";

const exec = promisify(execFile);

const ROOT = path.resolve(import.meta.dirname, "..");
const SRC = path.join(ROOT, "first75");
const OUT = path.join(ROOT, "site", "wasm");
const BUILD = path.join(ROOT, "build");

// "! = Special.c" / "!! = Useful.c" / "!!! = Good.c" sit in the folder as a
// legend for the bangs in the filenames.
const TAGS = { "!": "Special", "!!": "Useful", "!!!": "Good" };

// The leading number and the bang tag are both optional: most files are
// "22 !! guess - SP-w4&5-7.c", but a bonus like "!!! Snake.c" carries the tag
// with no number.
/** "22 !! guess - SP-w4&5-7.c" -> { num, tag, title, ref } */
function parseName(file) {
  const stem = file.replace(/\.c$/i, "");
  const m = /^(?:(\d+)\s+)?(!{1,3})?\s*(.*)$/.exec(stem);

  let rest = m[3].trim();
  let ref = null;
  // Trailing " - SP-w3-2 (EXE-5.2.5)" is the coursework reference, not a title.
  const dash = rest.lastIndexOf(" - ");
  if (dash !== -1) {
    ref = rest.slice(dash + 3).trim();
    rest = rest.slice(0, dash).trim();
  }
  return {
    num: m[1] ? Number(m[1]) : null,
    tag: m[2] ? TAGS[m[2]] : null,
    title: rest,
    ref,
  };
}

function slugify(s) {
  return s
    .toLowerCase()
    .replace(/\.c$/i, "")
    .replace(/[^a-z0-9]+/g, "-")
    .replace(/^-|-$/g, "");
}

async function collect() {
  const items = [];

  for (const f of (await fs.readdir(SRC)).sort()) {
    // The three legend files ("! = Special.c" etc.) are empty and only
    // document the bang tags; skip those but keep bang-prefixed programs.
    if (!f.endsWith(".c") || /^!+ =/.test(f)) continue;
    items.push({ file: path.join(SRC, f), name: f, dir: SRC });
  }

  return items.map((it) => {
    const meta = parseName(it.name);
    return {
      ...it,
      ...meta,
      // Files share numbers (63 v1.0/v2.0/v3.0), so the slug carries the name.
      id: slugify(it.name),
      num: meta.num,
    };
  });
}

const NEEDS_INPUT = /\b(scanf|getchar|gets|fgets\s*\([^)]*stdin|getch|getche|kbhit)\s*\(/;

/*
 * Three programs lean on things the 2008 Dev-C++ toolchain allowed and clang
 * rejects outright. These are applied to a temporary copy at build time so
 * first75/ stays exactly as written; the site always shows the original.
 */
const PATCHES = {
  "65 virus 3 v1.5 - final project.c": [
    // Prototypes say char a[][]; the definitions below say [maxboard][maxboard].
    [/\[\]\[\]/g, "[][maxboard]"],
    // ctime()/time_t are used but time.h was never included.
    [/#include<windows.h>/, "#include<windows.h>\n#include<time.h>"],
  ],
  "73 card dealer - SP-w12-4.c": [
    // Without stdlib.h, srand() was implicitly int, making this an endless
    // deal loop. Keep that meaning now that the shim declares it void.
    [/while \(srand\(seed\)\)/, "while ((srand(seed), 1))"],
  ],
};

const FLAGS = [
  "-O2",
  // MinGW's char was signed. Programs that store a raw getch() in a char and
  // compare it to a negative sentinel (Snake tests the arrow-key lead byte
  // 0xE0 against -32) need the same, or the comparison never matches.
  "-fsigned-char",
  "-I", BUILD,
  "-I", path.join(BUILD, "include"),
  "-include", path.join(BUILD, "c75shim.h"),
  "--js-library", path.join(BUILD, "lib_c75.js"),
  "-sMODULARIZE=1",
  "-sEXPORT_NAME=createProgram",
  "-sENVIRONMENT=worker",
  "-sINVOKE_RUN=0",
  "-sEXIT_RUNTIME=1",
  "-sFORCE_FILESYSTEM=1",
  "-sALLOW_MEMORY_GROWTH=1",
  "-sSTACK_SIZE=5MB",
  "-sEXPORTED_RUNTIME_METHODS=callMain,FS",
  // These are 2008 K&R-flavoured sources; the warnings are noise, not news.
  "-Wno-implicit-function-declaration",
  "-Wno-implicit-int",
  "-Wno-return-type",
  "-Wno-format",
  "-Wno-parentheses",
  "-Wno-main-return-type",
  "-lm",
];

async function compile(prog, source) {
  const out = path.join(OUT, `${prog.id}.js`);

  let input = prog.file;
  const patches = PATCHES[prog.name];
  if (patches) {
    const patched = patches.reduce((s, [find, sub]) => s.replace(find, sub), source);
    input = path.join(TMP, prog.name);
    await fs.writeFile(input, patched);
  }

  const args = [input, path.join(BUILD, "c75shim.c"), ...FLAGS, "-o", out];

  // Programs that read or write data files expect a text/ folder beside them.
  const data = path.join(prog.dir, "text");
  if (await fs.stat(data).then(() => true, () => false)) {
    args.push("--embed-file", `${data}@/text`);
  }

  const { stderr } = await exec("emcc", args, { cwd: ROOT, maxBuffer: 32 * 1024 * 1024 });

  // A signature mismatch links to a stub that traps the moment it is called,
  // so it is a build failure here rather than a mystery at runtime.
  return stderr
    .split("\n")
    .filter((l) => /signature mismatch|undefined symbol/.test(l))
    .map((l) => l.trim());
}

const items = await collect();
const TMP = await fs.mkdtemp(path.join(os.tmpdir(), "c75-"));
await fs.mkdir(OUT, { recursive: true });

const manifest = [];
const failed = [];
const suspect = [];
let done = 0;

// emcc is single-threaded per invocation; run a few at once.
const queue = [...items];
const workers = Array.from({ length: Math.max(2, os.cpus().length - 1) }, async () => {
  for (let prog; (prog = queue.shift()); ) {
    const source = await fs.readFile(prog.file, "utf8");
    try {
      const warnings = await compile(prog, source);
      if (warnings.length) suspect.push({ name: prog.name, warnings });
      manifest.push({
        id: prog.id,
        num: prog.num,
        title: prog.title,
        tag: prog.tag,
        ref: prog.ref,
        file: prog.name,
        // Files with no leading number (Snake) are bonus entries, listed last.
        extra: prog.num == null,
        interactive: NEEDS_INPUT.test(source),
        patched: Boolean(PATCHES[prog.name]),
        source: source.replace(/\r\n/g, "\n"),
      });
    } catch (e) {
      failed.push({ name: prog.name, error: (e.stderr || e.message).slice(-1200) });
    }
    process.stdout.write(`\r  compiled ${++done}/${items.length}`);
  }
});
await Promise.all(workers);

// Unnumbered bonus programs sort after everything numbered.
const rank = (p) => (p.num == null ? Infinity : p.num);
manifest.sort((a, b) => rank(a) - rank(b) || a.file.localeCompare(b.file));
await fs.writeFile(
  path.join(ROOT, "site", "programs.json"),
  JSON.stringify(manifest, null, 1)
);

// Drop wasm from programs that no longer exist (e.g. the removed Sliding
// Puzzle), so site/wasm always mirrors the current manifest.
const keep = new Set(manifest.flatMap((p) => [`${p.id}.js`, `${p.id}.wasm`]));
for (const f of await fs.readdir(OUT)) {
  if (!keep.has(f)) await fs.rm(path.join(OUT, f));
}

console.log(`\n${manifest.length} programs built -> site/programs.json`);

if (suspect.length) {
  console.log(`\n${suspect.length} with signature/symbol warnings (these trap at runtime):`);
  for (const s of suspect) console.log(`  ${s.name}\n    ${s.warnings.join("\n    ")}`);
}
if (failed.length) {
  console.log(`\n${failed.length} FAILED:`);
  for (const f of failed) console.log(`\n--- ${f.name}\n${f.error}`);
  process.exitCode = 1;
}
