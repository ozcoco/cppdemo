//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <optional>
#include <utility>

template<typename T, T ...ts>
constexpr
std::optional<T> foo() {
  if (!sizeof...(ts)) return std::nullopt;
  using res_type = std::decay_t<T>;
  res_type res{};
  ((res += ts), ...);
  return res;
}

template<typename T, T ...ts>
struct sum {
  using value_type = std::decay_t<T>;
 private:
  inline static value_type v{};
 public:
  inline static value_type const value = ((v += ts), ...);
};

template<typename T, T ...ts>
inline std::decay_t<T> const sum_v = sum<T, ts...>::value;

template<typename T, typename ...ts>
struct get_first_type {
  using type = T;
};

template<typename T>
struct get_first_type<T> {
  using type = T;
};

int main() {

  if (auto ret = foo<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>()) {
    std::cout << "return value: " << *ret;
  } else {
    //error handle
    std::cout << "error handle\n";
  }

  std::cout << "\nsum = " << sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value;
  std::cout << "\nsum_t = " << sum_v<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>;
}