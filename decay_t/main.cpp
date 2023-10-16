//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

/*
 * std::decay 元函数，用于去除类型修饰符
 *
 * */

int main() {

  int a = 1;
  int &ar = a;
  int &&b = 2;
  const int &c = b;
  std::cout << "a:" << typeid(a).name() << std::endl;
  std::cout << "ar:" << typeid(ar).name() << std::endl;
  std::cout << "b:" << typeid(b).name() << std::endl;
  std::cout << "c:" << typeid(c).name() << std::endl;

  std::cout << "c: = a:" << std::is_same_v<decltype(c), decltype(a)> << std::endl;
  using Tc = std::decay<decltype(c)>::type; //去除类型修饰符
  using Tc2 = std::decay_t<decltype(c)>;
  std::cout << "c: = a:" << std::is_same_v<Tc, decltype(a)> << std::endl;
  std::cout << "c: = a:" << std::is_same_v<Tc2, decltype(a)> << std::endl;

}