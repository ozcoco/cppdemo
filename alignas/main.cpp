//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

/*
 * 字节对齐能提高CPU访问内存效率
 *
 * */

struct A { //默认8字节对齐   : 16
  char c;
  bool b;
  short sn;
  double d;
};

struct B {//: 24
  char c;
  bool b;
  alignas(8) short sn;
  double d;
};

struct C { //32
  char c;
  alignas(8) bool b;
  alignas(8) short sn;
  double d;
};

struct D { //32
  alignas(8) char c;
  alignas(8) bool b;
  alignas(8) short sn;
  double d;
};

struct E { //16
  alignas(8) char c; //1
  bool b;  //1
  short sn; //2
  double d;
};

int main() {

  std::cout << "char = " << sizeof(char) << "\n";
  std::cout << "bool = " << sizeof(bool) << "\n";
  std::cout << "short = " << sizeof(short) << "\n";
  std::cout << "int = " << sizeof(int) << "\n";
  std::cout << "long int = " << sizeof(long int) << "\n";
  std::cout << "long long int = " << sizeof(long long int) << "\n";
  std::cout << "float = " << sizeof(float) << "\n";
  std::cout << "double = " << sizeof(double) << "\n";
  std::cout << "struct A = " << sizeof(A) << "\n";
  std::cout << "struct B = " << sizeof(B) << "\n";
  std::cout << "struct C = " << sizeof(C) << "\n";
  std::cout << "struct D = " << sizeof(D) << "\n";
  std::cout << "struct E = " << sizeof(E) << "\n";

}