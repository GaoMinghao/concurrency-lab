#!/usr/bin/env bash
set -euo pipefail

# Build TSAN version
bash "$(dirname "$0")/build_tsan.sh"

# Run tests under TSAN with ASLR disabled if possible
if command -v setarch >/dev/null 2>&1; then
  setarch "$(uname -m)" -R ctest --test-dir build/tsan --output-on-failure
else
  echo "Warning: 'setarch' not found; running tests without disabling ASLR. ThreadSanitizer may crash."
  ctest --test-dir build/tsan --output-on-failure
fi
