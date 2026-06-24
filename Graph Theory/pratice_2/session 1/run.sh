#!/bin/bash

set -euo pipefail
cmake -S . -B build
cmake --build build
./build/session_1
