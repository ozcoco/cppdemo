//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

int main() {

  int a = -1;
  auto a_size = sizeof(a);
  printf("a_size=%llu\n", a_size);

  if (a > a_size) {
    printf("大于\n");
  } else {
    printf("小于\n");
  }

  auto ua = static_cast<unsigned int>(a);
  printf("ua=%u\n", ua);

}