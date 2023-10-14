//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <variant>
#include <string>

union Variant {
  char c;
  int n;
  double d;
};

//可变数据类型，共享内存，同一时间只存在一种数据类型
static void union_feature() {

  Variant v{};
  v.d = 0.4;
  std::cout << "sizeof(v)=" << sizeof v << std::endl;
  std::cout << "v.c=" << v.c << std::endl;
  std::cout << "v.n=" << v.n << std::endl;
  std::cout << "v.d=" << v.d << std::endl;

  v.c = 'a';
  std::cout << "v.c=" << v.c << std::endl;

  v.n = 54321;
  std::cout << "v.c=" << v.n << std::endl;

}

//可变数据类型
static void variant_feature() {

  try {

    static std::variant<char, int, double, float, bool, std::string> v{false};
    std::cout << "sizeof v = " << sizeof v << std::endl;
    v = "abc";
    std::cout << "v = " << get<std::string>(v) << std::endl;
    v = true;
    std::cout << "v = " << get<bool>(v) << std::endl;
    v = 0.33f;
    std::cout << "v = " << get<float>(v) << std::endl;
    v = 0.123;
    std::cout << "v = " << get<double>(v) << std::endl;
    v = 123;
    std::cout << "v = " << get<int>(v) << std::endl;
    v = 'a';
    std::cout << "v = " << get<char>(v) << std::endl;

    auto fnVariantPrint = [](auto &v)constexpr {

      if (auto *pV = std::get_if<std::string>(&v))
        std::cout << typeid(*pV).name() << " v = " << *pV << std::endl;

      if (auto *pV = std::get_if<bool>(&v))
        std::cout << typeid(*pV).name() << " v = " << *pV << std::endl;

      if (auto *pV = std::get_if<float>(&v))
        std::cout << typeid(*pV).name() << " v = " << *pV << std::endl;

      if (auto *pV = std::get_if<double>(&v))
        std::cout << typeid(*pV).name() << " v = " << *pV << std::endl;

      if (auto *pV = std::get_if<int>(&v))
        std::cout << typeid(*pV).name() << " v = " << *pV << std::endl;

      if (auto *pV = std::get_if<char>(&v))
        std::cout << typeid(*pV).name() << " v = " << *pV << std::endl;

    };

    v = 'x';
    fnVariantPrint(v);

  } catch (const std::bad_variant_access &e) {

    std::cout << e.what() << std::endl;

  }

}

int main() {

  union_feature();

  std::cout << "\n-------------------------------------------------------\n" << std::endl;

  variant_feature();

}