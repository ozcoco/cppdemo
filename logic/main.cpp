//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <bitset>


//位运算符：&,|,~,^
//逻辑运算符：&&, ||, !

int main() {

  char a = 2;
  char b = 5;
  std::cout << "a =" << std::bitset<sizeof(char) * 8>(a) << std::endl;
  std::cout << "b =" << std::bitset<sizeof(char) * 8>(b) << std::endl;
  std::cout << "a ^ b=" << std::bitset<sizeof(char) * 8>(a ^ b) << std::endl;

}