//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <functional>

template<typename T>
constexpr void print(T t) {
  std::cout << t << std::endl;
}

template<typename F, typename... T>
constexpr void print(F f, T ...t) {
  std::cout << f << std::endl;
  std::cout << sizeof...(t) << std::endl;
  printf(t...);
}

template<typename T>
constexpr void print_tuple(T t) {
  std::cout << typeid(t).name() << "\tt" << "=" << t << std::endl;
}

template<typename Tuple, size_t N>
struct foreach_tuple {

  constexpr static void print(const Tuple &t) {
    print_tuple(std::get<N - 1>(t));
    foreach_tuple<Tuple, N - 1>::print(t);
  }

};

template<typename Tuple>
struct foreach_tuple<Tuple, 1> {

  constexpr static void print(const Tuple &t) {
    print_tuple(std::get<0>(t));
  }

};

int main() {

  std::pair<std::string, std::vector<std::string>> p1{"a", {"a1", "a2"}};
  const auto [x, y] = p1;
  const auto &[f, s] = p1;
  printf("{&x=%p, &y=%p}\n", &x, &y);
  printf("{&f=%p, &s=%p}\n", &f, &s);
  printf("{&p1.first=%p, &p1.second=%p}\n", &p1.first, &p1.second);


  std::tuple<int, bool, float, std::string> t1;
  t1 = std::make_tuple(1, false, 0.5f, "abc");
  std::tuple<int, bool, float, std::string> t2;
  t2 = std::make_tuple(2, false, 1.5f, "def");
  std::cout << std::tuple_size<decltype(t1)>::value << std::endl;
  
  foreach_tuple<decltype(t1), std::tuple_size<decltype(t1)>::value>::print(t1);
  foreach_tuple<decltype(t2), std::tuple_size<decltype(t2)>::value>::print(t2);

}