// Lab 01B：`std::jthread` 重写并对比
#include <exception>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

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
    std::cerr << "[Error] Exception caught, but forgot to unlock!" << std::endl;
    write_m.unlock();
    throw;
  }

  write_m.unlock();
}

void copy_file(std::string src, std::string dst) {
  try {
    std::string data = read_file(src);
    write_file(dst, data);
  } catch (const std::exception &e) {
    std::cerr << "[Thread " << std::this_thread::get_id()
              << "] Caught exception: " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "[Thread " << std::this_thread::get_id()
              << "] Caught unknown exception." << std::endl;
  }
}

int main() {
  try {
    std::jthread t1(copy_file, "src", "dst");
    std::jthread t2(copy_file, "data", "fail");
  } catch (const std::exception &e) {
    std::cout << "Main caught exception: " << e.what() << std::endl;
  }
}