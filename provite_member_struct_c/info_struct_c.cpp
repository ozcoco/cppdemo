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



