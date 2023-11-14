//
// Created by ozcom on 2023/9/28.
//

#include <iostream>


class Foo {

 public:
  void *operator new(std::size_t count) = delete;   //方法1
  void *operator new[](std::size_t count) = delete;

// private:
//  void *operator new(std::size_t count) {   //方法2
//    return ::operator new(count);
//  }
//
//  void *operator new[](std::size_t count) {
//    return ::operator new[](count);
//  }


};


int main() {

  Foo foo{};
//  Foo *pFoo = new Foo{};  //compile error

}