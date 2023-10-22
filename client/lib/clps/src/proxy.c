#include <stdio.h>
#include <string.h>
#include "proxy.h"
#include "crh.h"

int getfd() {
    return run();
}

void pub(char *topic, char * msg, int sockfd) {
    int len = strlen(topic) + strlen(msg) + 8;
    char * res = malloc(sizeof(char) * len);
    sprintf(res, "%s %s %s", "PUBLISH", topic, msg);
    sendm(sockfd, res);
    free(res);
}

void sub(char *msg, int sockfd) {
    int len = strlen(msg) + 10;
    char *res = malloc(sizeof(char) * len);
    sprintf(res, "%s %s", "SUBSCRIBE", msg);
    sendm(sockfd, res);
    free(res);
}

void unsub(char * topic, int sockfd) {
    int len = strlen(topic) + 12;
    char *res = malloc(sizeof(char) * len);
    sprintf(res, "%s %s", "UNSUBSCRIBE", topic);
    sendm(sockfd, res);
    free(res);
}