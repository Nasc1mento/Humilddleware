#ifndef HUMILDDLEWARE_H
#define HUMILDDLEWARE_H

#include <unistd.h>
// Literal Strings = 12 -> OP:\nTPC:\nMSG: + OP = 1 -> 1,2,3
#define BUF_LEN 536
#define TPC_LEN 50
#define MSG_LEN 473
#define MAX_ATTEMPTS 3

#define HUMILDDLEWARE_OK 0
#define IPCONV_ERR 1
#define INIT_ERR 2
#define CONN_ERR 3
#define SEND_ERR 4
#define INCOMPLETE_SEND_ERR 5
#define RECV_ERR 6
#define NULL_VALUE_ERR 7
#define BUFFER_OVERFLOW_ERR 8
#define MARSH_ERROR 9
#define UNMARSH_ERROR 10

struct Broker {
    char ip[IPADDR_STRLEN_MAX];
    unsigned short int port;
};

struct Config {
    unsigned short int duty_cicle;
};

enum Operation {
    PUBLISH = 1,
    SUBSCRIBE = 2,
    UNSUBSCRIBE = 3
};

struct Invocation {
    Operation op;
    char tpc[TPC_LEN];
    char msg[MSG_LEN];
};

typedef struct Broker Broker;
typedef struct Config Config;
typedef enum Operation Operarion;
typedef struct Invocation Invocation;

uint8_t start(const char *, unsigned short int, Config);
uint8_t publish(Invocation);
uint8_t subscribe(Invocation);
uint8_t unsubscribe(Invocation);
Invocation invocation(const char *, const char *);
Invocation listen(const char *);

#endif