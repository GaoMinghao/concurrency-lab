// Lab 00A：故意制造 data race → TSan 报告 → 修复到 clean
#include <iostream>
#include <thread>

int global_value = 0;

void increase_global_value() { 
  global_value++; }

int main() {
  std::thread t_a(increase_global_value);
  std::thread t_b(increase_global_value);
  t_a.join();
  t_b.join();
  std::cout << global_value << std::endl;
}
