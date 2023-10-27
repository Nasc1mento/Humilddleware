//
// Created by afreis on 10/19/23.
//
#include <stdio.h>
#include <string.h>
#include "notifcons.h"
#include "submanager.h"
#include "subscription.h"

void request(char* buffer, int sockfd) {
    char *op = strtok(buffer, " ");
    if (strcmp(op, "SUBSCRIBE") == 0) {
        char *topic = strtok(NULL, " ");
        inssub(topic, sockfd);
    } else if (strcmp(op, "PUBLISH") == 0) {
        char *topic = strtok(NULL, " ");
        char *msg = strtok(NULL, " ");
        notify(topic, msg, sockfd);
    } else if (strcmp(op, "UNSUBSCRIBE") == 0) {
        char *topic = strtok(NULL, " ");
        unssub(topic, sockfd);
    } else {
        printf("Invalid operation");
    }
}
