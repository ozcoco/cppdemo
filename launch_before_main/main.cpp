#include <iostream>

/**
 *
 * 如何在main函数之前执行代码？
 *  可以使用初始化全局变量实现
 *
 * **/

struct Data {
  static void print();
};

class Feature {

  friend struct Data;

 public:
  Feature() {
    std::cout << flag_ << "--->Feature()" << std::endl;
  }

  explicit Feature(int flag) : flag_(flag) {
    std::cout << flag_ << "--->explicit Feature(int flag)" << std::endl;
  }

  Feature(const Feature &rf) {
    std::cout << flag_ << "--->Feature(const Feature &rf)" << std::endl;
  }

  Feature(Feature &&rf) noexcept {
    std::cout << flag_ << "--->Feature(Feature &&rf) noexcept" << std::endl;
  }

  Feature &operator=(const Feature &rf) {
    std::cout << flag_ << "--->Feature &operator=(const Feature &rf)" << std::endl;
    return *this;
  }

  Feature &operator=(Feature &&rf) noexcept {
    std::cout << flag_ << "--->Feature &operator=(Feature &&rf) noexcept" << std::endl;
    return *this;
  }

  virtual ~Feature() {
    std::cout << flag_ << "--->virtual ~Feature()" << std::endl;
  }

  friend std::ostream &operator<<(std::ostream &os, const Feature &feature) noexcept {
    os << "flag_: " << feature.flag_;
    return os;
  }

 private:
  int flag_{};
};

void Data::print() {
  std::cout << "Hello, World!" << "\t" << "Feature().flag_=" << Feature().flag_ << std::endl;
}

static Feature ft = Feature();

static Feature launch() {
  return Feature(5);
}
static Feature ft5 = launch();

static Feature launch2() {
  Feature ft6(6);
  std::cout << ft6 << std::endl;
  return ft6;
}
static Feature ft6 = launch2();

static Feature launch3() {
  Feature ft7(7);
  std::cout << ft7 << std::endl;
  return ft7;
}

static Feature launch4() {
  Feature ft8(8);
  std::cout << ft8 << std::endl;
  return ft8;
}

static Feature &launch5() {
  Feature ft9(9);
  std::cout << ft9 << std::endl;
  return dynamic_cast<Feature &>(ft9);
}

int main() {

  std::cout << "Hello, World!" << std::endl;

  ft = Feature(1);

  Feature ft2{2};

  auto &&ft3 = Feature{3}; //延长右值的生命周期

  ft2 = ft3;

  ft2 = launch3();

  Feature ft8(launch4());

  Feature *ft9 = &launch5(); //已被回收
  std::cout << *ft9 << std::endl;

  std::cout << "Exit" << std::endl;

  return 0;
}
