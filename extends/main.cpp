//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

/**
 *
 * C++中纯虚函数不能被构造函数调用，但在Java中可以
 *
 * **/

class Foo {
 public:
  Foo() {
//    print();  //compile error
    printf("Foo init\n");
//    show(); //runtime error
  }

  virtual void print() = 0;

  virtual void show() {
    print();
  }

};

class SubFoo : public Foo {
 public:
  SubFoo() {
    printf("SubFoo init\n");
  }

  void print() override {

    printf("--->SubFoo\n");

  }

  void show() override {
    Foo::show();
  }

};

int main() {

  Foo *f = new SubFoo{};
  f->print();
  f->show();

}