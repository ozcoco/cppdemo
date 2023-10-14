//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <exception>
#include <string>
#include <utility>

class MyException : public std::exception {

 public:
  explicit MyException(std::string msg) noexcept: msg(std::move(msg)) {}

  [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
    return msg.c_str();
  }

 private:
  const std::string msg;

};

static void catch_my_exception() noexcept {

  try {

    printf("catch_my_exception\n");

    throw MyException{"my exception test"};

  } catch (const MyException &ex) {

    std::cout << ex.what() << std::endl;

  } catch (...) {

    std::cout << std::current_exception().__cxa_exception_type()->name() << std::endl;

  }

}

int main() {

  catch_my_exception();

}