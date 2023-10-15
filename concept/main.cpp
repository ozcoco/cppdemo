//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <concepts>

/*
 * concept定义概念
 * requires定义约束
 *    可约束模板参数
 *    可约束函数行为
 *
 * */
template<typename T, typename U>
concept Addable1 = std::is_same_v<T, int> && std::is_same_v<U, int> /*定义类型约束*/
    && requires(T t, U u){
      t + u; /*定义行为约束*/
      { t + u } -> std::same_as<int>;  //约束行为的结果
    };

template<typename T, typename U>
concept Addable2 = requires(T t, U u){
  requires std::is_same_v<T, int>; /*定义类型约束*/
  requires std::is_same_v<U, int>;
  t + u; /*定义行为约束*/
  { t + u } -> std::same_as<int>;  //约束行为的结果
};

template<typename T, typename U>
requires Addable1<T, U>
auto add(T t, U u) {
  return t + u;
}

template<typename T, typename U>
auto add2(T t, U u) requires Addable1<T, U> {
  return t + u;
}

template<typename T, typename U>
requires std::is_same_v<T, int> && std::is_same_v<U, int> /*定义类型约束*/
    && requires(T t, U u){
      t + u; /*定义行为约束*/
      { t + u } -> std::same_as<int>;  //约束行为的结果
    }
auto add3(T t, U u) {
  return t + u;
}

template<typename T, typename U>
auto add5(T t, U u) requires Addable2<T, U> {
  return t + u;
}

template<typename T>
concept Inter1= std::is_same<T, int>::value;

Inter1 auto add4(Inter1 auto t, Inter1 auto u) {
  return t + u;
}

auto add(...) {
  return 0;
}

int main() {

  std::cout << add(1, 0) << std::endl;
  std::cout << add(0.4, 0) << std::endl;
  std::cout << add("0.4", "0") << std::endl;

}