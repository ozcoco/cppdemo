//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

/*
 * c++17模板自动推导
 *  自己创建的class需要自定义推导引导
 *
 * */

template<size_t N, typename T, typename ...Args>
class Bar {
 public:
  explicit Bar(Args const ... args) : arr(args...) {
    std::cout << "模板参数构造" << std::endl;
  }

  constexpr size_t size() {
    return N;
  }

  friend std::ostream &operator<<(std::ostream &os, const Bar &bar) {
    os << "arr: [";
    for (auto &&v : bar.arr) {
      os << " " << v;
    }
    os << " ]";
    return os;
  }

 private:
  T arr[N];

};

/*
* 推导定义
* */
template<typename ...Args_>
explicit Bar(Args_ const ... args) -> Bar<sizeof...(args), std::common_type_t<Args_...>, Args_...>;

//
//template<size_t N, typename T, T ...Args>
//class Foo {
// public:
//
//  explicit Foo( ) {
//    std::cout << "模板参数构造" << std::endl;
//  }
//
//  constexpr size_t size() {
//    return N;
//  }
//
//  friend std::ostream &operator<<(std::ostream &os, const Foo &bar) {
//    os << "arr: [";
//    for (auto &&v : bar.arr) {
//      os << " " << v;
//    }
//    os << " ]";
//    return os;
//  }
//
// private:
//  T arr[N]{Args...};
//
//};
//
//template<typename ...Args_>
//explicit Foo(Args_ ... args) -> Foo<sizeof...(args), std::common_type_t<Args_...>, args...>;

int main() {

  Bar b{1, 2};
  std::cout << b << "\n";

//  Foo f{1, 4, 7, 9, 2};

}