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