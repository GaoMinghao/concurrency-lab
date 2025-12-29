// Lab 01A：`thread_guard` + 异常路径反例
#include <cwchar>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>

std::mutex read_m;
std::mutex write_m;

void read_file(std::string file, std::fstream &fs) {
  std::lock_guard<std::mutex> read_lock(read_m);
  std::fstream(file, std::ios::in | std::ios::binary);
  fs.read(, streamsize n)
}

void write_file(std::string file) {
  write_m.lock();
  try {
    std::fstream(file, std::ios::out | std::ios::binary);
  } catch (...) {
    throw;
  }
  write_m.unlock();
}

void copy_file(std::string src, std::string dst) {
  read_file(src);
  write_file(dst);
}

int main() { std::thread t1(copy_file("src", "dst")) }