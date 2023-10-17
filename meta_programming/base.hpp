//
// Created by ozcom on 2023/10/17.
//

#ifndef CPP_FEATURE_DEMO_META_PROGRAMMING_BASE_HPP_
#define CPP_FEATURE_DEMO_META_PROGRAMMING_BASE_HPP_

#include <iostream>
#include <array>
#include <string>
#include <string_view>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;


//template<typename T>
//constexpr auto sqt(T t) -> decltype(t * t) {
//  return t * t;
//}

template<typename T>
constexpr auto sqt(T t) {
  return t * t;
}

template<auto v>
constexpr auto t1 = sqt(v);

template<typename T, typename U>
struct foo {
  foo(const T &&t, const U &&u) {}
  void operator()() {
    std::cout << "泛化版本" << std::endl;
  }
};

template<typename U>
struct foo<int, U> {
  foo(const int &t, const U &&u) {}
  void operator()() {
    std::cout << "偏特化版本" << std::endl;
  }
};

template<>
struct foo<int, char> {
  foo(const int &t, const char &u) {}
  void operator()() {
    std::cout << "全特化版本" << std::endl;
  }
};

template<typename T, typename U>
void my_print(T t, U u) {
  std::cout << "my_print泛化版本" << std::endl;
}

/*
 * 函数模板不支持偏特化
 * */
//template<typename U>
//void my_print<int, U>() {
//  std::cout << "my_print泛化版本" << std::endl;
//}


/*
 * 重新定义只有U模板参数my_print版本
 * 可达到偏特化效果
 * */
template<typename U>
void my_print(bool t, U u) {
  std::cout << "重新定义只有U模板参数my_print版本" << std::endl;
}

template<>
void my_print<int, std::string>(int t, std::string u) {
  std::cout << "my_print全特化版本" << std::endl;
}

template<typename T, std::size_t N>
constexpr std::size_t static_carr_size(T const (&)[N]) {
  return N;
}

void base_main() {

  constexpr auto v = t1<123>;
  std::cout << "v=" << v << "\n";

  foo<int, int>{1, 2}();
  foo<double, double>{2.0, 4.0}();
  foo<int, char>{123, 'a'}();
  foo{'b', 'a'}();
  foo{"123"s, "7584"s}();

  my_print<double, double>(4.0, 3.3);
  my_print<double>(4.0, 3.3);
  my_print<int, std::string>(4, "3.3"s);
  my_print<std::string>(true, "3.3"s);
  my_print(4.0, 3.3);
  my_print(4.0, 3.3);
  my_print(4, "3.3"s);
  my_print(true, "3.3"s);

  std::array arr{1231, 45, 67767};

  char carr[]{1, 2, 3, 4, 45, 5, 56, 6, 6, 4, 45, 34, 4};
  std::cout << "carr size: " << static_carr_size(carr) << "\n";
  std::cout << "carr size: " << static_carr_size({1, 2, 3, 4, 45, 4, 45, 34, 4}) << "\n";

}

#endif //CPP_FEATURE_DEMO_META_PROGRAMMING_BASE_HPP_
