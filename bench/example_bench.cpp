#include <chrono>
#include <cstdint>
#include <iostream>

// Placeholder "benchmark" (no Google Benchmark dependency).
// Replace with Google Benchmark when you are ready.
int main() {
  constexpr std::uint64_t N = 50'000'000;
  volatile std::uint64_t x = 0;
  auto t0 = std::chrono::steady_clock::now();
  for (std::uint64_t i = 0; i < N; ++i) x += i;
  auto t1 = std::chrono::steady_clock::now();
  auto ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
  std::cout << "bench: " << ms << " ms\n";
  return 0;
}
