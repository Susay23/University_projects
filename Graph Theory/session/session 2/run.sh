#!/bin/bash
set -euo pipefail
cmake -S . -B build
cmake --build build
ctest --test-dir build
./build/session_2
