#include <sys/socket.h>
#include "humilddleware.h"

static HC run (Broker broker) {
    HC hc;
    struct sockaddr_in dst;
    memset(&dst, 0, sizeof(dst));

    if (inet_pton(AF_INET, broker.ip, &dst.sin_addr) <= 0) {
        fprintf(stderr,"Failed to convert IP address: %s:%i",broker.ip, broker.port);
        hc.status = IPCONV_ERR;
    }
    
    dst.sin_family = AF_INET;
    dst.sin_port = htons(broker.port);

    if ((hc.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0) {
        perror("Failed to create socket instance");
        hc.status = INIT_ERR;
    }

    if (connect(hc.fd, (struct sockaddr *)&dst, sizeof(dst)) != 0) {
        fprintf(stderr,"Failed to connect to %s:%i", broker.ip, broker.port);
        close(hc.fd);
        hc.status = CONN_ERR;
    } else {
        hc.status = HUMILDDLEWARE_OK;
    }
    return hc;
}

static inline uint8_t send_data(const HC *hc, const char *payload, size_t len) {
    if (!payload) {
        perror("No payload");
        return NULL_VALUE_ERR;
    }

    ssize_t b = send(hc->fd, payload, len, 0);

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

static inline uint8_t recv_data(const HC* hc, char *buf, size_t len) {
    ssize_t b = recv(hc->fd, buf, len - 1, 0);

    if (b < 0) {
        perror("Nothing to receive");
        return RECV_ERR;
    }
    
    if (b == 0) {
        perror("Connection closed by peer");
        return RECV_ERR;
    }

    buf[b] = '\0';
    return HUMILDDLEWARE_OK;
}

HC start(const char *ip, const unsigned short int port) {
    Broker broker;
    strcpy(broker.ip, ip);
    broker.port = port;
    return run(broker);
}

static inline Invocation unmarshall(char *payload, size_t len) {
    char *token = strtok(payload, "\n");
    Invocation invocation = {};

    while (token != NULL) {
        if (strncmp(token, "OP:", 3) == 0) {
            sscanf(token, "OP:%d", &invocation.op);
        } else if (strncmp(token, "TPC:", 4) == 0) {
            sscanf(token, "TPC:%[^\n]", &invocation.tpc);
        } else if (strncmp(token, "MSG:", 4) == 0) {
            sscanf(token, "MSG:%[^\n]", &invocation.msg);
        }
        token = strtok(NULL, "\n");
    }
    return invocation;
}

static inline uint8_t marshall(const Invocation* invocation, char* buf, size_t size_buf) {
    int r = -1;

    switch (invocation->op) {
    case PUBLISH:
        r = sprintf(
            buf,"OP:%i\nTPC:%s\nMSG:%s",
            invocation->op,
            invocation->tpc,
            invocation->msg
        );
        break;
    case SUBSCRIBE:
    case UNSUBSCRIBE:
        r = sprintf(
            buf,"OP:%i\nTPC:%s",
            invocation->op,
            invocation->tpc
        );
        break;
    }

    if (r < 0 || r >= BUF_LEN) {
        perror("Buffer overflow");
        return BUFFER_OVERFLOW_ERR;
    }
    return HUMILDDLEWARE_OK;
} 

static inline uint8_t send_command(const HC* hc, const Invocation *invocation) {
    char buf[BUF_LEN];
    marshall(invocation, buf, sizeof(buf));
    return send_data(hc, buf, strlen(buf)); 
}

uint8_t publish(const HC* hc, Invocation *invocation) {
    if (
        invocation->msg == NULL ||
        invocation->tpc == NULL
    ) {
        perror("Null value");
        return NULL_VALUE_ERR;
    }

    invocation->op = PUBLISH;
    return send_command(hc, invocation);
}

uint8_t subscribe(const HC *hc, Invocation *invocation) {
    if (
        invocation->tpc == NULL
    ) {
        perror("Null value");
        return NULL_VALUE_ERR;
    }

    invocation->op = SUBSCRIBE;
    return send_command(hc, invocation);
}

uint8_t unsubscribe(const HC *hc, Invocation *invocation) {
     if (
        invocation->tpc == NULL
    ) {
        perror("Null value");
        return NULL_VALUE_ERR;
    }

    invocation->op = UNSUBSCRIBE;
    return send_command(hc, invocation);
}

Invocation invocation(const char *tpc, const char *msg) {
    Invocation invocation = {};
    tpc == NULL ? strcpy(invocation.tpc, "") : strcpy(invocation.tpc, tpc);
    msg == NULL ? strcpy(invocation.msg, "") : strcpy(invocation.msg, msg);
    return invocation;
}

Invocation listen(const HC *hc, const char *tpc) {
    char buf[BUF_LEN];
    recv_data(hc, buf, sizeof(buf));
    return unmarshall(buf, strlen(buf));
}