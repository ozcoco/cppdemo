//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <any>
#include <string>
#include <vector>
#include <variant>

using namespace std::literals::string_literals;

template<typename T>
struct Any {

  using value_type = T;

  constexpr Any(const T &&t) : _t_(t) {}

  constexpr operator T() {
    return _t_;
  }

  value_type _t_;
};

int main() {

  std::any a = 123;
  std::cout << "int size:" << sizeof(int) << std::endl;
  std::cout << "a size:" << sizeof a << std::endl;
  std::cout << "std::any size:" << sizeof(std::any) << std::endl;
  std::variant<bool, char, unsigned char, int, unsigned int, long int, unsigned long int, std::string, Any<int>>
      i1 = 123;
  std::cout << "i1 size:" << sizeof(i1) << std::endl;
  std::cout << "std::variant<int> size:" << sizeof(decltype(i1)) << std::endl;
  std::cout << "a:" << typeid(a).name() << std::endl;
  std::cout << "a:" << a.type().name() << std::endl;
  std::cout << "a =" << std::any_cast<int>(a) << std::endl;

  Any y1 = 123;
  Any s1 = std::string{"123"};

  int yy1 = y1;
  std::string ss1 = s1;
  std::cout << "yy1 =" << yy1 << std::endl;

  std::vector<std::any> vec{false, 'a', 0.1f, 0.123, 2, 3U, 4L, 5UL, "12345"s};
  for (auto &&e : vec) {

    if (auto *p = std::any_cast<bool>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<char>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<float>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<double>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<int>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<unsigned int>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<long int>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<unsigned long int>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<std::string>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;

  }

}