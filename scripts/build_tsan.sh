#!/usr/bin/env bash
set -euo pipefail
cmake -S . -B build/tsan -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCONCURRENCY_ENABLE_TSAN=ON -DCONCURRENCY_ENABLE_TESTS=ON -DCONCURRENCY_ENABLE_BENCH=ON
cmake --build build/tsan -j
echo "Built: build/tsan"
