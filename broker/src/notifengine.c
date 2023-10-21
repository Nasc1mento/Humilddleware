//
// Created by afreis on 10/19/23.
//
#include <stdio.h>
#include <string.h>
#include "notifcons.h"
#include "submanager.h"

void request(char *op, char *topic, char *msg, int sockfd) {

    if (strcmp(op, "SUBSCRIBE") == 0) {
        inssub(topic, sockfd);
    } else if (strcmp(op, "PUBLISH") == 0) {
        notify(topic, msg, sockfd);
    } else if (strcmp(op, "UNSUBSCRIBE") == 0) {
        remsub(topic, sockfd);
    } else {
        printf("Invalid operation");
    }

}
