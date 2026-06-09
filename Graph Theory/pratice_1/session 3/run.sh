#!/bin/bash
# This script is used to build and run the session_2 project
set -euo pipefail
cmake -S . -B build
cmake --build build
ctest --test-dir build
./build/session_3
