#ifndef HUMILDDLEWARE_H
#define HUMILDDLEWARE_H

#include <unistd.h>

#define MAX_SIZE_BUFFER 100
#define MAX_ATTEMPTS 3

#define HUMILDDLEWARE_OK 0
#define IPCONV_ERR 1
#define INIT_ERR 2
#define CONN_ERR 3
#define SEND_ERR 4
#define INCOMPLETE_SEND_ERR 5
#define RECV_ERR 6
#define NULL_VALUE_ERR 7

struct Broker {
    char *host;
    int port;
};

struct Config {
    uint16_t duty_cicle;
};

enum Operation {
    PUBLISH = 1,
    SUBSCRIBE = 2,
    UNSUBSCRIBE = 3
};

struct Invocation {
    Operation op;
    char *tpc;
    char *msg;
};

typedef struct Broker Broker;
typedef struct Config Config;
typedef enum Operation Operarion;
typedef struct Invocation Invocation;


int start(Config, Broker);
int publish(Invocation);
int subscribe(Invocation);
int unsubscribe(Invocation);

#endif