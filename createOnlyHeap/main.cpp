//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

class Foo {

 public:
  ~Foo() = delete;  //方法1

  void release() {
    //recycle memory
  }

// private:
//  ~Foo() = default;   //方法2

};

int main() {

//  Foo foo{};  //compile error
  Foo *pFoo = new Foo{};
  pFoo->release();

}