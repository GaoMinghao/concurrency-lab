// stop_token 最小可控实例
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <stop_token>
#include <thread>

void worker(std::stop_token stop_token) {
  while (!stop_token.stop_requested()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Working..." << std::endl;
  }
}

using namespace std::chrono_literals;

void worker_2(std::stop_token stop_token) {
  std::mutex m;
  std::condition_variable_any cv;

  while (!stop_token.stop_requested()) {
    std::cout << "Working... (Thread id: " << std::this_thread::get_id()
              << std::endl;

    std::unique_lock lk(m);
    // wait_for 5s 之后会醒来，收到 request_stop 也会立刻醒来
    cv.wait_for(lk, stop_token, 2s, []() { return false; });
  }
  std::cout << "Worker thread stopped gracefully." << std::endl;
}

int main() {
  // std::jthread t(worker);
  // std::this_thread::sleep_for(3s);
  // t.request_stop();
  std::jthread t2(worker_2);
  std::this_thread::sleep_for(5s);
  t2.request_stop();
}