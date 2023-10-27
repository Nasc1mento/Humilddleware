#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proxy.h"

int sockfd = -1;

int getfd(const char host[INET6_ADDRSTRLEN], const char port[6]) {
    return sockfd = crh_run(host, port);
}

static inline void checkfd() {
    if (sockfd == -1) {
        perror("sockfd: Not initialized");
        exit(1);
    }
}

void publish(char *topic, char *msg) {
    checkfd();
    char res[MAXDATASIZE];
    sprintf(res, "%s %s %s", "PUBLISH", topic, msg);
    sendm(sockfd, res);
    free(res);
}

void subscribe(char *topic) {
    checkfd();
    char res[MAXDATASIZE];
    sprintf(res, "%s %s", "SUBSCRIBE", topic);
    sendm(sockfd, res);
    char buf[MAXDATASIZE];
    while (1) {
        recvm(sockfd, buf);
        printf("%s\n", buf);
    }
}

void unsubscribe(char *topic) {
    checkfd();
    char res[MAXDATASIZE];
    sprintf(res, "%s %s", "UNSUBSCRIBE", topic);
    sendm(sockfd, res);
    free(res);
}