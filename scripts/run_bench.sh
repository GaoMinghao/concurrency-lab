#!/usr/bin/env bash
set -euo pipefail
if [[ -x build/release/bin/example_bench ]]; then
  build/release/bin/example_bench
else
  echo "example_bench not found. Ensure CONCURRENCY_ENABLE_BENCH=ON and build release."
  exit 1
fi
