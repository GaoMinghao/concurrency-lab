// Lab 01A：`thread_guard` + 异常路径反例
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class thread_guard {
public:
  explicit thread_guard(std::thread &t_) : t(t_) {}
  ~thread_guard() {
    if (t.joinable()) {
      t.join();
    }
  }
  thread_guard(thread_guard &other) = delete;
  thread_guard &operator=(thread_guard &other) = delete;

private:
  std::thread &t;
};

std::mutex read_m;
std::mutex write_m;

std::string read_file(std::string file) {
  std::lock_guard<std::mutex> read_lock(read_m);
  std::string content = "Data from " + file;
  std::cout << "[Read] Read data from " << file << std::endl;
  return content;
}

void write_file(std::string file, std::string &data) {
  write_m.lock();
  try {
    std::cout << "[Write] Writing to " << file << ": " << data << std::endl;

    if (file.find("fail") != std::string::npos) {
      throw std::runtime_error("Write failed");
    }
  } catch (...) { // 异常路径的反例
    std::cout << "[Error] Exception caught, but forgot to unlock!" << std::endl;
    throw;
  }

  write_m.unlock();
}

void copy_file(std::string src, std::string dst) {
  std::string data = read_file(src);
  write_file(dst, data);
}

int main() {
  try {
    std::thread t1(copy_file, "src", "dst");
    thread_guard g1(t1);
    std::thread t2(copy_file, "data", "fail");
    thread_guard g2(t2);
  } catch (const std::exception &e) {
    std::cout << "Main caught exception: " << e.what() << std::endl;
  }
}