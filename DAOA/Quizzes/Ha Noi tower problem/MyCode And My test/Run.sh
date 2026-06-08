#!/bin/bash
set -euo pipefail

if [[ ! -d build ]]; then
  mkdir build
fi

if [[ "${1:-}" == "--fresh" ]]; then
  cmake --fresh -S . -B build
else
  cmake -S . -B build
fi

cmake --build build
clear
./build/TowerOfHanoi