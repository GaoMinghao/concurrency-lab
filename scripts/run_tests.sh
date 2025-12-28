#!/usr/bin/env bash
set -euo pipefail
if [[ -d build/release ]]; then
  ctest --test-dir build/release --output-on-failure
else
  echo "build/release not found. Run ./scripts/build_release.sh first."
  exit 1
fi
