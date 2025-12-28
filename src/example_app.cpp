#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

// 检查 C++ 版本是否支持 C++20
#if __cplusplus < 202002L
#error "当前编译器未开启 C++20 模式，请在编译选项中添加 -std=c++20"
#endif

// Placeholder app: demonstrates a simple start gate.
// Replace with your weekly labs (prefer putting labs in labs/weekXX/).
int main() {
  std::atomic<bool> go{false};

  std::jthread t([&](std::stop_token st) {
    // C++20: avoid busy-wait in real code; use atomic::wait/notify in Week 4.
    while (!go.load(std::memory_order_relaxed) && !st.stop_requested()) {
      std::this_thread::yield();
    }
    if (st.stop_requested())
      return;
    std::cout << "worker started\n";
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  go.store(true, std::memory_order_relaxed);
  std::cout << "go\n";
  return 0;
}
