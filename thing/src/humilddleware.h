#ifndef HUMILDDLEWARE_H
#define HUMILDDLEWARE_H

#include <unistd.h>

// Literal Strings = 12 -> OP:\nTPC:\nMSG: + 1(OP)
#define BUF_LEN             536
#define TPC_LEN             50
#define MSG_LEN             473
#define MAX_ATTEMPTS        3

enum Status {
    HUMILDDLEWARE_OK        = 0,
    IPCONV_ERR              = 1,
    INIT_ERR                = 2,
    CONN_ERR                = 3,
    SEND_ERR                = 4,
    INCOMPLETE_SEND_ERR     = 5,
    RECV_ERR                = 6,
    NULL_VALUE_ERR          = 7,
    BUFFER_OVERFLOW_ERR     = 8,
};

// struct HumilddlewareConnection {
//     int fd;
//     unsigned int port;
//     unsigned int active:1;
//     char buffer[BUF_LEN];
// };

struct Broker {
    char ip[IPADDR_STRLEN_MAX];
    unsigned short int port;
};

enum Operation {
    PUBLISH         = 1,
    SUBSCRIBE       = 2,
    UNSUBSCRIBE     = 3
};

struct Invocation {
    Operation op;
    char tpc[TPC_LEN];
    char msg[MSG_LEN];
};

typedef struct Broker Broker;
typedef enum Operation Operation;
typedef struct Invocation Invocation;

uint8_t start(const char *, const unsigned short int);
uint8_t publish(Invocation);
uint8_t subscribe(Invocation);
uint8_t unsubscribe(Invocation);
Invocation invocation(const char *, const char *);
Invocation listen(const char *);

#endif