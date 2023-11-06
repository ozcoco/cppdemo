//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

template<auto T, auto U>
constexpr
auto add() {
  return T + U;
}

int main() {

  constexpr bool v = std::is_same_v<decltype(add<3, 1>()), bool>;
  std::cout << v << "\n";

}