// Lab 00A：故意制造 data race → TSan 报告 → 修复到 clean
#include <iostream>
#include <mutex>
#include <thread>

int global_value = 0;

std::mutex m;

void increase_global_value_by_one() {
  std::lock_guard<std::mutex> lock(m);
  global_value++;
}

void increase_global_value() {
  for (int i = 0; i < 10000000; ++i) {
    increase_global_value_by_one();
  }
}

int main() {
  std::thread t_a(increase_global_value);
  std::thread t_b(increase_global_value);
  t_a.join();
  t_b.join();
  std::cout << global_value << std::endl;
}