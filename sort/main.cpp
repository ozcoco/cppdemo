//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <span>

template<typename T, std::size_t N>
constexpr
void sort(std::span<T, N> _span) {
  T tmp{};
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (_span[i] > _span[j]) {
        tmp = _span[j];
        _span[j] = _span[i];
        _span[i] = tmp;
      }
    }
  }
}

int main() {

  int arr[]{1, 7, 9, 23, 43, 76574, 3, 9, 99, 6, 77, 899, 356};
  sort(std::span{arr});
  for (auto const &v : arr) {
    std::cout << v << "\t";
  }

}