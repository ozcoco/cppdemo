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