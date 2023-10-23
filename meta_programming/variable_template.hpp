//
// Created by ozcom on 2023/10/17.
//

#ifndef CPP_FEATURE_DEMO_META_PROGRAMMING_VARIABLE_TEMPLATE_HPP_
#define CPP_FEATURE_DEMO_META_PROGRAMMING_VARIABLE_TEMPLATE_HPP_

#include <iostream>
#include <array>
#include <string>
#include <string_view>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

template<typename ...Args>
constexpr
auto types_sum(Args &&...args) {
  return (... + args);
}

template<typename T, T ...args>
struct my_args_sum {
  enum {
    value = (... + args),
    value2 = (args + ... ),
    value3 = (0 + ... + args),
    value4 = (args + ... + 0)
  };
};

template<double ...args>
struct my_args_sum<double, args...> {
  constexpr inline static auto value = (... + args);
};

class Bar {
 public:
  Bar() = delete;
  constexpr explicit Bar(std::pair<std::string, int> const &v) : v_(v) {}
  constexpr explicit Bar(std::pair<std::string, int> &&v) : v_(v) {}

  constexpr Bar operator+(const Bar &rfh) const {
    std::string k{this->v_.first};
    k.append(", ");
    k.append(rfh.v_.first);
    return Bar{std::make_pair(std::move(k), this->v_.second + rfh.v_.second)};
  }

  bool operator==(const Bar &rhs) const {
    return v_ == rhs.v_;
  }
  bool operator!=(const Bar &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const Bar &rhs) const {
    return v_ < rhs.v_;
  }
  bool operator>(const Bar &rhs) const {
    return rhs < *this;
  }
  bool operator<=(const Bar &rhs) const {
    return !(rhs < *this);
  }
  bool operator>=(const Bar &rhs) const {
    return !(*this < rhs);
  }

   private:
  std::pair<std::string, int> v_;
};

template<typename T, T ...args>
constexpr auto my_args_sum_v = my_args_sum<T, args...>::value;

template<int...args>
constexpr auto my_integer_sequence_sum_v = my_args_sum_v<int, args...>;

void variable_template_main() {

  std::cout << types_sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 0) << "\n";
  std::cout << my_args_sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value << "\n";
  std::cout << my_args_sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value2 << "\n";
  std::cout << my_args_sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value3 << "\n";
  std::cout << my_args_sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value4 << "\n";
  std::cout << my_args_sum_v<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0> << "\n";
  std::cout << my_integer_sequence_sum_v<1, 2, 3, 4, 5, 6, 7, 8, 9, 0> << "\n";

}

#endif //CPP_FEATURE_DEMO_META_PROGRAMMING_VARIABLE_TEMPLATE_HPP_
