//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

enum A {
  A1 = 100, A2, A3
};

//强类型enum不会隐式转换为int
enum class B {
  B1 = 10000, B2, B3
};

int main() {

  int a = A1;
//  int b = B::B1; //error, 编译失败

  std::cout << A1 << std::endl;

  {
    using enum B; //c++20强类型enum特性
    std::cout << static_cast<int>(B1) << std::endl;
  }

}