#include <atomic>
#include <iostream>
#include <thread>

int main() {
  std::atomic<int> counter{0};
  auto increment = [&counter]() { ++counter; };

  std::thread t1(increment);
  std::thread t2(increment);

  t1.join();
  t2.join();

  std::cout << "Counter value: " << counter << std::endl;
}