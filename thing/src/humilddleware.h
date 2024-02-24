#ifndef HUMILDDLEWARE
#define HUMILDDLEWARE

#include <unistd.h>

#define MAX_SIZE_BUFFER 100
#define MAX_ATTEMPTS 3

typedef struct Broker Broker;
typedef struct Config Config;
typedef struct Invocation Invocation;

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
    UNSUBSCRIBE = 3,
};

struct Invocation {
    char tpc[20];
    char msg[50];
    enum Operation op;
};

inline int run(Config, Broker);
inline int publish(Invocation);
inline int subscribe(Invocation);

#endif