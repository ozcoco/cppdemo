//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <string>
#include <string_view>

//string_view可减少字符串复制

int main() {

  std::string s{"abcdefghijk"};
  std::string s1 = s;
  std::string s2 = s;
  printf("s.data() = %p\n", s.data());
  printf("s1.data() = %p\n", s1.data());
  printf("s2.data() = %p\n", s2.data());

  std::string_view sv1 = s;
  std::string_view sv2 = s;
  printf("sv1.data() = %p\n", sv1.data());
  printf("sv2.data() = %p\n", sv2.data());

}