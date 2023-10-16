//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <span>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

//高效便捷访问连续内存的实例对象

template<typename T, std::size_t N>
constexpr void for_each_span(std::span<T, N> _span) {
  std::for_each(_span.begin(), _span.end(), [](auto &&e) {
    std::cout << e << "\t";
  });
  std::cout << "\n";
}

constexpr void for_each_span(auto &&_span) {
  std::for_each(_span.begin(), _span.end(), [](auto &&e) {
    std::cout << e << "\t";
  });
  std::cout << "\n";
}

int main() {

  std::array<int, 6> arr{1, 2, 3, 4, 5, 6};
  for_each_span(std::span{arr});

  std::vector<std::string> vec{"123", "abc", "ABC", "456", "def", "DEF"};
  for_each_span(std::span{vec});

  constexpr char const *const carr[]{"11", "22", "33", "44", "55","66l"};
  for_each_span(std::span{carr});

}