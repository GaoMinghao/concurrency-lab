// Lab 01A：`thread_guard` + 异常路径反例
#include <cwchar>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>

std::mutex read_m;
std::mutex write_m;

std::streambuf *read_file(std::string file) {
  std::lock_guard<std::mutex> read_lock(read_m);
  std::fstream f{file, std::ios::binary};
  return f.rdbuf();
}

void write_file(std::string file, std::streambuf *buf) {
  write_m.lock();
  try {
    std::fstream dest{file, std::ios::out | std::ios::binary};
    dest << buf;
  } catch (...) { // 异常路径的反例
    throw;
  }

  write_m.unlock();
}

void copy_file(std::string src, std::string dst) {
  std::streambuf *buf = read_file(src);
  write_file(dst, buf);
}

int main() {
  std::thread t1(copy_file, "src", "dst");
  std::thread t2(copy_file, "dst", "src");
  if (t1.joinable()) {
    t1.join();
  }
  if (t2.joinable()) {
    t2.join();
  }
}