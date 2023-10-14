//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <tuple>
#include <string>
#include <array>
#include <map>

int main() {

  std::tuple<char, int, double, float, bool, std::string> t{'a', 123, 0.123, 0.123f, false, "123"};
  std::cout << "get type-----------------------------------------" << std::endl;
  std::cout << get<std::string>(t) << std::endl;
  std::cout << get<bool>(t) << std::endl;
  std::cout << get<float>(t) << std::endl;
  std::cout << get<double>(t) << std::endl;
  std::cout << get<int>(t) << std::endl;
  std::cout << get<char>(t) << std::endl;
  std::cout << "get index-----------------------------------------" << std::endl;
  std::cout << get<0>(t) << std::endl;
  std::cout << get<1>(t) << std::endl;
  std::cout << get<2>(t) << std::endl;
  std::cout << get<3>(t) << std::endl;
  std::cout << get<4>(t) << std::endl;
  std::cout << get<5>(t) << std::endl;

  {
    std::cout << "get tie-----------------------------------------" << std::endl;
    char c;
    int n;
    double d;
    float f;
    bool b;
    std::string s;
    std::tie(c, n, d, f, b, s) = t;
    std::cout << c << std::endl;
    std::cout << n << std::endl;
    std::cout << d << std::endl;
    std::cout << f << std::endl;
    std::cout << b << std::endl;
    std::cout << s << std::endl;
  }

  {
    std::cout << "get struct binding-----------------------------------------" << std::endl;
    auto &[c, n, d, f, b, s] = t;
    std::cout << c << std::endl;
    std::cout << n << std::endl;
    std::cout << d << std::endl;
    std::cout << f << std::endl;
    std::cout << b << std::endl;
    std::cout << s << std::endl;
  }

  {
    std::cout << "get tie-----------------------------------------" << std::endl;
    std::pair<char, int> p{'a', 123};
    char c;
    int n;
    std::tie(c, n) = p;
    std::cout << c << std::endl;
    std::cout << n << std::endl;
  }

  {
    std::cout << "get struct binding-----------------------------------------" << std::endl;
    std::pair<char, int> p{'a', 123};
    auto &[c, n] = p;
    std::cout << c << std::endl;
    std::cout << n << std::endl;
  }

  {
    std::cout << "get struct binding it map-----------------------------------------" << std::endl;
    std::map<int, std::string> m{
        {1, "123"}, {2, "456"}
    };
    printf("std::map<int, std::string>::value_type is std::pair<>\n");

    for (auto &[k, v] : m) {
      printf("{%d, %s}\n", k, v.c_str());
    }
  }

}