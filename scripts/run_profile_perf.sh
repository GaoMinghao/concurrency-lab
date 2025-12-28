#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <binary> [args...]"
  echo "Example: $0 build/release/bin/example_app"
  exit 1
fi

BIN="$1"; shift
if ! command -v perf >/dev/null 2>&1; then
  echo "perf not found. Install linux-tools/perf or use another profiler."
  exit 1
fi

perf record -g --call-graph dwarf -- "${BIN}" "$@"
perf report --stdio > results/week00_perf_report.txt
head -n 15 results/week00_perf_report.txt

