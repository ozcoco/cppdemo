//
// Created by ozcom on 2023/9/28.
//

/**
 *
 * weak_ptr
 * 1、内存观察者
 * 2、0额外资源占用
 * 3、需要与shared_ptr配合使用
 *
 * **/

#include <iostream>
#include <memory>
#include <functional>

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

  void flag(int flag) {
    flag_ = flag;
  }

 private:
  int flag_{};
};

static void init_weak_ptr() {

  std::shared_ptr<Car> sp = std::make_shared<Car>(1);
  sp->run();
  std::cout << "sp use_count=" << sp.use_count() << std::endl;

  std::weak_ptr<Car> wp{sp};
  {

    if (std::shared_ptr<Car> spt = wp.lock()) {
      spt->run();
      std::cout << "spt use_count=" << spt.use_count() << std::endl;
    } else {
      std::cout << "spt use_count=" << std::endl;
    }

    std::cout << "1 exit" << std::endl;
  }

  {
    sp.reset();

    std::cout << "wp use_count=" << wp.use_count() << std::endl;

    if (std::shared_ptr<Car> spt = wp.lock()) {
      spt->run();
      std::cout << "spt use_count=" << spt.use_count() << std::endl;
    } else {
      std::cout << "gw is expired" << std::endl;
    }

  }

}

int main() {

  init_weak_ptr();

}