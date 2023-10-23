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