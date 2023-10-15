# C++编程

------

## 基础

### 变量

#### 定义字符串数组

```c
const char *argv[] = {"test", "/tmp"};
int len = sizeof argv / sizeof argv[0]; //数组长度
```

## 异常处理

[[include]] <exception>

```c++
[[include]] <iostream>
[[include]] <exception>

class MyException : public std::exception {

public:

    inline explicit MyException(const char *_msg) noexcept : msg(_msg) {

    }

    [[nodiscard]] inline const char *getMsg() const noexcept {

        return msg.c_str();
    }

private:
    std::string msg;

};


int main() {

    try {

        printf("1234\n");

        throw MyException("11212421423");

    } catch (const MyException &ex) {

        printf("----->%s", ex.getMsg());

    }
    catch (...) {

        printf("finally");

    }

}
```

## 容器

### 常见问题

#### 对象切割

```c++
class Anim
{


public:
    Anim(int type, int age, std==string name, std==string desc) : type(type), age(age), name(std::move(name)),

                                                                  desc(std::move(desc)) {}

    virtual ~Anim()
    {

    }

    int getType() const
    {
        return type;
    }

    void setType(int type)
    {
        Anim::type = type;
    }

    int getAge() const
    {
        return age;
    }

    void setAge(int age)
    {
        Anim::age = age;
    }

    const std::string &getName() const
    {
        return name;
    }

    void setName(const std::string &name)
    {
        Anim::name = name;
    }

    const std::string &getDesc() const
    {
        return desc;
    }

    void setDesc(const std::string &desc)
    {
        Anim::desc = desc;
    }

    bool operator==(const Anim &rhs) const
    {
        return type == rhs.type &&
               age == rhs.age &&
               name == rhs.name &&
               desc == rhs.desc;
    }

    bool operator!=(const Anim &rhs) const
    {
        return !(rhs == *this);
    }

    bool operator<(const Anim &rhs) const
    {
        if (type < rhs.type)
            return true;
        if (rhs.type < type)
            return false;
        if (age < rhs.age)
            return true;
        if (rhs.age < age)
            return false;
        if (name < rhs.name)
            return true;
        if (rhs.name < name)
            return false;
        return desc < rhs.desc;
    }

    bool operator>(const Anim &rhs) const
    {
        return rhs < *this;
    }

    bool operator<=(const Anim &rhs) const
    {
        return !(rhs < *this);
    }

    bool operator>=(const Anim &rhs) const
    {
        return !(*this < rhs);
    }

    friend std==ostream &operator<<(std==ostream &os, const Anim &anim)
    {
        os << "type: " << anim.type << " age: " << anim.age << " name: " << anim.name << " desc: " << anim.desc;
        return os;
    }

private:
    int type;
    int age;
    std::string name;
    std::string desc;
};


class Dog : public Anim
{
public:
    Dog(int type, int age, const std==string &name, const std==string &desc, int color) : Anim(type, age, name, desc),
                                                                                          color(color) {}

    enum : int
    {
        RED = 0xff0000,
        GREEN = 0x00ff00,
        BLUE = 0x0000ff
    };

    enum class TYPE : unsigned int
    {
        RED = 0xff0000,
        GREEN = 0x00ff00,
        BLUE = 0x0000ff
    };

    int getColor() const
    {
        return color;
    }

    void setColor(int color)
    {
        Dog::color = color;
    }

private:
    int color;

};

[[include]] <vector>

void objectCut()
{
    using std::vector;

    vector<Anim> animVc;

[[ifdef]] __linux__

    printf("anim size:%lu\n dog size:%lu\n", sizeof(Anim &), sizeof(Dog &));

    __try
    {
        animVc.push_back(Dog(1, 12, "oneko", "Cat", 123456));

        Dog &dog2 = (Dog &) animVc.at(0);

        printf("color=%d\nname=%s", dog2.getColor(), dog2.getName().c_str());
    }
    __catch(std::bad_cast &ex)
    {
        printf("ERR:%s\n", ex.what());
    }
    __catch(std::bad_alloc &ex)
    {
        printf("ERR:%s\n", ex.what());
    }
    __catch(...)
    {
        printf("ERR:%s\n", std::current_exception().__cxa_exception_type()->name());
    }

[[elif]] WIN32

    using std;

    cout<<"windows"<<endl;

[[endif]]


}
```

结果：

anim size:80
 dog size:88
color=0
name=oneko
Process finished with exit code 0

## malloc与new

malloc无法创建对象仅分配内存空间，new创建对象且分配内存

free仅释放内存空间，delete销毁对象且释放内存空间

operator new()仅为malloc的包装调用，operator delete()仅为free的包装调用

```c++
//
// Created by Administrator on 2021/1/14.
//

[[include]] "class_new_malloc.h"
[[include]] <iostream>

using namespace std;

class MemTest
{
 public:
    inline MemTest()
        : i(10)
    {
        cout << "MemTest" << endl;
    }

    inline virtual ~MemTest()
    {
        cout << "~MemTest" << endl;
    }

    inline void info() const
    {
        cout << "info: " << i << endl;
    }

 private:
    int i;

};

static void test_new_class()
{

    MemTest* mt = new MemTest;

    mt->info();

}

static void test_malloc_class()
{

    MemTest* mt = static_cast<MemTest*>(malloc(sizeof(MemTest)));

    mt->info();

}

static void test_delete_class()
{

    MemTest* mt = new MemTest;
    mt->info();
    delete mt;
}

static void test_free_class()
{

    MemTest* mt = static_cast<MemTest*>(malloc(sizeof(MemTest)));
    mt->info();
    free(mt);

}

void test_class_new_malloc()
{

    test_new_class();
    cout << "----------------------------------------------------" << endl;
    test_malloc_class();
    cout << "----------------------------------------------------" << endl;
    test_delete_class();
    cout << "----------------------------------------------------" << endl;
    test_free_class();
    cout << "----------------------------------------------------" << endl;
}
```

```shell
MemTest
info: 10
----------------------------------------------------
info: 0
----------------------------------------------------
MemTest
info: 10
~MemTest
----------------------------------------------------
info: 0
----------------------------------------------------
```

## Reference&Object&Pointer

```c++
//
// Created by oz on 23-9-4.
//


/**
 *
 * 容器接收对象和指针的区别
 * 结论：
 * 1、容器存储多态对象时会发生对象分割
 * 2、容器存储多态对象应该存储其指针
 *
 *
 * **/

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <exception>

using String = std::string;

class Computer {

public:
    Computer() : Computer(0) {}

    explicit Computer(int flag)
            : Computer(flag, 0) {

    }

    Computer(int flag, int price)
            : Computer(flag, price, "") {

    }

    Computer(int flag, int price, String vendor)
            : Computer(flag, price, std::move(vendor), "") {

    }

    Computer(int flag, int price, String vendor, String desc)
            : flag_(flag), price_(price), vendor_(std::move(vendor)), desc_(std::move(desc)) {

    }


    [[nodiscard]] int getFlag() const {
        return flag_;
    }

    void setFlag(int flag) {
        flag_ = flag;
    }

    [[nodiscard]] int getPrice() const {
        return price_;
    }

    void setPrice(int price) {
        price_ = price;
    }

    [[nodiscard]] const String &getVendor() const {
        return vendor_;
    }

    void setVendor(const String &vendor) {
        vendor_ = vendor;
    }

    [[nodiscard]] const String &getDesc() const {
        return desc_;
    }

    void setDesc(const String &desc) {
        desc_ = desc;
    }

    friend std::ostream &operator<<(std::ostream &os, const Computer &computer) {
        os << "flag_: " << computer.flag_ << " price_: " << computer.price_ << " vendor_: " << computer.vendor_
           << " desc_: " << computer.desc_;
        return os;
    }

    virtual void start() {}

    virtual void stop() {}

protected:
    virtual void scale() {}

private:
    int flag_;
    int price_;
    String vendor_;
    String desc_;

};

enum class Input : unsigned int {
    Common = 0xffff1111,
    Choco,
    Machine
};

class Notebook : public Computer {
    using super = Computer;

public:
    Notebook(int flag, int price, String vendor, String desc, Input input)
            : super(flag, price, std::move(vendor), std::move(desc)), input_(input) {

    }

    void start() override {

    }

    void stop() override {

    }

    void scale() override {

    }

    friend std::ostream &operator<<(std::ostream &os, const Notebook &notebook) {
        os << static_cast<const Computer &>(notebook) << " input_: " << static_cast<unsigned int >(notebook.input_);
        return os;
    }

private:
    Input input_;

};


int main() try {

    Notebook nb(1, 35, "机械师", "机械师笔记本电脑", Input::Choco);
    std::cout << nb << std::endl;

    Notebook &&nb2 = Notebook(3, 200, "惠普", "惠普笔记本电脑", Input::Choco);

    std::vector<Computer> vec{Computer(2, 100, "联想", "联想笔记本电脑")};
    vec.push_back(nb);
    vec.push_back(nb2);

    for (auto &r: vec) {
        std::cout << r << std::endl;
    }

    auto &notebook = reinterpret_cast<Notebook &>(vec[1]);
    std::cout << notebook << std::endl;

} catch (...) {

    std::cout << "exception: " << std::current_exception().__cxa_exception_type()->name() << std::endl;
}


##output
/home/oz/WK/cpp/test_oop/cmake-build-debug/reference_object_pointer/test-reference_object_pointer
flag_: 1 price_: 35 vendor_: 机械师 desc_: 机械师笔记本电脑 input_: 4294906130
flag_: 2 price_: 100 vendor_: 联想 desc_: 联想笔记本电脑
flag_: 1 price_: 35 vendor_: 机械师 desc_: 机械师笔记本电脑
flag_: 3 price_: 200 vendor_: 惠普 desc_: 惠普笔记本电脑
flag_: 1 price_: 35 vendor_: 机械师 desc_: 机械师笔记本电脑 input_: 4245949552

Process finished with exit code 0
```

## nullptr

```c++

```

# C++20

## concept

```c++
//
// Created by Administrator on 2020/9/30.
//

[[include]] "Concepts.h"
[[include]] <iostream>

using namespace cpp20;

/**********************************************************************/
//                                concept basic
/**********************************************************************/


template<typename T>
requires (sizeof(T) < 8)
class A
{
 public:
    inline void do_something()
    {
        std==cout << "------> do_something" << std==endl;
    }
};

template<typename T>
concept SizeLessThan8 = sizeof(T) < 8;

template<SizeLessThan8 T>
class B
{
 public:
    inline void do_something()
    {
        std==cout << "------> do_something" << std==endl;
    }
};

struct TestType
{
    int a;
    int b;

    inline void do_something()
    {
        std==cout << "------> do_something" << std==endl;
    }
};

template<typename T, unsigned N>
concept SizeLessThan = sizeof(T) < N;

template<SizeLessThan<8> T>
class C
{
 public:
    inline void do_something()
    {
        std==cout << "------> do_something" << std==endl;
    }
};

template<typename T>
concept CanDoSomething =
requires(T v){ v.do_something(); };

template<CanDoSomething T>
class D
{
 public:
    inline void do_something()
    {
        std==cout << "------> do_something" << std==endl;
    }
};

static void concept_basic()
{

    A<TestType> a1;

    a1.do_something();

    D<TestType> d1;

    d1.do_something();
}

void concepts::test_concepts()
{
    concept_basic();
}
```

## ranges

```c++
//
// Created by Administrator on 2020/9/30.
//

[[include]] "Ranges.h"
[[include]] <iostream>
[[include]] <vector>
[[include]] <ranges>

using namespace cpp20;

/**********************************************************************/
//                      ranges basic
/**********************************************************************/


static void ranges_basic()
{
   auto ints = std==views==iota(0, 10);
   auto even = [](int i)
   { return 0 == i % 2; };
   auto square = [](int i)
   { return i * i; };

   for (int i : ints | std==views==filter(even) | std==views==transform(square))
      std::cout << i << ' ';
}

void ranges::test_ranges()
{
   ranges_basic();
}
```

# Feature

### const

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

static void const_pointer_var() {

  int a = 1;
  int const *ap = &a;   // *ap r, ap rw
  printf("a=%d\n", a);
  printf("*ap=%d\n", *ap);
  printf("ap=%p\n", ap);
  printf("&ap=%p\n", &ap);
  printf("------------------------------------------------\n");

  int a2 = 2;
  ap = &a2;
//  *ap = 22;
  printf("a2=%d\n", a2);
  printf("*ap=%d\n", *ap);
  printf("ap=%p\n", ap);
  printf("&ap=%p\n", &ap);
  printf("------------------------------------------------\n");

  int a3 = 2;
  int const *const ap2 = &a3; //*ap2 r, ap2 r
  printf("a3=%d\n", a3);
  printf("*ap2=%d\n", *ap2);
  printf("ap2=%p\n", ap2);
  printf("&ap2=%p\n", &ap2);
  printf("------------------------------------------------\n");

  int a4 = 4;
//  ap2 = &a4;
//  *ap2 = 5;
  printf("------------------------------------------------\n");

  int a5 = 5;
  int *const ap3 = &a5; //*ap3 rw, ap3 r
  printf("a5=%d\n", a5);
  printf("*ap3=%d\n", *ap3);
  printf("ap3=%p\n", ap3);
  printf("&ap3=%p\n", &ap3);
  printf("------------------------------------------------\n");

//  ap3 = nullptr;
  *ap3 = 6;
  printf("a5=%d\n", a5);
  printf("*ap3=%d\n", *ap3);
  printf("ap3=%p\n", ap3);
  printf("&ap3=%p\n", &ap3);
  printf("------------------------------------------------\n");

  int a7 = 7;
  int *ap7 = &a7;
  printf("a7=%d\n", a7);
  printf("*ap7=%d\n", *ap7);
  printf("&a7=%p\n", &a7);
  printf("ap7=%p\n", ap7);
  printf("&ap7=%p\n", &ap7);

  int a8 = 8;
  ap7 = &a8;
  printf("a8=%d\n", a8);
  printf("*ap7=%d\n", *ap7);
  printf("&a8=%p\n", &a8);
  printf("ap7=%p\n", ap7);
  printf("&ap7=%p\n", &ap7);

  *ap7 = 9;
  printf("a8=%d\n", a8);
  printf("*ap7=%d\n", *ap7);
  printf("&a8=%p\n", &a8);
  printf("ap7=%p\n", ap7);
  printf("&ap7=%p\n", &ap7);

  printf("------------------------------------------------\n");

}


int main() {

  const_pointer_var();

}




##output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\const\test-const.exe
a=1
*ap=1
ap=000000b4d81ffdb8
&ap=000000b4d81ffdb0
------------------------------------------------
a2=2
*ap=2
ap=000000b4d81ffdac
&ap=000000b4d81ffdb0
------------------------------------------------
a3=2
*ap2=2
ap2=000000b4d81ffda8
&ap2=000000b4d81ffda0
------------------------------------------------
------------------------------------------------
a5=5
*ap3=5
ap3=000000b4d81ffd9c
&ap3=000000b4d81ffd90
------------------------------------------------
a5=6
*ap3=6
ap3=000000b4d81ffd9c
&ap3=000000b4d81ffd90
------------------------------------------------
a7=7
*ap7=7
&a7=000000b4d81ffd8c
ap7=000000b4d81ffd8c
&ap7=000000b4d81ffd80
a8=8
*ap7=8
&a8=000000b4d81ffd7c
ap7=000000b4d81ffd7c
&ap7=000000b4d81ffd80
a8=9
*ap7=9
&a8=000000b4d81ffd7c
ap7=000000b4d81ffd7c
&ap7=000000b4d81ffd80
------------------------------------------------

Process finished with exit code 0
```

### pointer

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

int main() {

  int a = 1, c = 2, b = 3;
  int *v_arr[3]{&a, &b, &c}; //{&int, &int, &int}

  int i_arr[3]{};
  int (*vp)[3] = &i_arr;

  int (*f)(int) = [](int v) -> int {
    printf("--->v=%d\n", v);
    return 0;
  };
  f(1);

  int (*f_arr[])(int){
      [](int) -> int {
        printf("--->f_arr 0\n");
        return 0;
      },
      [](int) -> int {
        printf("--->f_arr 1\n");
        return 1;
      },
      [](int) -> int {
        printf("--->f_arr 2\n");
        return 2;
      },
      [](int) -> int {
        printf("--->f_arr 3\n");
        return 3;
      },
      [](int) -> int {
        printf("--->f_arr 4\n");
        return 4;
      },
      nullptr
  };

  for (auto *fun : f_arr) {
    if (fun)
      fun(0);
  }
  printf("---------------------------------------\n");

  int (*(*fp)[])(int){&f_arr};
  int i = 0;
  do {
    (*fp)[i](i);
    i++;
  } while ((*fp)[i]);
  printf("---------------------------------------\n");

  int (*fun1[])(int){f};
  int (*(*fp1)[])(int){&fun1};
  (**fp1)(100);
  printf("---------------------------------------\n");

  int barr[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  int (*bp)[]{&barr};
  for (int i = 0; i < 10; i++) {
    printf("(*bp)[%d]=%d\n", i, (*bp)[i]);
  }
  printf("---------------------------------------\n");

}


##output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\pointer\test-pointer.exe
--->v=1
--->f_arr 0
--->f_arr 1
--->f_arr 2
--->f_arr 3
--->f_arr 4
---------------------------------------
--->f_arr 0
--->f_arr 1
--->f_arr 2
--->f_arr 3
--->f_arr 4
---------------------------------------
--->v=100
---------------------------------------
(*bp)[0]=1
(*bp)[1]=2
(*bp)[2]=3
(*bp)[3]=4
(*bp)[4]=5
(*bp)[5]=6
(*bp)[6]=7
(*bp)[7]=8
(*bp)[8]=9
(*bp)[9]=0
---------------------------------------

Process finished with exit code 0
```

### rvalue（右值）

```c++
//
// Created by ozcom on 2023/9/28.
//

/**
 *
 * 如何判断右值
 * 1、右值实例不能取地址
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


##output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\rvalue\test-rvalue.exe
1--->init
1--->run
2--->init
1--->init
2--->move assign
1--->deinit
2--->run
2--->copy assign
2--->move assign
2--->move assign
2--->move assign
3--->init
2--->move assign
3--->deinit
2--->deinit
1--->deinit

Process finished with exit code 0
```

### 如何解决宏定义冲突问题？

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

#define min(a, b) (((a) > (b)) ? (b) : (a))

/**
 *
 * 宏的污染是应为宏的命名没有限制
 * 因此导致命名冲突
 *
 * 规避宏污染的方式
 * 1、取消宏定义
 * 2、使用（）
 *
 * **/

int main() {

//  constexpr int v = std::min(1, 2); //编译失败，min函数会被min宏替换: constexpr int v = std::(((1) > (2)) ? (2) : (1))

  constexpr int v = (std::min)(1, 2); //函数加()
  std::cout << "v=" << v << std::endl;

#ifdef min
#undef min //取消宏定义
#endif
  constexpr int v2 = std::min(1, 2);
  std::cout << "v2=" << v2 << std::endl;

}



##output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\macro_polluting\test-macro_polluting.exe
v=1
v2=1

Process finished with exit code 0
```

### 如何在main函数前执行代码？

**可以使用初始化全局变量实现**

```c++
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



##output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\launch_before_main\test-launch_before_main.exe
0--->Feature()
5--->explicit Feature(int flag)
6--->explicit Feature(int flag)
flag_: 6
Hello, World!
1--->explicit Feature(int flag)
0--->Feature &operator=(Feature &&rf) noexcept
1--->virtual ~Feature()
2--->explicit Feature(int flag)
3--->explicit Feature(int flag)
2--->Feature &operator=(const Feature &rf)
7--->explicit Feature(int flag)
flag_: 7
2--->Feature &operator=(Feature &&rf) noexcept
7--->virtual ~Feature()
8--->explicit Feature(int flag)
flag_: 8
9--->explicit Feature(int flag)
flag_: 9
9--->virtual ~Feature()
flag_:
Process finished with exit code -1073741819 (0xC0000005)
```

### 智能指针

#### shared_ptr

```c++
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



##output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\shared_ptr\test-shared_ptr.exe
1--->init
1--->run
1--->deinit
2--->init
2--->run
2--->deinit
3--->init
3--->run
sp3: use_count=1
3--->run
sp3: use_count=2
sp4: use_count=2
3--->run
sp3: use_count=3
sp4: use_count=3
sp5: use_count=3
sp3: use_count=2
sp4: use_count=2
sp5: use_count=0
3--->deinit
30--->deinit
24--->deinit
18--->deinit
12--->deinit
6--->deinit
0--->deinit
init_shared_ptr exit
7--->init
7--->run
sp7: use_count=1
7--->run
sp8: use_count=2
7--->run
sp9: use_count=3
7--->run
sp10: use_count=4
sp10: use_count=0
11--->init
11--->run
sp7: use_count=1
reset_shared_ptr exit
7--->deinit
11--->deinit

Process finished with exit code 0
```

#### unique_ptr

```c++
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
```

#### weak_ptr

```c++
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



##output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\weak_ptr\test-weak_ptr.exe
1--->init
1--->run
sp use_count=1
1--->run
spt use_count=2
1 exit
1--->deinit
wp use_count=0
gw is expired

Process finished with exit code 0
```

### tuple&pair&遍历

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <functional>

template<typename T>
constexpr void print(T t) {
  std::cout << t << std::endl;
}

template<typename F, typename... T>
constexpr void print(F f, T ...t) {
  std::cout << f << std::endl;
  std::cout << sizeof...(t) << std::endl;
  printf(t...);
}

template<typename T>
constexpr void print_tuple(T t) {
  std::cout << typeid(t).name() << "\tt" << "=" << t << std::endl;
}

template<typename Tuple, size_t N>
struct foreach_tuple {

  constexpr static void print(const Tuple &t) {
    print_tuple(std::get<N - 1>(t));
    foreach_tuple<Tuple, N - 1>::print(t);
  }

};

template<typename Tuple>
struct foreach_tuple<Tuple, 1> {

  constexpr static void print(const Tuple &t) {
    print_tuple(std::get<0>(t));
  }

};

int main() {

  std::pair<std::string, std::vector<std::string>> p1{"a", {"a1", "a2"}};
  const auto [x, y] = p1;
  const auto &[f, s] = p1;
  printf("{&x=%p, &y=%p}\n", &x, &y);
  printf("{&f=%p, &s=%p}\n", &f, &s);
  printf("{&p1.first=%p, &p1.second=%p}\n", &p1.first, &p1.second);


  std::tuple<int, bool, float, std::string> t1;
  t1 = std::make_tuple(1, false, 0.5f, "abc");
  std::tuple<int, bool, float, std::string> t2;
  t2 = std::make_tuple(2, false, 1.5f, "def");
  std::cout << std::tuple_size<decltype(t1)>::value << std::endl;

  foreach_tuple<decltype(t1), std::tuple_size<decltype(t1)>::value>::print(t1);
  foreach_tuple<decltype(t2), std::tuple_size<decltype(t2)>::value>::print(t2);

}


####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\tuple\test-tuple.exe
{&x=0000004542fff6c0, &y=0000004542fff6e0}
{&f=0000004542fff700, &s=0000004542fff720}
{&p1.first=0000004542fff700, &p1.second=0000004542fff720}
4
NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE    t=abc
f       t=0.5
b       t=0
i       t=1
NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE    t=def
f       t=1.5
b       t=0
i       t=2

Process finished with exit code 0
```

### thread

#### jthread

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <coroutine>

int main() {

  std::jthread{[](const int &arg) {

    printf("arg=%d\n", arg);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    printf("child thread exit\n");

  }, 1};  //自动join

  std::thread{[](const int &arg) {

    printf("arg=%d\n", arg);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    printf("child thread exit\n");

  }, 1};  //若无主动join或detach，则会报异常


  printf("main thread exit\n");

}
```

#### mutex& condition_variable

##### 生产者和消费者

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <thread>
#include <condition_variable>

static std::mutex g_iMutex{};
static std::condition_variable g_iConditionVar{};

static long count = 0;

int main() {

  std::thread t1{[&]() {

    for (;;) {

      std::unique_lock lock{g_iMutex};
      count += 3;
      std::cout << "count += 3\n";

      g_iConditionVar.notify_one();

    }

  }};

  std::thread t2{[&]() {

    for (;;) {

      std::unique_lock lock{g_iMutex};

      if (count < 5)
        g_iConditionVar.wait(lock);

      count -= 2;
      std::cout << "count =" << count << "\n";

    }

  }};

  t2.join();
  t1.join();

}
```

### union&std::variant

```c++
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



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\variant\test-variant.exe
sizeof(v)=8
v.c=
v.n=-1717986918
v.d=0.4
v.c=a
v.c=54321

-------------------------------------------------------

sizeof v = 40
v = abc
v = 1
v = 0.33
v = 0.123
v = 123
v = a
c v = x

Process finished with exit code 0
```

### tie&结构化绑定&map遍历

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <tuple>
#include <string>
#include <array>
#include <map>

int main() {

  std::tuple<char, int, double, float, bool, std::string> t{'a', 123, 0.123, 0.123f, false, "123"};
  std::cout << "get type-----------------------------------------" << std::endl;
  std::cout << get<std::string>(t) << std::endl;
  std::cout << get<bool>(t) << std::endl;
  std::cout << get<float>(t) << std::endl;
  std::cout << get<double>(t) << std::endl;
  std::cout << get<int>(t) << std::endl;
  std::cout << get<char>(t) << std::endl;
  std::cout << "get index-----------------------------------------" << std::endl;
  std::cout << get<0>(t) << std::endl;
  std::cout << get<1>(t) << std::endl;
  std::cout << get<2>(t) << std::endl;
  std::cout << get<3>(t) << std::endl;
  std::cout << get<4>(t) << std::endl;
  std::cout << get<5>(t) << std::endl;

  {
    std::cout << "get tie-----------------------------------------" << std::endl;
    char c;
    int n;
    double d;
    float f;
    bool b;
    std::string s;
    std::tie(c, n, d, f, b, s) = t;
    std::cout << c << std::endl;
    std::cout << n << std::endl;
    std::cout << d << std::endl;
    std::cout << f << std::endl;
    std::cout << b << std::endl;
    std::cout << s << std::endl;
  }

  {
    std::cout << "get struct binding-----------------------------------------" << std::endl;
    auto &[c, n, d, f, b, s] = t;
    std::cout << c << std::endl;
    std::cout << n << std::endl;
    std::cout << d << std::endl;
    std::cout << f << std::endl;
    std::cout << b << std::endl;
    std::cout << s << std::endl;
  }

  {
    std::cout << "get tie-----------------------------------------" << std::endl;
    std::pair<char, int> p{'a', 123};
    char c;
    int n;
    std::tie(c, n) = p;
    std::cout << c << std::endl;
    std::cout << n << std::endl;
  }

  {
    std::cout << "get struct binding-----------------------------------------" << std::endl;
    std::pair<char, int> p{'a', 123};
    auto &[c, n] = p;
    std::cout << c << std::endl;
    std::cout << n << std::endl;
  }

  {
    std::cout << "get struct binding it map-----------------------------------------" << std::endl;
    std::map<int, std::string> m{
        {1, "123"}, {2, "456"}
    };
    printf("std::map<int, std::string>::value_type is std::pair<>\n");

    for (auto &[k, v] : m) {
      printf("{%d, %s}\n", k, v.c_str());
    }
  }

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\tie\test-tie.exe
get type-----------------------------------------
123
0
0.123
0.123
123
a
get index-----------------------------------------
a
123
0.123
0.123
0
123
get tie-----------------------------------------
a
123
0.123
0.123
0
123
get struct binding-----------------------------------------
a
123
0.123
0.123
0
123
get tie-----------------------------------------
a
123
get struct binding-----------------------------------------
a
123
get struct binding it map-----------------------------------------
std::map<int, std::string>::value_type is std::pair<>
{1, 123}
{2, 456}

Process finished with exit code 0
```

concepts （概念）

> concept定义概念
> requires定义约束
>  可约束模板参数
>  可约束函数行为

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <concepts>

/*
 * concept定义概念
 * requires定义约束
 *    可约束模板参数
 *    可约束函数行为
 *
 * */
template<typename T, typename U>
concept Addable1 = std::is_same_v<T, int> && std::is_same_v<U, int> /*定义类型约束*/
    && requires(T t, U u){
      t + u; /*定义行为约束*/
      { t + u } -> std::same_as<int>;  //约束行为的结果
    };

template<typename T, typename U>
concept Addable2 = requires(T t, U u){
  requires std::is_same_v<T, int>; /*定义类型约束*/
  requires std::is_same_v<U, int>;
  t + u; /*定义行为约束*/
  { t + u } -> std::same_as<int>;  //约束行为的结果
};

template<typename T, typename U>
requires Addable1<T, U>
auto add(T t, U u) {
  return t + u;
}

template<typename T, typename U>
auto add2(T t, U u) requires Addable1<T, U> {
  return t + u;
}

template<typename T, typename U>
requires std::is_same_v<T, int> && std::is_same_v<U, int> /*定义类型约束*/
    && requires(T t, U u){
      t + u; /*定义行为约束*/
      { t + u } -> std::same_as<int>;  //约束行为的结果
    }
auto add3(T t, U u) {
  return t + u;
}

template<typename T, typename U>
auto add5(T t, U u) requires Addable2<T, U> {
  return t + u;
}

template<typename T>
concept Inter1= std::is_same<T, int>::value;

Inter1 auto add4(Inter1 auto t, Inter1 auto u) {
  return t + u;
}

auto add(...) {
  return 0;
}

int main() {

  std::cout << add(1, 0) << std::endl;
  std::cout << add(0.4, 0) << std::endl;
  std::cout << add("0.4", "0") << std::endl;

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\concept\test-concept.exe
1
0
0

Process finished with exit code 0
```


