#ifndef HUMILDDLEWARE_H
#define HUMILDDLEWARE_H

#include <unistd.h>

#define MAX_SIZE_BUFFER 100
#define MAX_ATTEMPTS 3
#define HUMILDDLEWARE_OK 0



struct Broker {
    char addr[16];
    uint8_t port;
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
    char tpc[20];
    char msg[70];
    enum Operation op;
};

typedef struct Broker Broker;
typedef struct Config Config;
typedef enum Operation Operation;
typedef struct Invocation Invocation;

int start(Config, Broker);
inline int publish(Invocation);
inline int subscribe(Invocation);

#endif