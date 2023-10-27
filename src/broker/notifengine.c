//
// Created by afreis on 10/19/23.
//
#include <stdio.h>
#include <string.h>
#include "notifcons.h"
#include "submanager.h"

void request(char* buffer, int sockfd, struct sub *subscribers[], int *sub_count) {
    char *op = strtok(buffer, " ");
    if (strcmp(op, "SUBSCRIBE") == 0) {
        char *topic = strtok(NULL, " ");
        inssub(topic, sockfd, &subscribers, &sub_count);
    } else if (strcmp(op, "PUBLISH") == 0) {
        printf("Published: \n" );
        char *topic = strtok(NULL, " ");
        char *msg = strtok(NULL, " ");
        notify(topic, msg, sockfd, &subscribers, &sub_count);

    } else if (strcmp(op, "UNSUBSCRIBE") == 0) {
        char *topic = strtok(NULL, " ");
        unssub(topic, sockfd, &subscribers, &sub_count);
    } else {
        printf("Invalid operation");
    }
}
