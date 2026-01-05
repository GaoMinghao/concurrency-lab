cmake_minimum_required(VERSION 3.20)
project(concurrency_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CONCURRENCY_ENABLE_TSAN "Enable ThreadSanitizer instrumentation" OFF)
option(CONCURRENCY_ENABLE_TESTS "Build tests" ON)
option(CONCURRENCY_ENABLE_BENCH "Build benchmarks" OFF)

# Common warnings (tweak as you like)
if (MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if (CONCURRENCY_ENABLE_TSAN)
  message(STATUS "ThreadSanitizer enabled")
  if (NOT MSVC)
    add_compile_options(-fsanitize=thread -fno-omit-frame-pointer)
    add_link_options(-fsanitize=thread)
  else()
    message(WARNING "TSan is not supported with MSVC in the same way; use clang-cl/WSL clang if needed.")
  endif()
endif()

# Output layout
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ---- Core example app (placeholder) ----
add_executable(lab00_race labs/week00/src/lab00_race.cpp)
add_executable(lab00_clean labs/week00/src/lab00_clean.cpp)
add_executable(lab01A labs/week01/Lab01A.cpp)

# ---- Tests (placeholder; not wired to gtest by default) ----
if (CONCURRENCY_ENABLE_TESTS)
  enable_testing()
  add_test(NAME lab00_race COMMAND lab00_race)
  add_test(NAME lab00_clean COMMAND lab00_clean)
  add_test(NAME lab01A COMMAND lab01A)
endif()

# ---- Bench (placeholder; not wired to google benchmark by default) ----
if (CONCURRENCY_ENABLE_BENCH)
  add_executable(example_bench
    bench/example_bench.cpp
  )
endif()

# Notes:
# - If you want gtest / benchmark:
#   Option A) vendoring: put sources under third_party/ and add_subdirectory them.
#   Option B) FetchContent: download during configure (requires network).
