//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

inline auto call(...) {
  std::cout << "大保底" << "\n";
}

template<typename T, typename F>
constexpr
auto call(T t, F f) -> decltype((t.*f)()) {
  std::cout << "call 1" << "\n";
  return (t.*f)();
}

template<typename T, typename F>
constexpr
auto call(T t, F f) -> decltype((t->*f)()) {
  std::cout << "call 2" << "\n";
  return (t->*f)();
}

struct A {
  inline void print() const {
    std::cout << "hello A" << "\n";
  }
};


//------------------------------------------------------

template<bool, typename T>
struct enable_if {
  using type = T;
};

template<typename T>
struct enable_if<false, T> {};

auto foo(...) {
  std::cout << "大保底" << "\n";
}

template<typename T>
constexpr
typename enable_if<std::is_same_v<T, int>, T>::type foo(T v) {
  std::cout << "T type int" << "\n";
  return v;
}

template<typename T>
constexpr
typename enable_if<std::is_same_v<T, double>, T>::type foo(T v) {
  std::cout << "T type double" << "\n";
  return v;
}

//------------------------------------------------------

template<typename T>
constexpr
enable_if<std::is_integral_v<T>, bool>::type is_odd(T t) {
  std::cout << "is_odd: T type int" << "\n";
  return bool(t % 2);
}


//------------------------------------------------------

template<typename, typename>
struct has_x : std::false_type {};

template<typename T>
struct has_x<T, decltype(T::x)> : std::true_type {};

template<typename T, typename C>
inline constexpr bool has_x_v = has_x<T, C>::value;

struct F {
  int x;
};

struct E {
  double x;
};


//------------------------------------------------------

template<typename ... Types>
using void_t = void;

template<typename, typename = void_t<>>
struct has_type_member : std::false_type {};

template<typename T>
struct has_type_member<T, void_t<typename T::type>> : std::true_type {};

struct S {
  using type = int;
};

struct S2 {
};

int main() {

  A a{};
  call(a, &A::print);
  call(&a, &A::print);
  call(1, 2);

  printf("---------------------------------------------------------\n");
  foo(1);
  foo(0.02);
  foo();

  printf("---------------------------------------------------------\n");
  is_odd(1);
//  is_odd(0.1); //error

  printf("---------------------------------------------------------\n");
  constexpr auto f_has = has_x_v<F, double>;
  std::cout << "f_has=" << f_has << "\n";
  constexpr auto ff_has = has_x_v<F, int>;
  std::cout << "b_has=" << ff_has << "\n";

  constexpr auto e_has = has_x_v<E, double>;
  std::cout << "e_has=" << e_has << "\n";
  constexpr auto ee_has = has_x_v<E, int>;
  std::cout << "e_has=" << ee_has << "\n";

  printf("---------------------------------------------------------\n");

  constexpr auto s_has = has_type_member<S>::value;
  std::cout << "s_has=" << s_has << "\n";
  constexpr auto s2_has = has_type_member<S2>::value;
  std::cout << "s2_has=" << s2_has << "\n";

}