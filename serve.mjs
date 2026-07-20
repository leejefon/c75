#!/usr/bin/env node
// Static file server for site/.
//
// The COOP/COEP headers are the point: without them the page is not
// cross-origin isolated, SharedArrayBuffer is unavailable, and blocking
// stdin (scanf, getch) cannot work.
import http from "node:http";
import fs from "node:fs";
import path from "node:path";

const ROOT = path.join(import.meta.dirname, "site");
const PORT = Number(process.env.PORT) || 8075;

const TYPES = {
  ".html": "text/html; charset=utf-8",
  ".js": "text/javascript; charset=utf-8",
  ".mjs": "text/javascript; charset=utf-8",
  ".css": "text/css; charset=utf-8",
  ".json": "application/json; charset=utf-8",
  ".wasm": "application/wasm",
  ".data": "application/octet-stream",
  ".svg": "image/svg+xml",
};

http
  .createServer((req, res) => {
    const url = decodeURIComponent(req.url.split("?")[0]);
    const file = path.join(ROOT, url === "/" ? "index.html" : url);

    // Never serve outside site/.
    if (!file.startsWith(ROOT)) {
      res.writeHead(403).end("Forbidden");
      return;
    }

    fs.readFile(file, (err, body) => {
      if (err) {
        res.writeHead(404, { "content-type": "text/plain" }).end("Not found");
        return;
      }
      res.writeHead(200, {
        "content-type": TYPES[path.extname(file)] ?? "application/octet-stream",
        "cross-origin-opener-policy": "same-origin",
        "cross-origin-embedder-policy": "require-corp",
        "cache-control": "no-cache",
      });
      res.end(body);
    });
  })
  .listen(PORT, () => console.log(`first75 → http://localhost:${PORT}`));
