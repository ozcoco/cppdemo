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



# OOP

## 纯虚函数

> 注意点：
>
> 1、C++中纯虚函数不能被构造函数调用，但在Java中可以；
>
> 2、构造函数直接调用纯虚函数会在编译时报错
>
> 3、构造函数间接调用纯虚函数会在运行时报错

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

/**
 *
 * C++中纯虚函数不能被构造函数调用，但在Java中可以
 *
 * **/

class Foo {
 public:
  Foo() {
//    print();  //compile error
    printf("Foo init\n");
    show(); //runtime error
  }

  virtual void print() = 0;

  virtual void show() {
    print();
  }

};

class SubFoo : public Foo {
 public:
  SubFoo() {
    printf("SubFoo init\n");
  }

  void print() override {

    printf("--->SubFoo\n");

  }

  void show() override {
    Foo::show();
  }

};

int main() {

  Foo *f = new SubFoo{};
  f->print();
  f->show();

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\extends\test-extends.exe
Foo init
SubFoo init
--->SubFoo
--->SubFoo

Process finished with exit code 0

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



# Meta Programming

## 模板特化

> 类模板可以偏特化和全特化
>
> 函数只能全特化

```c++
//
// Created by ozcom on 2023/10/17.
//

#ifndef CPP_FEATURE_DEMO_META_PROGRAMMING_BASE_HPP_
#define CPP_FEATURE_DEMO_META_PROGRAMMING_BASE_HPP_

#include <iostream>
#include <array>
#include <string>
#include <string_view>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;


//template<typename T>
//constexpr auto sqt(T t) -> decltype(t * t) {
//  return t * t;
//}

template<typename T>
constexpr auto sqt(T t) {
  return t * t;
}

template<auto v>
constexpr auto t1 = sqt(v);

template<typename T, typename U>
struct foo {
  foo(const T &&t, const U &&u) {}
  void operator()() {
    std::cout << "泛化版本" << std::endl;
  }
};

template<typename U>
struct foo<int, U> {
  foo(const int &t, const U &&u) {}
  void operator()() {
    std::cout << "偏特化版本" << std::endl;
  }
};

template<>
struct foo<int, char> {
  foo(const int &t, const char &u) {}
  void operator()() {
    std::cout << "全特化版本" << std::endl;
  }
};

template<typename T, typename U>
void my_print(T t, U u) {
  std::cout << "my_print泛化版本" << std::endl;
}

/*
 * 函数模板不支持偏特化
 * */
//template<typename U>
//void my_print<int, U>() {
//  std::cout << "my_print泛化版本" << std::endl;
//}


/*
 * 重新定义只有U模板参数my_print版本
 * 可达到偏特化效果
 * */
template<typename U>
void my_print(bool t, U u) {
  std::cout << "重新定义只有U模板参数my_print版本" << std::endl;
}

template<>
void my_print<int, std::string>(int t, std::string u) {
  std::cout << "my_print全特化版本" << std::endl;
}

template<typename T, std::size_t N>
constexpr std::size_t static_carr_size(T const (&)[N]) {
  return N;
}

void base_main() {

  constexpr auto v = t1<123>;
  std::cout << "v=" << v << "\n";

  foo<int, int>{1, 2}();
  foo<double, double>{2.0, 4.0}();
  foo<int, char>{123, 'a'}();
  foo{'b', 'a'}();
  foo{"123"s, "7584"s}();

  my_print<double, double>(4.0, 3.3);
  my_print<double>(4.0, 3.3);
  my_print<int, std::string>(4, "3.3"s);
  my_print<std::string>(true, "3.3"s);
  my_print(4.0, 3.3);
  my_print(4.0, 3.3);
  my_print(4, "3.3"s);
  my_print(true, "3.3"s);

  std::array arr{1231, 45, 67767};

  char carr[]{1, 2, 3, 4, 45, 5, 56, 6, 6, 4, 45, 34, 4};
  std::cout << "carr size: " << static_carr_size(carr) << "\n";
  std::cout << "carr size: " << static_carr_size({1, 2, 3, 4, 45, 4, 45, 34, 4}) << "\n";

}

#endif //CPP_FEATURE_DEMO_META_PROGRAMMING_BASE_HPP_




####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\meta_programming\test-meta_programming.exe
v=15129
偏特化版本
泛化版本
全特化版本
泛化版本
泛化版本
my_print泛化版本
my_print泛化版本
my_print全特化版本
重新定义只有U模板参数my_print版本
my_print泛化版本
my_print泛化版本
my_print全特化版本
重新定义只有U模板参数my_print版本
carr size: 13
carr size: 9

Process finished with exit code 0


```



## 可变参数模板

> # Fold expressions(since C++17)
>
>  
>
> [C++](https://en.cppreference.com/w/cpp)
>
>  
>
> [C++ language](https://en.cppreference.com/w/cpp/language)
>
>  
>
> [Expressions](https://en.cppreference.com/w/cpp/language/expressions)
>
>  
>
> [Templates](https://en.cppreference.com/w/cpp/language/templates)
>
>  
>
> Reduces ([folds](https://en.wikipedia.org/wiki/Fold_(higher-order_function))) a [parameter pack](https://en.cppreference.com/w/cpp/language/parameter_pack) over a binary operator.
>
> ### Syntax
>
> |                                               |      |      |
> | --------------------------------------------- | ---- | ---- |
> | `**(**` *pack op* `**... )**`                 | (1)  |      |
> |                                               |      |      |
> | `**( ...**` *op pack* `**)**`                 | (2)  |      |
> |                                               |      |      |
> | `**(**` *pack op* `**...**` *op init* `**)**` | (3)  |      |
> |                                               |      |      |
> | `**(**` *init op* `**...**` *op pack* `**)**` | (4)  |      |
> |                                               |      |      |
>
> 1) Unary right fold.
> 2) Unary left fold.
> 3) Binary right fold.
> 4) Binary left fold.
>
> | *op*   | -    | any of the following 32 *binary* operators: + - * / % ^ & \| = < > << >> += -= *= /= %= ^= &= \|= <<= >>= == != <= >= && \|\| , .* ->*. In a binary fold, both *op*s must be the same. |
> | ------ | ---- | ------------------------------------------------------------ |
> | *pack* | -    | an expression that contains an unexpanded [parameter pack](https://en.cppreference.com/w/cpp/language/parameter_pack) and does not contain an operator with [precedence](https://en.cppreference.com/w/cpp/language/operator_precedence) lower than cast at the top level (formally, a *cast-expression*) |
> | *init* | -    | an expression that does not contain an unexpanded [parameter pack](https://en.cppreference.com/w/cpp/language/parameter_pack) and does not contain an operator with [precedence](https://en.cppreference.com/w/cpp/language/operator_precedence) lower than cast at the top level (formally, a *cast-expression*) |
>
> Note that the opening and closing parentheses are a required part of the fold expression.
>
> ### Explanation
>
> The instantiation of a *fold expression* expands the expression e as follows:
>
> 1) Unary right fold `(E` *op* `...)` becomes `(E1` *op* `(`... *op* `(EN-1` *op* `EN)))`
> 2) Unary left fold `(...` *op* `E)` becomes `(((E1` *op* `E2)` *op* ...`)` *op* `EN)`
> 3) Binary right fold `(E` *op* `...` *op* `I)` becomes `(E1` *op* `(`... *op* `(EN−1` *op* `(EN` *op* `I))))`
> 4) Binary left fold `(I` *op* `...` *op* `E)` becomes `((((I` *op* `E1)` *op* `E2)` *op* ...`)` *op* `EN)`
>
> (where `N` is the number of elements in the pack expansion)
>
> For example,
>
> ```c++
> template<typename... Args>
> bool all(Args... args) { return (... && args); }
>  
> bool b = all(true, true, true, false);
> // within all(), the unary left fold expands as
> //  return ((true && true) && true) && false;
> // b is false
> ```
>
> When a unary fold is used with a pack expansion of length zero, only the following operators are allowed:
>
> 1) Logical AND (&&). The value for the empty pack is true.
> 2) Logical OR (||). The value for the empty pack is false.
> 3) The comma operator (,). The value for the empty pack is void().
>
> ### Notes
>
> If the expression used as *init* or as *pack* has an operator with [precedence](https://en.cppreference.com/w/cpp/language/operator_precedence) below cast at the top level, it must be parenthesized:
>
> ```c++
> template<typename... Args>
> int sum(Args&&... args)
> {
> //  return (args + ... + 1 * 2);   // Error: operator with precedence below cast
>     return (args + ... + (1 * 2)); // OK
> }
> ```
>
> |                      Feature-test macro                      |  Value  |   Std   |                           Feature                            |
> | :----------------------------------------------------------: | :-----: | :-----: | :----------------------------------------------------------: |
> | [`__cpp_fold_expressions`](https://en.cppreference.com/w/cpp/feature_test#cpp_fold_expressions) | 201603L | (C++17) | [Fold expressions](https://en.cppreference.com/w/cpp/language/fold#top) |
>
> ### Example
>
> Run this code
>
> ```c++
> #include <climits>
> #include <concepts>
> #include <cstdint>
> #include <iostream>
> #include <type_traits>
> #include <utility>
> #include <vector>
>  
> template<typename... Args>
> void printer(Args&&... args)
> {
>     (std::cout << ... << args) << '\n';
> }
>  
> template<typename T, typename... Args>
> void push_back_vec(std::vector<T>& v, Args&&... args)
> {
>     static_assert((std::is_constructible_v<T, Args&&> && ...));
>     (v.push_back(std::forward<Args>(args)), ...);
> }
>  
> template<class T, std::size_t... dummy_pack>
> constexpr T bswap_impl(T i, std::index_sequence<dummy_pack...>)
> {
>     T low_byte_mask = (unsigned char)-1;
>     T ret{};
>     ([&]
>     {
>         (void)dummy_pack;
>         ret <<= CHAR_BIT;
>         ret |= i & low_byte_mask;
>         i >>= CHAR_BIT;
>     }(), ...);
>     return ret;
> }
>  
> constexpr auto bswap(std::unsigned_integral auto i)
> {
>     return bswap_impl(i, std::make_index_sequence<sizeof(i)>{});
> }
>  
> int main()
> {
>     printer(1, 2, 3, "abc");
>  
>     std::vector<int> v;
>     push_back_vec(v, 6, 2, 45, 12);
>     push_back_vec(v, 1, 2, 9);
>     for (int i : v)
>         std::cout << i << ' ';
>     std::cout << '\n';
>  
>     static_assert(bswap<std::uint16_t>(0x1234u) == 0x3412u);
>     static_assert(bswap<std::uint64_t>(0x0123456789abcdefull) == 0xefcdab8967452301ULL);
> }
> ```
>
> Output:
>
> ```shell
> 123abc
> 6 2 45 12 1 2 9
> ```
>
> ### References
>
> - C++23 standard (ISO/IEC 14882:2023):
>
> - C++20 standard (ISO/IEC 14882:2020):
>
> - C++17 standard (ISO/IEC 14882:2017):
>
>   

```c++
//
// Created by ozcom on 2023/10/17.
//

#ifndef CPP_FEATURE_DEMO_META_PROGRAMMING_VARIABLE_TEMPLATE_HPP_
#define CPP_FEATURE_DEMO_META_PROGRAMMING_VARIABLE_TEMPLATE_HPP_

#include <iostream>
#include <array>
#include <string>
#include <string_view>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

template<typename ...Args>
constexpr
auto types_sum(Args &&...args) {
  return (... + args);
}

template<typename T, T ...args>
struct my_args_sum {
  enum {
    value = (... + args),
    value2 = (args + ... ),
    value3 = (0 + ... + args),
    value4 = (args + ... + 0)
  };
};

template<double ...args>
struct my_args_sum<double, args...> {
  constexpr inline static auto value = (... + args);
};

class bar {
 public:
  bar() = delete;
  constexpr explicit bar(std::pair<std::string, int> const &v) : v_(v) {}
  constexpr explicit bar(std::pair<std::string, int> &&v) : v_(v) {}

  constexpr bar operator+(const bar &rfh) const {
    std::string k{this->v_.first};
    k.append(", ");
    k.append(rfh.v_.first);
    return bar{std::make_pair(std::move(k), this->v_.second + rfh.v_.second)};
  }

  bool operator==(const bar &rhs) const {
    return v_ == rhs.v_;
  }
  bool operator!=(const bar &rhs) const {
    return !(rhs == *this);
  }

  bool operator<(const bar &rhs) const {
    return v_ < rhs.v_;
  }
  bool operator>(const bar &rhs) const {
    return rhs < *this;
  }
  bool operator<=(const bar &rhs) const {
    return !(rhs < *this);
  }
  bool operator>=(const bar &rhs) const {
    return !(*this < rhs);
  }

  friend std::ostream &operator<<(std::ostream &os, const bar &bar) {
    os << "v_: {" << bar.v_.first << " -> " << bar.v_.second << "}";
    return os;
  }

 private:
  std::pair<std::string, int> v_;
};

template<typename T, T ...args>
constexpr auto my_args_sum_v = my_args_sum<T, args...>::value;

template<int...args>
constexpr auto my_integer_sequence_sum_v = my_args_sum_v<int, args...>;

void variable_template_main() {

  std::cout << types_sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 0) << "\n";
  std::cout << my_args_sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value << "\n";
  std::cout << my_args_sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value2 << "\n";
  std::cout << my_args_sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value3 << "\n";
  std::cout << my_args_sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value4 << "\n";
  std::cout << my_args_sum_v<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0> << "\n";
  std::cout << my_integer_sequence_sum_v<1, 2, 3, 4, 5, 6, 7, 8, 9, 0> << "\n";

}

#endif //CPP_FEATURE_DEMO_META_PROGRAMMING_VARIABLE_TEMPLATE_HPP_




####outpu
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\meta_programming\test-meta_programming.exe
v=15129
偏特化版本
泛化版本
全特化版本
泛化版本
泛化版本
my_print泛化版本
my_print泛化版本
my_print全特化版本
重新定义只有U模板参数my_print版本
my_print泛化版本
my_print泛化版本
my_print全特化版本
重新定义只有U模板参数my_print版本
carr size: 13
carr size: 9
------------------------------------------------------------------------------
45
45
45
45
45
45
45

Process finished with exit code 0

```



# Stream

> C++ 包含如下的输入/输出库：[OOP-风格的](https://en.wikipedia.org/wiki/Object-oriented_programming)、[基于流的输入/输出](https://zh.cppreference.com/w/cpp/io#.E5.9F.BA.E4.BA.8E.E6.B5.81.E7.9A.84.E8.BE.93.E5.85.A5.2F.E8.BE.93.E5.87.BA)库，[基于打印的函数族](https://zh.cppreference.com/w/cpp/io#.E6.89.93.E5.8D.B0.E5.87.BD.E6.95.B0_.28C.2B.2B23_.E8.B5.B7.29) (C++23 起)、以及[C 风格输入/输出](https://zh.cppreference.com/w/cpp/io#C_.E9.A3.8E.E6.A0.BC.E8.BE.93.E5.85.A5.2F.E8.BE.93.E5.87.BA)函数的标准集合。
>
> 
>
> ### 基于流的输入/输出
>
> 基于流的输入/输出库围绕抽象的输入/输出设备组织。这些抽象设备允许相同代码处理对文件、内存流或随即进行任意操作（例如压缩）的自定义适配器设备的输入/输出。
>
> 大多数已经被类模板化，故它们能被适配到任何标准字符类型。为最常用的基本字符类型（char 和 wchar_t）提供分离的 typedef。以下列层次将类组织：
>
> 
>
> 继承图
>
> ![image-20231019224409425](./C++%E7%BC%96%E7%A8%8B.assets/image-20231019224409425.png)
>
> | 抽象                                                         |                                                              |
> | ------------------------------------------------------------ | ------------------------------------------------------------ |
> | 在标头 `<ios>` 定义                                          |                                                              |
> | [ios_base](https://zh.cppreference.com/w/cpp/io/ios_base)    | 管理格式化标志和输入/输出异常 (类)                           |
> | [basic_ios](https://zh.cppreference.com/w/cpp/io/basic_ios)  | 管理任意流缓冲 (类模板)                                      |
> | 在标头 `<streambuf>` 定义                                    |                                                              |
> | [basic_streambuf](https://zh.cppreference.com/w/cpp/io/basic_streambuf) | 抽象原生设备 (类模板)                                        |
> | 在标头 `<ostream>` 定义                                      |                                                              |
> | [basic_ostream](https://zh.cppreference.com/w/cpp/io/basic_ostream) | 包装给定的抽象设备（[std::basic_streambuf](https://zh.cppreference.com/w/cpp/io/basic_streambuf)） 并提供高层输出接口 (类模板) |
> | 在标头 `<istream>` 定义                                      |                                                              |
> | [basic_istream](https://zh.cppreference.com/w/cpp/io/basic_istream) | 包装给定的抽象设备（[std::basic_streambuf](https://zh.cppreference.com/w/cpp/io/basic_streambuf)） 并提供高层输入接口 (类模板) |
> | [basic_iostream](https://zh.cppreference.com/w/cpp/io/basic_iostream) | 包装给定的抽象设备（[std::basic_streambuf](https://zh.cppreference.com/w/cpp/io/basic_streambuf)） 并提供高层输入/输出接口 (类模板) |
> | 文件输入/输出实现                                            |                                                              |
> | 在标头 `<fstream>` 定义                                      |                                                              |
> | [basic_filebuf](https://zh.cppreference.com/w/cpp/io/basic_filebuf) | 抽象原生文件设备 (类模板)                                    |
> | [basic_ifstream](https://zh.cppreference.com/w/cpp/io/basic_ifstream) | 实现高层文件流输入操作 (类模板)                              |
> | [basic_ofstream](https://zh.cppreference.com/w/cpp/io/basic_ofstream) | 实现高层文件流输出操作 (类模板)                              |
> | [basic_fstream](https://zh.cppreference.com/w/cpp/io/basic_fstream) | 实现高层文件流输入/输出操作 (类模板)                         |
> | 字符串输入/输出实现                                          |                                                              |
> | 在标头 `<sstream>` 定义                                      |                                                              |
> | [basic_stringbuf](https://zh.cppreference.com/w/cpp/io/basic_stringbuf) | 实现原生字符串设备 (类模板)                                  |
> | [basic_istringstream](https://zh.cppreference.com/w/cpp/io/basic_istringstream) | 实现高层字符串流输入操作 (类模板)                            |
> | [basic_ostringstream](https://zh.cppreference.com/w/cpp/io/basic_ostringstream) | 实现高层字符串流输出操作 (类模板)                            |
> | [basic_stringstream](https://zh.cppreference.com/w/cpp/io/basic_stringstream) | 实现高层字符串流输入/输出操作 (类模板)                       |
> | 数组输入/输出实现                                            |                                                              |
> | 在标头 `<spanstream>` 定义                                   |                                                              |
> | [basic_spanbuf](https://zh.cppreference.com/w/cpp/io/basic_spanbuf)(C++23) | 实现原始固定字符缓冲区设备 (类模板)                          |
> | [basic_ispanstream](https://zh.cppreference.com/w/cpp/io/basic_ispanstream)(C++23) | 实现固定字符缓冲区输入操作 (类模板)                          |
> | [basic_ospanstream](https://zh.cppreference.com/w/cpp/io/basic_ospanstream)(C++23) | 实现固定字符缓冲区输出操作 (类模板)                          |
> | [basic_spanstream](https://zh.cppreference.com/w/cpp/io/basic_spanstream)(C++23) | 实现固定字符缓冲区输入/输出操作 (类模板)                     |
> | 在标头 `<strstream>` 定义                                    |                                                              |
> | [strstreambuf](https://zh.cppreference.com/w/cpp/io/strstreambuf)(C++98 中弃用) | 实现原生字符数组设备 (类)                                    |
> | [istrstream](https://zh.cppreference.com/w/cpp/io/istrstream)(C++98 中弃用) | 实现字符数组输入操作 (类)                                    |
> | [ostrstream](https://zh.cppreference.com/w/cpp/io/ostrstream)(C++98 中弃用) | 实现字符数组输出操作 (类)                                    |
> | [strstream](https://zh.cppreference.com/w/cpp/io/strstream)(C++98 中弃用) | 实现字符数组输入/输出操作 (类)                               |
> | 同步的输出                                                   |                                                              |
> | 在标头 `<syncstream>` 定义                                   |                                                              |
> | [basic_syncbuf](https://zh.cppreference.com/w/cpp/io/basic_syncbuf)(C++20) | 同步输出设备的包装 (类模板)                                  |
> | [basic_osyncstream](https://zh.cppreference.com/w/cpp/io/basic_osyncstream)(C++20) | 同步输出流的包装 (类模板)                                    |
>
> #### typedef
>
> 在 `std` 命名空间提供对常用字符类型的下列 typedef：
>
> ```c++
> typedef basic_ios<char>                ios;
> typedef basic_ios<wchar_t>            wios;
>  
> typedef basic_streambuf<char>     streambuf;
> typedef basic_streambuf<wchar_t> wstreambuf;
> typedef basic_filebuf<char>         filebuf;
> typedef basic_filebuf<wchar_t>     wfilebuf;
> typedef basic_stringbuf<char>     stringbuf;
> typedef basic_stringbuf<wchar_t> wstringbuf;
> typedef basic_syncbuf<char>         syncbuf; // C++20
> typedef basic_syncbuf<wchar_t>     wsyncbuf; // C++20
> typedef basic_spanbuf<char>         spanbuf; // C++23
> typedef basic_spanbuf<wchar_t>     wspanbuf; // C++23
>  
> typedef basic_istream<char>         istream;
> typedef basic_istream<wchar_t>     wistream;
> typedef basic_ostream<char>         ostream;
> typedef basic_ostream<wchar_t>     wostream;
> typedef basic_iostream<char>       iostream;
> typedef basic_iostream<wchar_t>   wiostream;
>  
> typedef basic_ifstream<char>       ifstream;
> typedef basic_ifstream<wchar_t>   wifstream;
> typedef basic_ofstream<char>       ofstream;
> typedef basic_ofstream<wchar_t>   wofstream;
> typedef basic_fstream<char>         fstream;
> typedef basic_fstream<wchar_t>     wfstream;
>  
> typedef basic_istringstream<char>     istringstream;
> typedef basic_istringstream<wchar_t> wistringstream;
> typedef basic_ostringstream<char>     ostringstream;
> typedef basic_ostringstream<wchar_t> wostringstream;
> typedef basic_stringstream<char>       stringstream;
> typedef basic_stringstream<wchar_t>   wstringstream;
>  
> typedef basic_osyncstream<char>     osyncstream; // C++20
> typedef basic_osyncstream<wchar_t> wosyncstream; // C++20
>  
> typedef basic_ispanstream<char>     ispanstream; // C++23
> typedef basic_ispanstream<wchar_t> wispanstream; // C++23
> typedef basic_ospanstream<char>     ospanstream; // C++23
> typedef basic_ospanstream<wchar_t> wospanstream; // C++23
> typedef basic_spanstream<char>       spanstream; // C++23
> typedef basic_spanstream<wchar_t>   wspanstream; // C++23
> ```
>
> #### 预定义标准流对象
>
> | 在标头 `<iostream>` 定义                               |                                                              |
> | ------------------------------------------------------ | ------------------------------------------------------------ |
> | [cinwcin](https://zh.cppreference.com/w/cpp/io/cin)    | 从标准 C 输入流 [stdin](https://zh.cppreference.com/w/cpp/io/c) 中读取 (全局对象) |
> | [coutwcout](https://zh.cppreference.com/w/cpp/io/cout) | 写入到标准 C 输出流 [stdout](https://zh.cppreference.com/w/cpp/io/c) (全局对象) |
> | [cerrwcerr](https://zh.cppreference.com/w/cpp/io/cerr) | 写入到标准 C 错误流 [stderr](https://zh.cppreference.com/w/cpp/io/c)，无缓冲 (全局对象) |
> | [clogwclog](https://zh.cppreference.com/w/cpp/io/clog) | 写入到标准 C 错误流 [stderr](https://zh.cppreference.com/w/cpp/io/c) (全局对象) |
>
> #### [输入/输出操纵符](https://zh.cppreference.com/w/cpp/io/manip)
>
> 基于流的输入/输出库用 [输入/输出操纵符](https://zh.cppreference.com/w/cpp/io/manip)（例如 [std::boolalpha](https://zh.cppreference.com/w/cpp/io/manip/boolalpha)、[std::hex](https://zh.cppreference.com/w/cpp/io/manip/hex) 等）控制流的行为。
>
> #### 类型
>
> 定义下列辅助类型：
>
> | 在标头 `<ios>` 定义                                          |                                                              |
> | ------------------------------------------------------------ | ------------------------------------------------------------ |
> | [streamoff](https://zh.cppreference.com/w/cpp/io/streamoff)  | 表示相对的文件/流位置（距 fpos 的偏移），足以表示任何文件大小 (typedef) |
> | [streamsize](https://zh.cppreference.com/w/cpp/io/streamsize) | 表示一次输入/输出操作中转移的字符数或输入/输出缓冲区的大小 (typedef) |
> | [fpos](https://zh.cppreference.com/w/cpp/io/fpos)            | 表示流或文件中的绝对位置 (类模板)                            |
>
> 提供下列 [std::fpos](http://zh.cppreference.com/w/cpp/io/fpos)<[std::mbstate_t](http://zh.cppreference.com/w/cpp/string/multibyte/mbstate_t)> 的 typedef 名：
>
> | 在标头 `<iosfwd>` 定义      |                                                              |
> | --------------------------- | ------------------------------------------------------------ |
> | 类型                        | 定义                                                         |
> | `std::streampos`            | [std::fpos](http://zh.cppreference.com/w/cpp/io/fpos)<[std::char_traits](http://zh.cppreference.com/w/cpp/string/char_traits)<char>::state_type> |
> | `std::wstreampos`           | [std::fpos](http://zh.cppreference.com/w/cpp/io/fpos)<[std::char_traits](http://zh.cppreference.com/w/cpp/string/char_traits)<wchar_t>::state_type> |
> | `std::u8streampos` (C++20)  | [std::fpos](http://zh.cppreference.com/w/cpp/io/fpos)<[std::char_traits](http://zh.cppreference.com/w/cpp/string/char_traits)<char8_t>::state_type> |
> | `std::u16streampos` (C++11) | [std::fpos](http://zh.cppreference.com/w/cpp/io/fpos)<[std::char_traits](http://zh.cppreference.com/w/cpp/string/char_traits)<char16_t>::state_type> |
> | `std::u32streampos` (C++11) | [std::fpos](http://zh.cppreference.com/w/cpp/io/fpos)<[std::char_traits](http://zh.cppreference.com/w/cpp/string/char_traits)<char32_t>::state_type> |
>
> #### 错误类别接口
>
> | 在标头 `<ios>` 定义                                          |                               |
> | ------------------------------------------------------------ | ----------------------------- |
> | [io_errc](https://zh.cppreference.com/w/cpp/io/io_errc)(C++11) | 输入/输出流的错误码 (枚举)    |
> | [iostream_category](https://zh.cppreference.com/w/cpp/io/iostream_category)(C++11) | 鉴别 iostream 错误类别 (函数) |
>
> ### 打印函数 (C++23 起)
>
> 对Unicode编码的格式化文本提供输入输出支持的print族函数。这些函数拥有 std::format 带来的性能优势，默认情况下与本地环境无关；减少使用全局状态，同时避免 operator<< 调用和申请临时的 [std::string](https://zh.cppreference.com/w/cpp/string/basic_string) 对象。一般情况下比 [iostreams](https://zh.cppreference.com/w/cpp/io#Stream-based_I.2FO) 和 [stdio](https://zh.cppreference.com/w/cpp/io#C-style_I.2FO) 更高效。
>
> 标准库提供了如下print族函数：
>
> | 在标头 `<print>` 定义                                        |                                                              |
> | ------------------------------------------------------------ | ------------------------------------------------------------ |
> | [print](https://zh.cppreference.com/w/cpp/io/print)(C++23)   | 将参数的 [格式化](https://zh.cppreference.com/w/cpp/utility/format) 表达输出到 [stdout](https://zh.cppreference.com/w/cpp/io/c) 或文件缓冲区 (函数模板) |
> | [println](https://zh.cppreference.com/w/cpp/io/println)(C++23) | 将参数的 [格式化](https://zh.cppreference.com/w/cpp/utility/format) 表达输出到 [stdout](https://zh.cppreference.com/w/cpp/io/c) 或文件缓冲区，输出完成后换行 (函数模板) |
> | [vprint_unicode](https://zh.cppreference.com/mwiki/index.php?title=cpp/io/vprint_unicode&action=edit&redlink=1)(C++23) | 使用[类型擦除](https://zh.cppreference.com/w/cpp/utility/format/basic_format_args)的参数表示，打印到支持Unicode的[stdout](https://zh.cppreference.com/w/cpp/io/c)或文件流 (函数) |
> | [vprint_nonunicode](https://zh.cppreference.com/mwiki/index.php?title=cpp/io/vprint_nonunicode&action=edit&redlink=1)(C++23) | 使用[类型擦除](https://zh.cppreference.com/w/cpp/utility/format/basic_format_args)的参数表示，打印到[stdout](https://zh.cppreference.com/w/cpp/io/c)或文件流 (函数) |
>
> 
>
> ### [C 风格输入/输出](https://zh.cppreference.com/w/cpp/io/c)
>
> C++ 也包含了 [C 所定义的输入/输出函数](https://zh.cppreference.com/w/cpp/io/c)，如 [std::fopen](https://zh.cppreference.com/w/cpp/io/c/fopen)、[std::getc](https://zh.cppreference.com/w/cpp/io/c/fgetc) 等。



## 文件读写

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Bar {
  int n;
  Bar() {
    std::cout << "Enter n: ";
    std::cin >> n;
  }
};

static Bar b;
static void standard_stream() {

  std::cout << "standard output stream \n";

  std::string s{};
  std::cin >> s;

  std::cerr << s << "\n";

  std::wstring ws{};
  std::wcin >> ws;

  std::wclog << ws << "\n";

  std::clog << "sadfasdtgdfgdfg\n";

  std::clog << "b.n=" << b.n;

}

static void str_stream() {

  std::stringstream ss{};
  ss << "10000";
  int a;
  ss >> a;
  std::cout << "a = " << a << "\n";

  std::string s{};
  ss >> s;
  std::cout << "s = " << a << "\n";

}

static void file_stream() {

  std::fstream f{R"(C:\Users\ozcom\Desktop\123.txt)", std::ios::in | std::ios::out};

  if (!f.is_open()) {
    std::cerr << "failed to open " << R"(C:\Users\ozcom\Desktop\123.txt)" << "\n";
    return;
  }

  std::string str{};
  while (f >> str) {
    std::cout << str << "\n";
  }

}

int main() {

  standard_stream();
  str_stream();
  file_stream();

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\stream\test-stream.exe
Enter n: 123
standard output stream 
aaa
aaa
bbb
a = 10000
s = 10000
1111111111111111111111
aaaaaaaaaaa
CCCCCCCCCCCCCCCCCCCCCCC
三十个第三个第四个豆腐干士大夫根深蒂固
bbb
sadfasdtgdfgdfg
b.n=123
Process finished with exit code 0


```



# SFINAE

## 函数重载



### 指针、对象约束

> 根据类型为指针和对象的调用方式，选取特化函数

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

inline auto call(...) {
  std::cout << "大保底" << "\n";
}

template<typename T, typename F>
constexpr
auto call(T t, F f) -> decltype((t.*f)()) {
  std::cout << "call 1" << "\n";
  return (t.*f)();
}

template<typename T, typename F>
constexpr
auto call(T t, F f) -> decltype((t->*f)()) {
  std::cout << "call 2" << "\n";
  return (t->*f)();
}

struct A {
  inline void print() const {
    std::cout << "hello A" << "\n";
  }
};

int main() {

  A a{};
  call(a, &A::print);
  call(&a, &A::print);
  call(1, 2);

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\SFINAE\test-SFINAE.exe
call 1
hello A
call 2
hello A
大保底

Process finished with exit code 0


```



### 成员约束

> 根据类或者对象是否存在某个成员，选取特化函数

```c++
template<bool, typename T>
struct enable_if {
  using type = T;
};

template<typename T>
struct enable_if<false, T> {};

auto foo(...) {
  std::cout << "大保底" << "\n";
}

template<typename T>
constexpr
typename enable_if<std::is_same_v<T, int>, T>::type foo(T v) {
  std::cout << "T type int" << "\n";
  return v;
}

template<typename T>
constexpr
typename enable_if<std::is_same_v<T, double>, T>::type foo(T v) {
  std::cout << "T type double" << "\n";
  return v;
}

int main() {

  foo(1);
  foo(0.02);
  foo();

}



####output
T type int
T type double
大保底
```



### 类型约束

> 根据类型，选取特化函数

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

template<bool, typename T>
struct enable_if {
  using type = T;
};

template<typename T>
struct enable_if<false, T> {};

template<typename T>
constexpr
enable_if<std::is_integral_v<T>, bool>::type is_odd(T t) {
  std::cout << "is_odd: T type int" << "\n";
  return bool(t % 2);
}

int main() {

  is_odd(1);
//  is_odd(0.1); //error

}




####output
is_odd: T type int
    
```



### 成员类型和是否存在同时约束

> 根据成员是否存在以及是某个特定的类型，选取特化函数



```c++
template<typename, typename>
struct has_x : std::false_type {};

template<typename T>
struct has_x<T, decltype(T::x)> : std::true_type {};

template<typename T, typename C>
inline constexpr bool has_x_v = has_x<T, C>::value;

struct F {
  int x;
};

struct E {
  double x;
};

int main() {

  constexpr auto f_has = has_x_v<F, double>;
  std::cout << "f_has=" << f_has << "\n";
  constexpr auto ff_has = has_x_v<F, int>;
  std::cout << "b_has=" << ff_has << "\n";

  constexpr auto e_has = has_x_v<E, double>;
  std::cout << "e_has=" << e_has << "\n";
  constexpr auto ee_has = has_x_v<E, int>;
  std::cout << "e_has=" << ee_has << "\n";

}



####output
f_has=0
b_has=1
e_has=1
e_has=0


```



### 判断类中是否存在内嵌type

```c++


template<typename ... Types>
using void_t = void;

template<typename, typename = void_t<>>
struct has_type_member : std::false_type {};

template<typename T>
struct has_type_member<T, void_t<typename T::type>> : std::true_type {};

struct S {
  using type = int;
};

struct S2 {
};

int main() {

  constexpr auto s_has = has_type_member<S>::value;
  std::cout << "s_has=" << s_has << "\n";
  constexpr auto s2_has = has_type_member<S2>::value;
  std::cout << "s2_has=" << s2_has << "\n";

}



####output
s_has=1
s2_has=0

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

### concepts （概念）

> concept定义概念
> requires定义约束
>    可约束模板参数
>    可约束函数行为

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



### std::decay

> std::decay 元函数，用于去除类型修饰符

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

/*
 * std::decay 元函数，用于去除类型修饰符
 *
 * */

int main() {

  int a = 1;
  int &ar = a;
  int &&b = 2;
  const int &c = b;
  std::cout << "a:" << typeid(a).name() << std::endl;
  std::cout << "ar:" << typeid(ar).name() << std::endl;
  std::cout << "b:" << typeid(b).name() << std::endl;
  std::cout << "c:" << typeid(c).name() << std::endl;

  std::cout << "c: = a:" << std::is_same_v<decltype(c), decltype(a)> << std::endl;
  using Tc = std::decay<decltype(c)>::type; //去除类型修饰符
  using Tc2 = std::decay_t<decltype(c)>;
  std::cout << "c: = a:" << std::is_same_v<Tc, decltype(a)> << std::endl;
  std::cout << "c: = a:" << std::is_same_v<Tc2, decltype(a)> << std::endl;

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\decay_t\test-decay_t.exe
a:i
ar:i
b:i
c:i
c: = a:0
c: = a:1
c: = a:1

Process finished with exit code 0

```



### std::any

> 任意数据类型（泛型数据）

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <any>
#include <string>
#include <vector>
#include <variant>

using namespace std::literals::string_literals;

template<typename T>
struct Any {

  using value_type = T;

  constexpr Any(const T &&t) : _t_(t) {}

  constexpr operator T() {
    return _t_;
  }

  value_type _t_;
};

int main() {

  std::any a = 123;
  std::cout << "int size:" << sizeof(int) << std::endl;
  std::cout << "a size:" << sizeof a << std::endl;
  std::cout << "std::any size:" << sizeof(std::any) << std::endl;
  std::variant<bool, char, unsigned char, int, unsigned int, long int, unsigned long int, std::string, Any<int>>
      i1 = 123;
  std::cout << "i1 size:" << sizeof(i1) << std::endl;
  std::cout << "std::variant<int> size:" << sizeof(decltype(i1)) << std::endl;
  std::cout << "a:" << typeid(a).name() << std::endl;
  std::cout << "a:" << a.type().name() << std::endl;
  std::cout << "a =" << std::any_cast<int>(a) << std::endl;

  Any y1 = 123;
  Any s1 = std::string{"123"};

  int yy1 = y1;
  std::string ss1 = s1;
  std::cout << "yy1 =" << yy1 << std::endl;

  std::vector<std::any> vec{false, 'a', 0.1f, 0.123, 2, 3U, 4L, 5UL, "12345"s};
  for (auto &&e : vec) {

    if (auto *p = std::any_cast<bool>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<char>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<float>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<double>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<int>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<unsigned int>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<long int>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<unsigned long int>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;
    if (auto *p = std::any_cast<std::string>(&e))
      std::cout << typeid(std::remove_pointer_t<decltype(p)>).name() << " v =" << *p << std::endl;

  }

}




#####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\any\test-any.exe
int size:4
a size:16
std::any size:16
i1 size:40
std::variant<int> size:40
a:St3any
a:i
a =123
yy1 =123
b v =0
c v =a
f v =0.1
d v =0.123
i v =2
j v =3
l v =4
m v =5
NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE v =12345

Process finished with exit code 0

```



### std::visit

> 高效访问std::variant

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <variant>
#include <string>
#include <string_view>
#include <sstream>

using namespace std::literals::string_literals;

template<class>
inline static constexpr bool always_false_v = false;

struct Visitor {
  inline void operator()(bool v) const {
    std::cout << "bool v = " << v << std::endl;
  }
  inline void operator()(char v) const {
    std::cout << "char v = " << v << std::endl;
  }
  inline void operator()(int v) const {
    std::cout << "int v = " << v << std::endl;
  }
  inline void operator()(double v) const {
    std::cout << "double v = " << v << std::endl;
  }
  inline void operator()(float v) const {
    std::cout << "float v = " << v << std::endl;
  }
  inline void operator()(std::string &v) const {
    std::cout << "std::string v = " << v << std::endl;
  }
  inline void operator()(auto &&v) const {
    static_assert(always_false_v<decltype(v)>, "non-exhaustive visitor!");
  }

};

static void visit_feature() {

  std::variant<bool, char, int, double, float, std::string> v{};
  v = "abcdef"s;
  std::visit(Visitor{}, v);

  v = 0.01f;

  std::visit([](auto &&v) {

    using T = std::decay_t<decltype(v)>;

    if constexpr (std::is_same_v<T, bool>)
      std::cout << "bool v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, char>)
      std::cout << "char v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, int>)
      std::cout << "int v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, float>)
      std::cout << "float v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, double>)
      std::cout << "double v = " << v << std::endl;
    else if constexpr (std::is_same_v<T, std::string>)
      std::cout << "std::string v = " << v << std::endl;
    else
      static_assert(always_false_v<decltype(v)>, "non-exhaustive visitor!");

  }, v);

}

int main() {

  visit_feature();

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\visit\test-visit.exe
std::string v = abcdef
float v = 0.01

Process finished with exit code 0

```





### strong enum

> 强类型enum不会隐式转换为int
>
> 强类型enum默认无法开放式访问，需要使用using enum解开访问

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

enum A {
  A1 = 100, A2, A3
};

//强类型enum不会隐式转换为int
enum class B {
  B1 = 10000, B2, B3
};

int main() {

  int a = A1;
//  int b = B::B1; //error, 编译失败

  std::cout << A1 << std::endl;

  {
    using enum B; //c++20强类型enum特性
    std::cout << static_cast<int>(B1) << std::endl;
  }

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\strong_enum\test-strong_enum.exe
100
10000

Process finished with exit code 0

```



### string_view

> string_view可减少字符串复制

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <string>
#include <string_view>

//string_view可减少字符串复制

int main() {

  std::string s{"abcdefghijk"};
  std::string s1 = s;
  std::string s2 = s;
  printf("s.data() = %p\n", s.data());
  printf("s1.data() = %p\n", s1.data());
  printf("s2.data() = %p\n", s2.data());

  std::string_view sv1 = s;
  std::string_view sv2 = s;
  printf("sv1.data() = %p\n", sv1.data());
  printf("sv2.data() = %p\n", sv2.data());

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\string_view\test-string_view.exe
s.data() = 0000001c335ffbe0
s1.data() = 0000001c335ffbc0
s2.data() = 0000001c335ffba0
sv1.data() = 0000001c335ffbe0
sv2.data() = 0000001c335ffbe0

Process finished with exit code 0

```



### std::span

> 高效便捷访问连续内存的实例对象



```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <span>
#include <array>
#include <vector>
#include <string>
#include <algorithm>

//高效便捷访问连续内存的实例对象

template<typename T, std::size_t N>
constexpr void for_each_span(std::span<T, N> _span) {
  std::for_each(_span.begin(), _span.end(), [](auto &&e) {
    std::cout << e << "\t";
  });
  std::cout << "\n";
}

constexpr void for_each_span(auto &&_span) {
  std::for_each(_span.begin(), _span.end(), [](auto &&e) {
    std::cout << e << "\t";
  });
  std::cout << "\n";
}

int main() {

  std::array<int, 6> arr{1, 2, 3, 4, 5, 6};
  for_each_span(std::span{arr});

  std::vector<std::string> vec{"123", "abc", "ABC", "456", "def", "DEF"};
  for_each_span(std::span{vec});

  constexpr char const *const carr[]{"11", "22", "33", "44", "55","66l"};
  for_each_span(std::span{carr});

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\span\test-span.exe
1       2       3       4       5       6
123     abc     ABC     456     def     DEF
11      22      33      44      55

Process finished with exit code 0

```





### std::optional&std::expected

> 有状态的返回值
>  std::optional 异常值只能为std::null_opt
>  std::expected 可自定义异常值

```c++
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



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\optional_expected\test-optional_expected.exe
optional-------------------------------------------------------
abc
res1 error handle
res1.value_or=xxx
res1.value_or=abc
res2 error handle
expected-------------------------------------------------------
1234567890
res1 error handlebad access to std::expected without expected value, error code: 15
res1.value_or=xxx
res1.value_or=1234567890
res2 error handle, error code: 96

Process finished with exit code 0

```





### std::integer_sequence

> 类模板 std::integer_sequence 表示一个编译时的整数序列。在用作函数模板的实参时，能推导参数包 Ints 并将它用于包展开
> 1、可以定义一个编译时整数序列
> 2、包展开可用作元函数实参

```c++
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



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\integer_sequence\test-integer_sequence.exe
i_seq1= [ 3     46      3       9       22       ]
i_seq2= [ 0     1       2        ]
idx_seq= [ 0    1       2       3       4       5       6       7       8       9        ]
index_sequence_for= [ 0 1       2        ]
[ 1, a, 123, 0.123, 0.987, abcdef ]
print_tuple t1= [ 1     a       123     0.123   0.987   abcdef  1234567890       ]
print_tuple2 t2= [ 1    a       123     0.123   0.987   abcdef   ]

Process finished with exit code 0

```





### 可变参数模板

> 可定义一个编译时参数类型包

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>
#include <optional>
#include <utility>

template<typename T, T ...ts>
constexpr
std::optional<T> foo() {
  if (!sizeof...(ts)) return std::nullopt;
  using res_type = std::decay_t<T>;
  res_type res{};
  ((res += ts), ...);
  return res;
}

template<typename T, T ...ts>
struct sum {
  using value_type = std::decay_t<T>;
 private:
  inline static value_type v{};
 public:
  inline static value_type const value = ((v += ts), ...);
};

template<typename T, T ...ts>
inline std::decay_t<T> const sum_v = sum<T, ts...>::value;

int main() {

  if (auto ret = foo<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>()) {
    std::cout << "return value: " << *ret;
  } else {
    //error handle
    std::cout << "error handle\n";
  }

  std::cout << "\nsum = " << sum<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>::value;
  std::cout << "\nsum_t = " << sum_v<int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0>;
}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\template_types\test-template_types.exe
return value: 45
sum = 45
sum_t = 45
Process finished with exit code 0

```



### 内存对齐

> 字节对齐能提高CPU访问内存效率

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

/*
 * 字节对齐能提高CPU访问内存效率
 *
 * */

struct A { //默认8字节对齐   : 16
  char c;
  bool b;
  short sn;
  double d;
};

struct B {//: 24
  char c;
  bool b;
  alignas(8) short sn;
  double d;
};

struct C { //32
  char c;
  alignas(8) bool b;
  alignas(8) short sn;
  double d;
};

struct D { //32
  alignas(8) char c;
  alignas(8) bool b;
  alignas(8) short sn;
  double d;
};

struct E { //16
  alignas(8) char c; //1
  bool b;  //1
  short sn; //2
  double d;
};

int main() {

  std::cout << "char = " << sizeof(char) << "\n";
  std::cout << "bool = " << sizeof(bool) << "\n";
  std::cout << "short = " << sizeof(short) << "\n";
  std::cout << "int = " << sizeof(int) << "\n";
  std::cout << "long int = " << sizeof(long int) << "\n";
  std::cout << "long long int = " << sizeof(long long int) << "\n";
  std::cout << "float = " << sizeof(float) << "\n";
  std::cout << "double = " << sizeof(double) << "\n";
  std::cout << "struct A = " << sizeof(A) << "\n";
  std::cout << "struct B = " << sizeof(B) << "\n";
  std::cout << "struct C = " << sizeof(C) << "\n";
  std::cout << "struct D = " << sizeof(D) << "\n";
  std::cout << "struct E = " << sizeof(E) << "\n";

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\alignas\test-alignas.exe
char = 1
bool = 1
short = 2
int = 4
long int = 4
long long int = 8
float = 4
double = 8
struct A = 16
struct B = 24
struct C = 32
struct D = 32
struct E = 16

Process finished with exit code 0

```



### std::is_same

> 元函数
>
> 判断两个类型是否相同

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

template<auto T, auto U>
inline constexpr
auto add() {
  std::cout << __DATE__ << __TIMESTAMP__ << __FUNCTION__ << "\n";
  return T + U;
}

class A {
 public:
  auto add(int a, int b) {
    std::cout << __DATE__ << __TIMESTAMP__ << __FUNCTION__ << "\n";
    return a + b;
  }

};

int main() {

  constexpr bool v = std::is_same_v<decltype(add<3, 1>()), double>;
  std::cout << v << "\n";

//  std::declval不构造对象调用成员函数  decay_t去除类型修饰
  constexpr bool v2 = std::is_same_v<std::decay_t<decltype(std::declval<A>().add(1, 4))>, int>;
  std::cout << v2 << "\n";

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\SFINAE\test-SFINAE.exe
call 1
hello A
call 2
hello A
大保底
A::print pointer: 00000017befff8a0 

Process finished with exit code 0

```



### conditional

> 元函数
>
> 根据条件选择类型

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include <type_traits>

class A {
 public:
  inline void print() const {
    std::cout << "print A" << "\n";
  }
};

class B {
 public:
  inline void print() const {
    std::cout << "print B" << "\n";
  }
};

template<bool _cond>
class T : public std::conditional_t<_cond, A, B> {};

template<bool _cond, typename T, typename U>
struct conditional {
  using type = T;
};

template<typename T, typename U>
struct conditional<false, T, U> {
  using type = U;
};

template<bool cond, typename T, typename U>
using conditional_t = typename conditional<cond, T, U>::type;

template<bool _cond>
class T2 : public conditional_t<_cond, A, B> {};

int main() {

  T<true>().print();
  T<false>().print();

  T2<true>().print();
  T2<false>().print();

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\conditional\test-conditional.exe
print A
print B
print A
print B

Process finished with exit code 0

```







# ASIO

## 定时器

### 异步

#### 异步定时任务

```c++
//
// Created by oz on 23-9-9.
//
#include <iostream>
#include <boost/asio.hpp>
#include <array>

using namespace std::chrono;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost;

static void Print(boost::system::error_code ec) {
    std::cout << "Hello, world!" << std::endl;
}

static void async_timer() {

    boost::asio::io_context ioc;
    boost::asio::steady_timer timer(ioc, 3s);
    timer.async_wait(&Print);
    ioc.run();

}

int main(){
    async_timer();
}




####output
Hello, world!
```



## TCPIP

### TCP

#### echo_server

```c++
//
// Created by oz on 23-9-9.
//
#include <iostream>
#include <boost/asio.hpp>
#include <array>

using namespace std::chrono;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost;

enum {
    BUF_SIZE = 1024,
    TCP_PORT = 8080
};

static void Session(tcp::socket socket) {
    try {
        while (true) {
            std::array<char, BUF_SIZE> data{};

            boost::system::error_code ec;
            std::size_t length = socket.read_some(boost::asio::buffer(data), ec);

            if (ec == boost::asio::error::eof) {
                std::cout << "client close" << std::endl;
                break;
            } else if (ec) {
                throw boost::system::system_error(ec);
            }

            boost::asio::write(socket, boost::asio::buffer(data, length));
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

static void echo_server() {

    boost::asio::io_context ioc;

    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), TCP_PORT));

    try {
        while (true) {
            Session(acceptor.accept());
        }
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}


int main() {

    echo_server();

}



####output
(base) oz@ubuntu:~/WK/asio/test$ nc localhost 8080
hello
hello

```





# Sort



## 冒泡排序

```c++
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



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\sort\test-sort.exe
76574	899	356	99	77	43	23	9	9	7	6	3	1	
Process finished with exit code 0

```





# 冷知识

## 在C中定义struct的私有成员

> 核心知识点：
>
> 1、struct指针指向的地址是struct第一个成员的地址
>
> 2、union可以实现指针的多态

**info_struct_c.h**

```c++
//
// Created by ozcom on 2023/11/6.
//

#ifndef CPP_FEATURE_DEMO_PROVITE_MEMBER_STRUCT_C_INFO_STRUCT_C_H_
#define CPP_FEATURE_DEMO_PROVITE_MEMBER_STRUCT_C_INFO_STRUCT_C_H_

extern "C" {

typedef struct info {} info_t;

info_t *create_info(char const *name, int age);

int get_age(info_t const *info);
char const *get_name(info_t const *info);

void set_age(info_t const *info, int age);
void set_name(info_t const *info, char const *name);

}

#endif //CPP_FEATURE_DEMO_PROVITE_MEMBER_STRUCT_C_INFO_STRUCT_C_H_

```



 **info_struct_c.cpp**

```c++
//
// Created by ozcom on 2023/11/6.
//

extern "C" {

#include "info_struct_c.h"

#include <malloc.h>
#include <strings.h>

typedef struct info_impl {
  union { //多态
    info_t *p;
    int *_p;
  };
  int age;
  char *name;
} info_impl_t;

info_t *create_info(const char *name, int age) {

  info_impl_t *impl = (info_impl_t *) malloc(sizeof(info_impl));
  impl->age = age;
  impl->name = (char *) malloc(strlen(name) + 1);
  strcpy(impl->name, name);

  return (info_t *) impl;
}

int get_age(const info_t *info) {
  info_impl_t *impl = (info_impl_t *) info;
  return impl->age;
}

char const *get_name(const info_t *info) {
  info_impl_t *impl = (info_impl_t *) info;
  return impl->name;
}

void set_age(const info_t *info, int age) {
  info_impl_t *impl = (info_impl_t *) info;
  impl->age = age;
}

void set_name(const info_t *info, const char *name) {
  info_impl_t *impl = (info_impl_t *) info;

  if (strlen(name) == strlen(impl->name)) {
    strcpy(impl->name, name);
  } else {
    free(impl->name);
    impl->name = (char *) malloc(strlen(name) + 1);
    strcpy(impl->name, name);
  }

}

}




```



 **main.cpp**

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>
#include "info_struct_c.h"

int main() {

  info_t *info = create_info("abcd", 10);
  printf("info{ name=%s, age = %d }\n", get_name(info), get_age(info));

  set_name(info, "一只快乐的喵");
  set_age(info, 123);
  printf("info{ name=%s, age = %d }\n", get_name(info), get_age(info));

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\provite_member_struct_c\test-provite_member_struct_c.exe
info{ name=abcd, age = 10 }
info{ name=一只快乐的喵, age = 123 }

Process finished with exit code 0

```



## struct不定长数组的实现

> 核心知识点：
>
> 1、数组在struct中指向的是一个固定的地址
>
> 2、无长度数组是一个指向固定地址的指针

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

extern "C" {

#include <malloc.h>
#include <strings.h>

typedef struct message {
  int type;
  int id;
  int len;
  char data[];
} message_t;

}

int main() {

  char const data[]{"1111111111111111111111111111111111111111111111111"
                    "2222222222222222222222222222222222222222222222222"
                    "3333333333333333333333333333333333333333333333333"
                    "4444444444444444444444444444444444444444444444444"
                    "5555555555555555555555555555555555555555555555555"
                    "6666666666666666666666666666666666666666666666666"
                    "7777777777777777777777777777777777777777777777777"
                    "8888888888888888888888888888888888888888888888888"
                    "9999999999999999999999999999999999999999999999999"
                    "0000000000000000000000000000000000000000000000000"
                    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                    "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
                    "ccccccccccccccccccccccccccccccccccccccccccccccccc"};

  printf("data str len: %zu\n", strlen(data));
  printf("data size: %zu\n", sizeof(data));

  const int data_len = sizeof(data);
  const int msg_len = sizeof(message) + data_len;
  message_t *msg = (message_t *) malloc(msg_len);
  msg->type = 1;
  msg->id = 0xff0;
  msg->len = data_len;
  memcpy(msg->data, data, data_len);

  printf("message{ type=%d, id=%d, len=%d, data=%s }\n", msg->type, msg->id, msg->len, msg->data);

  char data2[]{"123"};
  msg->len = sizeof(data2);
  memcpy(msg->data, data2, msg->len);
  printf("message{ type=%d, id=%d, len=%d, data=%s }\n", msg->type, msg->id, msg->len, msg->data);

}



####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\zore_arr_struct\test-zore_arr_struct.exe
data str len: 637
data size: 638
message{ type=1, id=4080, len=638, data=1111111111111111111111111111111111111111111111111222222222222222222222222222222222222222222222222233333333333333333333333333333333333333333333333334444444444444444444444444444444444444444444444444555555555555555555555555555555555555555555555555566666666666666666666666666666666666666666666666667777777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888888899999999999999999999999999999999999999999999999990000000000000000000000000000000000000000000000000aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccc }
message{ type=1, id=4080, len=4, data=123 }

Process finished with exit code 0

```



## -1在怎样的情况下会大于正整数

> 核心知识点：
>
> 1、在逻辑运算中若存在有符号整型和无符号整数，有符号整数会隐式转换为无符号整型，然后再进行比较
>
> 2、在c/c++逻辑比较中应该避免使用无符号整型

```c++
 //
// Created by ozcom on 2023/9/28.
//

#include <iostream>

int main() {

  int a = -1;
  auto a_size = sizeof(a);
  printf("a_size=%llu\n", a_size);

  if (a > a_size) {
    printf("大于\n");
  } else {
    printf("小于\n");
  }

  auto ua = static_cast<unsigned int>(a);
  printf("ua=%u\n", ua);

}


####output
D:\WK\cpp\cpp_feature_demo\cmake-build-debug\how_negative_greater_unsigned_int_c\test-how_negative_greater_unsigned_int_c.exe
a_size=4
大于
ua=4294967295

Process finished with exit code 0

```



## 只能在Stack或Heap上创建的对象

> 核心知识点：
>
> 1、在Stack上创建的对象，会自动调用析构函数
>
> 2、在Heap上创建的对象，需要使用new关键字创建，调用析构函数需要手动使用delete关键字
>
> 3、只要阻止对应的创建过程或者销毁过程，就能实现只能在Stack或Heap上创建的对象

### 只能在Stack

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>


class Foo {

 public:
  void *operator new(std::size_t count) = delete;   //方法1
  void *operator new[](std::size_t count) = delete;

// private:
//  void *operator new(std::size_t count) {   //方法2
//    return ::operator new(count);
//  }
//
//  void *operator new[](std::size_t count) {
//    return ::operator new[](count);
//  }


};


int main() {

  Foo foo{};
//  Foo *pFoo = new Foo{};  //compile error

}
```

### 只能在Heap

```c++
//
// Created by ozcom on 2023/9/28.
//

#include <iostream>

class Foo {

 public:
  ~Foo() = delete;  //方法1

  void release() {
    //recycle memory
  }

// private:
//  ~Foo() = default;   //方法2

};

int main() {

//  Foo foo{};  //compile error
  Foo *pFoo = new Foo{};
  pFoo->release();

}
```
