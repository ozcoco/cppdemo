//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <thread>
#include <condition_variable>

static std::mutex g_iMutex{};
static std::condition_variable g_iConditionVar{};

static long count = 0;

int main() {

  std::thread t1{[&]() {

    for (;;) {

      std::unique_lock lock{g_iMutex};
      count += 3;
      std::cout << "count += 3\n";

      g_iConditionVar.notify_one();

    }

  }};

  std::thread t2{[&]() {

    for (;;) {

      std::unique_lock lock{g_iMutex};

      if (count < 5)
        g_iConditionVar.wait(lock);

      count -= 2;
      std::cout << "count =" << count << "\n";

    }

  }};

  t2.join();
  t1.join();

}