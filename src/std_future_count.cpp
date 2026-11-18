#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

// In a new thread, with std::future, count to 100 with a 0.1s pause on each number.
// Print the runtime then exit.

std::chrono::milliseconds count_to_100()
{
  auto start = std::chrono::steady_clock::now();
  for (size_t i = 0; i < 100; ++i)
  {
    std::this_thread::sleep_for(100ms);
  }
  auto end = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}

int main() {
  std::future<std::chrono::milliseconds> result = std::async(std::launch::async, count_to_100);
  std::cout << result.get() << std::endl;
  return 0;
}
