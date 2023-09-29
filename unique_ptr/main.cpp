//
// Created by ozcom on 2023/9/28.
//

/**
 *
 * unique_ptr
 * 1、独享智能指针
 * 2、0额外资源占用
 *
 *  推荐尽可能的在可用的地方使用
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

/**
 *
 * 初始化unique_ptr
 *
 * **/

static std::unique_ptr<Car> return_unique_ptr() {
  std::unique_ptr<Car> ptr{new Car{5}};
  return ptr;
}

static void init_unique_ptr() {

  {
    std::unique_ptr<Car> up1{new Car{1}}; //初始化
    up1->run();
  }

  {
    std::unique_ptr<Car> up2 = std::make_unique<Car>(2); //初始化
    (*up2).run();
  }

  {
    auto mallocCar = []() -> Car * {
      return new Car{3};
    };
    auto freeCar = [](Car *p) {
      std::cout << p->flag() << "--->" << "freeCar" << std::endl;
      delete p;
    };
    std::unique_ptr<Car, decltype(freeCar)> up3{new Car{3}, freeCar}; //初始化
    up3->run();
    std::cout << "up3   exit" << std::endl;
  }

  {
    std::unique_ptr<Car[], std::function<void(Car *)>> up4{
        new Car[5],
        [](Car *p) {
          std::cout << "--->up4 free" << std::endl;
          delete[] p;
        }
    }; //初始化
    up4[0].run();
    std::cout << "up4 exit" << std::endl;
  }

  {
    auto up5{return_unique_ptr()};
    up5->run();
  }

  {
    std::unique_ptr<Car[]> up6 = std::make_unique<Car[]>(5);
    up6[4].run();
  }

  std::cout << "init_unique_ptr exit" << std::endl;

}

/**
 *
 *  reset, release
 *
 * **/

static void reset_unique_ptr() {

  std::unique_ptr<Car> up7 = std::make_unique<Car>(7);
  up7->run();

  std::unique_ptr<Car> up8{up7.release()};
//    up7->run();
  up8->run();

  std::unique_ptr<Car> up9 = std::make_unique<Car>(9);
  up7.swap(up9);
  up7->run();
//    up9->run();

  up9 = std::make_unique<Car>(10);
  up9->run();

  std::unique_ptr<Car> up11 = std::make_unique<Car>(11);
  up11->run();
  up11.reset(up9.get());
  up11->run();

  up11.reset();
//  up11->run();

  std::cout << "reset_unique_ptr exit" << std::endl;
}

int main() {

  init_unique_ptr();

  reset_unique_ptr();

}