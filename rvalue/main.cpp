//
// Created by ozcom on 2023/9/28.
//

/**
 *
 * 如何判断右值
 * 1、右值实例不能取地址
 * 2、
 *
 * **/

#include <iostream>
#include <string>

class Car {
 public:
  Car() = default;

  explicit Car(int flag) : flag_(flag) {
    std::cout << flag_ << "--->" << "init" << std::endl;
  }

  Car(const Car &&rl) noexcept {
    std::cout << flag_ << "--->" << "copy init" << std::endl;
  }

  Car(Car &&rv) noexcept {
    std::cout << flag_ << "--->" << "move init" << std::endl;
  }

  Car &operator=(const Car &rl) noexcept {
    std::cout << flag_ << "--->" << "copy assign" << std::endl;
    return *this;
  }

  Car &operator=(Car &&rv) noexcept {
    std::cout << flag_ << "--->" << "move assign" << std::endl;
    return *this;
  }

  virtual ~Car() {
    std::cout << flag_ << "--->" << "deinit" << std::endl;
  }

  virtual void run() {
    std::cout << flag_ << "--->" << "run" << std::endl;
  }

  [[nodiscard]] int flag() const {
    return flag_;
  }

 private:
  int flag_{};
};

static Car return_car() {
  Car o{1};
  return o;
}

int main() {

  Car car1{return_car()};
  car1.run();

  Car car2{2};
  car2 = return_car();
  car2.run();

  car2 = car1; //左值

  car2 = std::forward<Car>(car1); //右值

  car2 = std::move(car1); //右值

  car2 = static_cast<Car &&>(car1); //右值

  car2 = Car{3};  //右值

//  Car *car4 = &Car{4}; //编译失败

}