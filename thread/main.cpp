//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <coroutine>

int main() {

  std::jthread{[](const int &arg) {

    printf("arg=%d\n", arg);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    printf("child thread exit\n");

  }, 1};  //自动join

  std::thread{[](const int &arg) {

    printf("arg=%d\n", arg);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    printf("child thread exit\n");

  }, 1};  //若无主动join或detach，则会报异常


  printf("main thread exit\n");

}