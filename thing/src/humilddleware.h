#ifndef HUMILDDLEWARE_H
#define HUMILDDLEWARE_H

#include <unistd.h>
// Literal Strings = 12 -> OP:\nTPC:\nMSG: + OP = 1 -> 1,2,3
#define BUF_LEN 536
#define TPC_LEN 50
#define MSG_LEN 473
#define MAX_ATTEMPTS 3

enum Status {
    HUMILDDLEWARE_OK = 0,
    IPCONV_ERR,
    INIT_ERR,
    CONN_ERR,
    SEND_ERR,
    INCOMPLETE_SEND_ERR,
    RECV_ERR,
    NULL_VALUE_ERR,
    BUFFER_OVERFLOW_ERR,
};

struct Broker {
    char ip[IPADDR_STRLEN_MAX];
    unsigned short int port;
};

struct Config {
    unsigned int duty_cicle;
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

uint8_t start(const char *, unsigned short int);
uint8_t publish(Invocation);
uint8_t subscribe(Invocation);
uint8_t unsubscribe(Invocation);
Invocation invocation(const char *, const char *);
Invocation listen(const char *);

#endif