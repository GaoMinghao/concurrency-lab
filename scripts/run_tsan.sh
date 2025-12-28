#!/usr/bin/env bash
set -euo pipefail
if [[ -d build/tsan ]]; then
  # Run tests under TSan build.
  ctest --test-dir build/tsan --output-on-failure
else
  echo "build/tsan not found. Run ./scripts/build_tsan.sh first."
  exit 1
fi
