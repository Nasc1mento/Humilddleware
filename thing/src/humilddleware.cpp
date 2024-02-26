#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "humilddleware.h"

static int _fd = -1;
uint8_t attempts;
static Broker _broker = {0};
static Config _config = {0};

static uint8_t run() {
    struct sockaddr_in dst;
    memset(&dst, 0, sizeof(dst));

    if (inet_pton(AF_INET, _broker.ip, &dst.sin_addr) <= 0) {
        fprintf(stderr,"Failed to convert IP address: %s:%i",_broker.ip, _broker.port);
        return IPCONV_ERR;
    }
    
    dst.sin_family = AF_INET;
    dst.sin_port = htons(_broker.port);

    if ((_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0) {
        perror("Failed to create socket instance");
        return INIT_ERR;
    }

    if (connect(_fd, (struct sockaddr *)&dst, sizeof(dst)) != 0) {
        fprintf(stderr,"Failed to connect to %s:%i", _broker.ip, _broker.port);
        close(_fd);
        return CONN_ERR;
    }
    return _fd;
}

static inline uint8_t send_data(const char *payload, size_t len) {
    if (!payload) {
        perror("No payload");
        return NULL_VALUE_ERR;
    }

    ssize_t b = send(_fd, payload, len, 0);

    if (b < 0) {
        perror("Failed to send data");
        return SEND_ERR;
    }
    
    if ((size_t) b < len) {
        fprintf(stderr, "Imcomplete send, payload length(%i) bigger than specified(%i)",b,len);
        return INCOMPLETE_SEND_ERR;
    }
    return HUMILDDLEWARE_OK;
}

static inline uint8_t recv_data(char *buf, size_t len) {
    ssize_t b = recv(_fd, buf, len - 1, 0);

    if (b < 0) {
        perror("Nothing to receive");
        return RECV_ERR;
    }
    
    if (b == 0) {
        perror("Connection closed by peer");
        return RECV_ERR;
    }
    return HUMILDDLEWARE_OK;
}


uint8_t start(const char ip[16], unsigned short int port, Config config) {
    _config = config;
    strcpy(_broker.ip, ip);
    _broker.port = port;
    return run();
}

static inline Invocation unmarshall(char *payload, size_t len) {
    uint8_t code = atoi(strtok(payload, " ")); 
    Operation op = (Operation) code;
    Invocation invocation;

    char *tpc = strtok(payload, " ");
    char *msg;

    switch (op) {
        case PUBLISH:
            msg = strtok(payload, " ");
            invocation.op = op;
            strcpy(invocation.tpc, tpc);
            strcpy(invocation.msg, msg);
            break;
        case SUBSCRIBE:
        case UNSUBSCRIBE:
            invocation.op = op;
            strcpy(invocation.tpc, tpc);
            break;
    }
    return invocation;
}

static inline uint8_t marshall(Invocation invocation, char* buf, int size_buf) {
    int r = -1;
    printf("DutyCicle:%i\n", _config.duty_cicle);

    switch (invocation.op) {
    case PUBLISH:
        r = sprintf(
            buf,"OP:%i\nTPC:%s\nMSG:%s\n",
            invocation.op,
            invocation.tpc,
            invocation.msg
        );
        break;
    case SUBSCRIBE:
    case UNSUBSCRIBE:
        r = sprintf(
            buf,"OP:%i\nTPC:%s\n",
            invocation.op,
            invocation.tpc
        );
        break;
    }

    if (r < 0 || r >= MAX_SIZE_BUFFER) {
        perror("Buffer overflow");
        return BUFFER_OVERFLOW_ERR;
    }

    buf[r] = '\0';
} 

static inline uint8_t send_command(Invocation invocation) {
    char buf[MAX_SIZE_BUFFER];
    marshall(invocation, buf, sizeof(buf));
    return send_data(buf, strlen(buf));
}

uint8_t publish(Invocation invocation) {
    if (
        invocation.msg == NULL ||
        invocation.tpc == NULL
    ) {
        perror("Null value");
        return NULL_VALUE_ERR;
    }
    return send_command(invocation);
}

uint8_t subscribe(Invocation invocation) {
    if (
        invocation.tpc == NULL
    ) {
        perror("Null value");
        return NULL_VALUE_ERR;
    }

    invocation.op = SUBSCRIBE;
    invocation.msg = NULL;
    return send_command(invocation);
}

uint8_t unsubscribe(Invocation invocation) {
     if (
        invocation.tpc == NULL
    ) {
        perror("Null value");
        return NULL_VALUE_ERR;
    }

    invocation.op = UNSUBSCRIBE;
    invocation.msg = NULL;
    return send_command(invocation);
}

uint8_t get_message(char *buf, size_t len) {
    int b = recv_data(buf, len);
    if (b >= 0 && b < len) {
        buf[b] = '\0';
    }

    return b;
}