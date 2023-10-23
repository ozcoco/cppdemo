//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

template<auto T, auto U>
inline constexpr
auto add() {
  std::cout << __DATE__ << __TIMESTAMP__ << __FUNCTION__ << "\n";
  return T + U;
}

class A {
 public:
  auto add(int a, int b) {
    std::cout << __DATE__ << __TIMESTAMP__ << __FUNCTION__ << "\n";
    return a + b;
  }

};

int main() {

  constexpr bool v = std::is_same_v<decltype(add<3, 1>()), double>;
  std::cout << v << "\n";

//  std::declval不构造对象调用成员函数  decay_t去除类型修饰
  constexpr bool v2 = std::is_same_v<std::decay_t<decltype(std::declval<A>().add(1, 4))>, int>;
  std::cout << v2 << "\n";

}