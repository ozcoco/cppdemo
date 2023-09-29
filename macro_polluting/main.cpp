//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

#define min(a, b) (((a) > (b)) ? (b) : (a))

/**
 *
 * 宏的污染是应为宏的命名没有限制
 * 因此导致命名冲突
 *
 * 规避宏污染的方式
 * 1、取消宏定义
 * 2、使用（）
 *
 * **/

int main() {

//  constexpr int v = std::min(1, 2); //编译失败，min函数会被min宏替换: constexpr int v = std::(((1) > (2)) ? (2) : (1))

  constexpr int v = (std::min)(1, 2); //函数加()
  std::cout << "v=" << v << std::endl;

#ifdef min
#undef min //取消宏定义
#endif
  constexpr int v2 = std::min(1, 2);
  std::cout << "v2=" << v2 << std::endl;

}