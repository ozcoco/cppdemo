//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

static void const_pointer_var() {

  int a = 1;
  int const *ap = &a;   // *ap r, ap rw
  printf("a=%d\n", a);
  printf("*ap=%d\n", *ap);
  printf("ap=%p\n", ap);
  printf("&ap=%p\n", &ap);
  printf("------------------------------------------------\n");

  int a2 = 2;
  ap = &a2;
//  *ap = 22;
  printf("a2=%d\n", a2);
  printf("*ap=%d\n", *ap);
  printf("ap=%p\n", ap);
  printf("&ap=%p\n", &ap);
  printf("------------------------------------------------\n");

  int a3 = 2;
  int const *const ap2 = &a3; //*ap2 r, ap2 r
  printf("a3=%d\n", a3);
  printf("*ap2=%d\n", *ap2);
  printf("ap2=%p\n", ap2);
  printf("&ap2=%p\n", &ap2);
  printf("------------------------------------------------\n");

  int a4 = 4;
//  ap2 = &a4;
//  *ap2 = 5;
  printf("------------------------------------------------\n");

  int a5 = 5;
  int *const ap3 = &a5; //*ap3 rw, ap3 r
  printf("a5=%d\n", a5);
  printf("*ap3=%d\n", *ap3);
  printf("ap3=%p\n", ap3);
  printf("&ap3=%p\n", &ap3);
  printf("------------------------------------------------\n");

//  ap3 = nullptr;
  *ap3 = 6;
  printf("a5=%d\n", a5);
  printf("*ap3=%d\n", *ap3);
  printf("ap3=%p\n", ap3);
  printf("&ap3=%p\n", &ap3);
  printf("------------------------------------------------\n");

  int a7 = 7;
  int *ap7 = &a7;
  printf("a7=%d\n", a7);
  printf("*ap7=%d\n", *ap7);
  printf("&a7=%p\n", &a7);
  printf("ap7=%p\n", ap7);
  printf("&ap7=%p\n", &ap7);

  int a8 = 8;
  ap7 = &a8;
  printf("a8=%d\n", a8);
  printf("*ap7=%d\n", *ap7);
  printf("&a8=%p\n", &a8);
  printf("ap7=%p\n", ap7);
  printf("&ap7=%p\n", &ap7);

  *ap7 = 9;
  printf("a8=%d\n", a8);
  printf("*ap7=%d\n", *ap7);
  printf("&a8=%p\n", &a8);
  printf("ap7=%p\n", ap7);
  printf("&ap7=%p\n", &ap7);

  printf("------------------------------------------------\n");

}


int main() {

  const_pointer_var();

}