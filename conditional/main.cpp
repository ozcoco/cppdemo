//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

class A {
 public:
  inline void print() const {
    std::cout << "print A" << "\n";
  }
};

class B {
 public:
  inline void print() const {
    std::cout << "print B" << "\n";
  }
};

template<bool _cond>
class T : public std::conditional_t<_cond, A, B> {};

template<bool _cond, typename T, typename U>
struct conditional {
  using type = T;
};

template<typename T, typename U>
struct conditional<false, T, U> {
  using type = U;
};

template<bool cond, typename T, typename U>
using conditional_t = typename conditional<cond, T, U>::type;

template<bool _cond>
class T2 : public conditional_t<_cond, A, B> {};

int main() {

  T<true>().print();
  T<false>().print();

  T2<true>().print();
  T2<false>().print();

}