# first 75

The C programs I wrote learning the language in 2008, compiled to WebAssembly
and running in the browser — including the interactive ones.

```bash
node serve.mjs      # → http://localhost:8075
```

Pick a program on the left; the source is on the right with a console beneath
it. Programs that read input take it in the console and nowhere else.

## How it runs

Every `.c` file is compiled ahead of time to its own `.wasm` by `build/build.mjs`.
The site is static — there is no compiler and no program execution on the
server. `serve.mjs` only serves files.

Each program runs on a Web Worker. `scanf()` and `getch()` need to *block*, so
the worker parks on `Atomics.wait` against a `SharedArrayBuffer` until the page
sends a keystroke. That requires the page to be cross-origin isolated, which is
why `serve.mjs` sets `Cross-Origin-Opener-Policy` and
`Cross-Origin-Embedder-Policy`. Opening `site/index.html` from the filesystem
will load but will not accept input.

The console is a real screen buffer rather than an append-only log, because
these programs clear and redraw in place. It decodes output as code page 437,
so the box-drawing art and arrow glyphs land as written.

## Making them build

The sources target Turbo C / Dev-C++ on Windows. `build/c75shim.h` is force-
included into every file and supplies what the browser lacks:

| Original | Here |
| --- | --- |
| `getch()`, `getche()` | raw key read, bypassing stdin as conio did |
| `system("cls")` | clears the screen buffer |
| `system("pause")` | prints the prompt, waits for a key |
| `system("mode con cols=… lines=…")` | resizes the console |
| `system("title …")` | sets the pane title |
| `SetConsoleTextAttribute` | Windows colour attribute → ANSI |
| `MessageBox` | drawn inline in the console |
| `sleep(1200)` | milliseconds, as MinGW meant it — not POSIX seconds |
| `fopen("text\\record.dat")` | backslash paths normalised |
| `gets()` | removed from C11; reimplemented |

The data files in `first75/text/` are embedded into the programs that read
them, so file I/O works. Writes land in an in-memory filesystem and last for
the run.

Two files needed a build-time patch to get through clang; both are listed in
`PATCHES` in `build/build.mjs`, applied to a temporary copy, and flagged as
`compat-patched` in the UI. `first75/` is never modified, and the source shown
on screen is always the original:

- **65 virus 3** — prototypes declared `char a[][]`, which the definitions
  spell `char a[maxboard][maxboard]`; `time.h` was never included.
- **73 card dealer** — `stdlib.h` was never included, so `srand` was implicitly
  `int` and `while (srand(seed))` was an endless deal loop. The patch keeps
  that meaning.

## Rebuilding

```bash
./build/setup.sh                                    # installs emsdk (~1.7 GB)
source tools/emsdk/emsdk_env.sh && node build/build.mjs
```

The build fails loudly on signature mismatches — on wasm those link to a stub
that traps the moment it is called, which is how `time()` without `time.h`
showed up.

## Layout

```
first75/       the original 2008 sources, untouched
build/         shim headers, JS bridge, build script
site/          the static site (index.html, terminal, worker, wasm/)
serve.mjs      static server with the isolation headers
```
