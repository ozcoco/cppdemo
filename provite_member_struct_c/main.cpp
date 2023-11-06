//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include "info_struct_c.h"

int main() {

  info_t *info = create_info("abcd", 10);
  printf("info{ name=%s, age = %d }\n", get_name(info), get_age(info));

  set_name(info, "一只快乐的喵");
  set_age(info, 123);
  printf("info{ name=%s, age = %d }\n", get_name(info), get_age(info));

}