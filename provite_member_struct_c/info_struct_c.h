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
