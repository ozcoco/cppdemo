//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <variant>
#include <string>
#include <string_view>
#include <sstream>

using namespace std::literals::string_literals;

template<class>
inline static constexpr bool always_false_v = false;

struct Visitor {
  inline void operator()(bool v) const {
    std::cout << "bool v = " << v << std::endl;
  }
  inline void operator()(char v) const {
    std::cout << "char v = " << v << std::endl;
  }
  inline void operator()(int v) const {
    std::cout << "int v = " << v << std::endl;
  }
  inline void operator()(double v) const {
    std::cout << "double v = " << v << std::endl;
  }
  inline void operator()(float v) const {
    std::cout << "float v = " << v << std::endl;
  }
  inline void operator()(std::string &v) const {
    std::cout << "std::string v = " << v << std::endl;
  }
  inline void operator()(auto &&v) const {
    static_assert(always_false_v<decltype(v)>, "non-exhaustive visitor!");
  }

};

static void visit_feature() {

  std::variant<bool, char, int, double, float, std::string> v{};
  v = "abcdef"s;
  std::visit(Visitor{}, v);

  v = 0.01f;

  std::visit([](auto &&v) {

    using T = std::decay_t<decltype(v)>;

    if constexpr (std::is_same_v<T, bool>)
      std::cout << "bool v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, char>)
      std::cout << "char v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, int>)
      std::cout << "int v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, float>)
      std::cout << "float v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, double>)
      std::cout << "double v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, std::string>)
      std::cout << "std::string v = " << v << std::endl;
    else
      static_assert(always_false_v<decltype(v)>, "non-exhaustive visitor!");

  }, v);

}

int main() {

  visit_feature();

}