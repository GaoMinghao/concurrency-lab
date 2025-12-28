#!/usr/bin/env bash
set -euo pipefail
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release -DCONCURRENCY_ENABLE_TSAN=OFF -DCONCURRENCY_ENABLE_TESTS=ON -DCONCURRENCY_ENABLE_BENCH=ON
cmake --build build/release -j
echo "Built: build/release"
