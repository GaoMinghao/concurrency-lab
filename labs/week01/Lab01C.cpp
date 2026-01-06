#include <iostream>
#include <stop_token>
#include <thread>

void worker(std::stop_token stop_token) {
  while (!stop_token.stop_requested()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Working..." << std::endl;
  }
}

int main() {
  std::jthread t(worker);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  // jthread 的析构函数中会直接调用 request_stop
}