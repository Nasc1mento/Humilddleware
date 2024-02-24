#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "humilddleware.h"

static int _fd = -1;
static Broker _broker = {0};
static Config _config = {0};

int run(Broker broker, Config config) {

    _broker = broker;
    _config = config;

    struct sockaddr_in dst;
    memset(&dst, 0, sizeof(dst));

    if (inet_pton(AF_INET, broker.addr, &dst.sin_addr) <= 0) {
        fprintf(stderr,"Failed to convert IP address: %s:%i",_broker.addr,_broker.port);
        return -1;
    }
    
    dst.sin_family = AF_INET;
    dst.sin_port = htons(_broker.port);

    if ((_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0) {
        perror("Failed to create socket instance");
        return -1;
    }

    if (connect(_fd, (struct sockaddr *)&dst, sizeof(dst)) != 0) {
        fprintf(stderr,"Failed to connect to %s:%i", _broker.addr,_broker.port);
        close(_fd);
        return -1;
    }
    return _fd;
}

inline int send_data(const char *payload, size_t len) {
    if (!payload) {
        perror("No payload");
        return -1;
    }

    ssize_t b = send(_fd, payload, len, 0);

    if (b < 0) {
        perror("Failed to send data");
        return -1;
    }
    
    if ((size_t) b < len) {
        fprintf(stderr, "Imcomplete send, payload length(%i) bigger than specified(%i)",b,len);
        return -1;
    }
    return 0;
}

inline int recv_data(char *buf, size_t len) {
    ssize_t b = recv(_fd, buf, len - 1, 0);

    if (b < 0) {
        perror("Nothing to receive");
        return -1;
    }
    
    if (b == 0) {
        perror("Connection closed by peer");
        return -1;
    }
    return 0;
}


static inline Invocation marshaller(char *buf, size_t len ) {
    

}

static inline char* unmarshaller(Invocation invocation) {

    char buf[MAX_SIZE_BUFFER];
    int r;

    switch (invocation.op)
    {
    case PUBLISH:
        r = snprintf(
            buf, MAX_SIZE_BUFFER, "%s %i" ,
            invocation.op, invocation.msg, invocation.tpc
        );
        break;
    case SUBSCRIBE:
    case UNSUBSCRIBE:
        r = snprintf(
            buf, MAX_SIZE_BUFFER, "%s %i" ,
            invocation.op, 
            invocation.tpc
        );
        break;
    default:
        break;
    }

    buf[r] = '\0';
    
    return buf;
}

static inline int send_command(Invocation invocation) {
    char *buf = unmarshaller(invocation);
    return send_data(buf, strlen(buf));
}

inline int publish(Invocation invocation) {
    if (
        invocation.tpc == NULL ||
        invocation.msg == NULL ||
        invocation.op == NULL
    ) {
        perror("Null value");
        return -1;
    }

    return send_command(invocation);
}

inline int subscribe(Invocation invocation) {
    if (
        invocation.tpc == NULL ||
        invocation.op == NULL
    ) {
        perror("Null value");
        return -1;
    }

    return send_command(invocation);
}