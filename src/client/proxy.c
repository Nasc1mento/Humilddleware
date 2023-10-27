#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proxy.h"
#include "crh.h"
#include "marshaller.h"

int sockfd = -1;

int getfd(const char *ip, const char *port) {
    return sockfd = crh_run(ip, port);
}

static inline void checkfd() {
    if (sockfd == -1) {
        perror("sockfd: Not initialized");
        exit(1);
    }
}

void publish(char *topic, char *msg) {
    checkfd();
    int len = strlen(topic) + strlen(msg) + 8;
    char *res = malloc(sizeof(char) * len);
    sprintf(res, "%s %s %s", "PUBLISH", topic, msg);
    sendm(sockfd, res);
    free(res);
}

void subscribe(char *msg) {
    checkfd();
    int len = strlen(msg) + 10;
    char *res = malloc(sizeof(char) * len);
    sprintf(res, "%s %s", "SUBSCRIBE", msg);
    sendm(sockfd, res);
    while (1) {
        char *r = recvm(sockfd);
        if (msg != NULL) {
            printf("%s\n", r);
        }
    }
}

void unsubscribe(char *topic) {
    checkfd();
    int len = strlen(topic) + 12;
    char *res = malloc(sizeof(char) * len);
    sprintf(res, "%s %s", "UNSUBSCRIBE", topic);
    sendm(sockfd, res);
    free(res);
}