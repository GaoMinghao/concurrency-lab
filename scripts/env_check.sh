#!/usr/bin/env bash
set -euo pipefail
echo "uname: $(uname -a)"
echo "cmake: $(cmake --version | head -n1 || true)"
echo "c++: $(c++ --version | head -n1 || true)"
echo "clang++: $(clang++ --version | head -n1 || true)"
echo "g++: $(g++ --version | head -n1 || true)"
echo "perf: $(perf --version 2>/dev/null || echo 'not found')"
