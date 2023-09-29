//
// Created by ozcom on 2023/9/28.
//

/**
 *
 * shared_ptr
 * 1、内存共享
 * 2、需要额外资源占用
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

static void init_shared_ptr() {

  {
    std::shared_ptr<Car> sp1{new Car{1}};
    sp1->run();
  }

  {
    std::shared_ptr<Car> sp2 = std::make_shared<Car>(2);
    sp2->run();

  }

  {
    std::shared_ptr<Car> sp3 = std::make_shared<Car>(3);
    sp3->run();
    std::cout << "sp3: use_count=" << sp3.use_count() << std::endl;

    std::shared_ptr<Car> sp4{sp3};
    sp4->run();
    std::cout << "sp3: use_count=" << sp3.use_count() << std::endl;
    std::cout << "sp4: use_count=" << sp4.use_count() << std::endl;

    std::shared_ptr<Car> sp5{sp3};
    sp5->run();
    std::cout << "sp3: use_count=" << sp3.use_count() << std::endl;
    std::cout << "sp4: use_count=" << sp4.use_count() << std::endl;
    std::cout << "sp5: use_count=" << sp5.use_count() << std::endl;

    sp5.reset();

    std::cout << "sp3: use_count=" << sp3.use_count() << std::endl;
    std::cout << "sp4: use_count=" << sp4.use_count() << std::endl;
    std::cout << "sp5: use_count=" << sp5.use_count() << std::endl;

  }

  {//数组管理
    std::shared_ptr<Car[]> sp6{([]() -> Car * {
      Car *cs = new Car[6];
      for (int i = 0; i < 6; i++) {
        cs[i].flag(6 * i);
      }
      return cs;
    })(), [](Car *p) {
      delete[] p;
    }};

  }

  std::cout << "init_shared_ptr exit" << std::endl;

}

static void reset_shared_ptr() {

  static std::shared_ptr<Car> sp7 = std::make_shared<Car>(7);
  sp7->run();
  std::cout << "sp7: use_count=" << sp7.use_count() << std::endl;
  std::shared_ptr<Car> sp8 = sp7;
  sp8->run();
  std::cout << "sp8: use_count=" << sp8.use_count() << std::endl;
  std::shared_ptr<Car> sp9{sp7};
  sp9->run();
  std::cout << "sp9: use_count=" << sp9.use_count() << std::endl;
  std::shared_ptr<Car> sp10{sp7};
  sp10->run();
  std::cout << "sp10: use_count=" << sp10.use_count() << std::endl;

  sp10.reset();
  std::cout << "sp10: use_count=" << sp10.use_count() << std::endl;

  sp7.reset(new Car{11});
  sp7->run();
  std::cout << "sp7: use_count=" << sp7.use_count() << std::endl;

  std::cout << "reset_shared_ptr exit" << std::endl;

}

int main() {

  init_shared_ptr();

  reset_shared_ptr();

}