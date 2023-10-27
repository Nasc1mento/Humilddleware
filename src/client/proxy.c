#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "proxy.h"
#include "crh.h"
#include "marshaller.h"

int getfd() {
    return crh_run();
}

void publish(char *topic, char *msg, int sockfd) {
    int len = strlen(topic) + strlen(msg) + 8;
    char *res = malloc(sizeof(char) * len);
    sprintf(res, "%s %s %s", "PUBLISH", topic, msg);
    sendm(sockfd, res);
    free(res);
}

void subscribe(char *msg, int sockfd) {
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

void unsubscribe(char *topic, int sockfd) {
    int len = strlen(topic) + 12;
    char *res = malloc(sizeof(char) * len);
    sprintf(res, "%s %s", "UNSUBSCRIBE", topic);
    sendm(sockfd, res);
    free(res);
}