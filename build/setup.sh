#!/usr/bin/env bash
# Installs the Emscripten SDK into tools/emsdk (gitignored, ~1.7 GB).
set -euo pipefail

cd "$(dirname "$0")/.."

if [ ! -d tools/emsdk ]; then
  git clone --depth 1 https://github.com/emscripten-core/emsdk.git tools/emsdk
fi

cd tools/emsdk
./emsdk install latest
./emsdk activate latest

echo
echo "Done. Now build with:"
echo "  source tools/emsdk/emsdk_env.sh && node build/build.mjs"
