//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <utility>
#include <functional>
#include <string_view>
#include <tuple>

using namespace std::literals::string_literals;

/*
 *
 * 类模板 std::integer_sequence 表示一个编译时的整数序列。在用作函数模板的实参时，能推导参数包 Ints 并将它用于包展开
 * 1、可以定义一个编译时整数序列
 * 2、包展开可用作元函数实参
 *
 * */

template<typename T, T... ts>
void print_int_seq(std::string_view _name, std::integer_sequence<T, ts...> _seq) {
  std::cout << _name << "= [ ";
  ((std::cout << ts << "\t"), ...); //types包展开
  std::cout << " ]\n";
}

template<typename ...tp, typename T, T... ts>
void print_tuple(std::string_view _name, std::tuple<tp...> _tp, std::integer_sequence<T, ts...> _seq) {
  std::cout << _name << "= [ ";
  ((std::cout << std::get<ts>(_tp) << "\t"), ...);
  std::cout << " ]\n";
}

template<typename ...tp>
void print_tuple(std::string_view _name, std::tuple<tp...> _tuple) {
  print_tuple(_name, _tuple, std::index_sequence_for<tp...>{});
}

template<typename ...tp>
void print_tuple2(std::string_view _name, std::tuple<tp...> _tuple) {
  std::cout << _name << "= [ ";
  ((std::cout << std::get<tp>(_tuple) << "\t"), ...);
  std::cout << " ]\n";
}

int main() {

  std::integer_sequence<unsigned int, 3, 46, 3, 9, 22> i_seq1{};
  std::make_integer_sequence<int, 3> i_seq2{};
  std::make_index_sequence<10> idx_seq{};
  std::index_sequence_for<>{};
  std::index_sequence<1, 2, 3, 4, 5, 6> i_seq3{}; //<=>std::integer_sequence<std::size_t, 3, 46, 3, 9, 22>{}

  print_int_seq("i_seq1", i_seq1);
  print_int_seq("i_seq2", i_seq2);
  print_int_seq("idx_seq", idx_seq);
  print_int_seq("index_sequence_for", std::index_sequence_for<float, std::iostream, char>{});

  //遍历元组
  std::apply([](auto &&arg, auto &&...args) {

    std::cout << "[ " << arg;
    ((std::cout << ", " << args), ...);
    std::cout << " ]\n";

  }, std::tuple{true, 'a', 123, 0.123, 0.987f, "abcdef"s});

  std::tuple t1{true, 'a', 123, 0.123, 0.987f, "abcdef"s, 1234567890};
  print_tuple("print_tuple t1", t1);
//  print_tuple2("print_tuple2 t1", t1); //error, 无法使用重复数据类型

  std::tuple t2{true, 'a', 123, 0.123, 0.987f, "abcdef"s};
  print_tuple2("print_tuple2 t2", t2);

}