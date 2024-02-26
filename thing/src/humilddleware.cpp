#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "humilddleware.h"

#define HOST_ADDR "192.168.0.111"
#define HOST_PORT 8889

static int _fd = -1;
static Config _config = {0};

int run() {
    struct sockaddr_in dst;
    memset(&dst, 0, sizeof(dst));

    if (inet_pton(AF_INET, HOST_ADDR, &dst.sin_addr) <= 0) {
        fprintf(stderr,"Failed to convert IP address: %s:%i",HOST_ADDR, HOST_PORT);
        return IPCONV_ERR;
    }
    
    dst.sin_family = AF_INET;
    dst.sin_port = htons(HOST_PORT);

    if ((_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0) {
        perror("Failed to create socket instance");
        return INIT_ERR;
    }

    if (connect(_fd, (struct sockaddr *)&dst, sizeof(dst)) != 0) {
        fprintf(stderr,"Failed to connect to %s:%i", HOST_ADDR, HOST_PORT);
        close(_fd);
        return CONN_ERR;
    }
    return _fd;
}

static inline int send_data(const char *payload, size_t len) {
    if (!payload) {
        perror("No payload");
        return -1;
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

static inline int recv_data(char *buf, size_t len) {
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


int start(Config config) {
    _config = config;
    
    int ret = run();
    return ret;
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

static inline char* marshall(Invocation invocation, char* buf, int size_buf) {
    int r;
    printf("%i %s %s\n", invocation.op, invocation.tpc, invocation.msg);

    switch (invocation.op) {
    case PUBLISH:
        r = sprintf(
            buf,"%i %s %s",
            invocation.op, 
            invocation.tpc,
            invocation.msg
        );
        break;
    case SUBSCRIBE:
    case UNSUBSCRIBE:
        r = sprintf(
            buf,"%i %s",
            invocation.op, 
            invocation.tpc
        );
        break;
    }

    buf[r] = '\0';
    return buf;
}

static inline int send_command(Invocation invocation) {
    char buf[MAX_SIZE_BUFFER];
    marshall(invocation, buf, sizeof(buf));

    int ret = send_data(buf, strlen(buf));
    return ret;
}

int publish(Invocation invocation) {
    if (
        invocation.msg == NULL ||
        invocation.tpc == NULL
    ) {
        perror("Null value");
        return NULL_VALUE_ERR;
    }
 
    int ret = send_command(invocation);

    return ret;
}

int subscribe(Invocation invocation) {
    if (
        invocation.tpc == NULL
    ) {
        perror("Null value");
        return NULL_VALUE_ERR;
    }

    invocation.op = SUBSCRIBE;
    return send_command(invocation);
}

int unsubscribe(Invocation invocation) {
     if (
        invocation.tpc == NULL
    ) {
        perror("Null value");
        return NULL_VALUE_ERR;
    }

    invocation.op = UNSUBSCRIBE;
    return send_command(invocation);
}