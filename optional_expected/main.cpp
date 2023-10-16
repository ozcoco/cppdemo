//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <optional>
#include <expected>
#include <string>

/*
 * 有状态的返回值
 *  std::optional 异常值只能为std::null_opt
 *  std::expected 可自定义异常值
 * */

enum class RES_ERR_CODE : unsigned char {
  E1 = 0x0f, E2, E3, E4, E5
};

static constexpr
std::optional<std::string> optional_test(const bool _cond) {
  if (_cond)
    return "abc";
  return std::nullopt;
}

static constexpr
std::expected<std::string, RES_ERR_CODE> expected_test(const int _cond) {
  if (_cond < 0)
    return std::unexpected{RES_ERR_CODE::E1};
  else if (_cond == 0)
    return std::unexpected{RES_ERR_CODE::E2};
  else if (_cond > 0xff)
    return std::unexpected{RES_ERR_CODE::E3};
  return "1234567890";
}

int main() {
  {
    std::cout << "optional-------------------------------------------------------" << std::endl;

    auto &&res = optional_test(true);
    if (res.has_value()) {
      std::cout << res.value() << std::endl;
    } else {
      //错误状态处理
      std::cout << "res error handle" << std::endl;
    }

    auto &&res1 = optional_test(false);
    try {
      auto &s = res1.value();
      std::cout << "res1.value=" << s << std::endl;
    } catch (const std::bad_optional_access &e) {
      //错误状态处理
      std::cout << "res1 error handle" << std::endl;
    }

    std::cout << "res1.value_or=" << optional_test(false).value_or("xxx") << std::endl;
    std::cout << "res1.value_or=" << optional_test(true).value_or("xxx") << std::endl;

    if (auto res2 = optional_test(false)) {
      std::cout << "*res2=" << *res2 << std::endl;
    } else {
      //错误状态处理
      std::cout << "res2 error handle" << std::endl;
    }

  }

  {
    std::cout << "expected-------------------------------------------------------" << std::endl;

    auto res = expected_test(0x1f);
    if (res.has_value()) {
      std::cout << res.value() << std::endl;
    } else {
      //错误状态处理
      std::cout << "res error handle , error code: " << static_cast<int>(res.error()) << std::endl;
    }

    auto res1 = expected_test(-1);
    try {
      auto &s = res1.value();
      std::cout << "res1.value=" << s << std::endl;
    } catch (const std::bad_expected_access<RES_ERR_CODE> &e) {
      //错误状态处理
      std::cout << "res1 error handle" << e.what() << ", error code: " << static_cast<int>(e.error()) << std::endl;
    }

    std::cout << "res1.value_or=" << expected_test(0xfff).value_or("xxx") << std::endl;
    std::cout << "res1.value_or=" << expected_test(0x2f).value_or("xxx") << std::endl;

    if (auto res2 = expected_test(0xfff)) {
      std::cout << "*res2=" << *res2 << std::endl;
    } else {
      //错误状态处理
      std::cout << "res2 error handle, error code: " << static_cast<int>(res.error()) << std::endl;
    }

  }

}