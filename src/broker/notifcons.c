//
// Created by afreis on 10/18/23.
//


#include <string.h>
#include "notifcons.h"
#include <sys/socket.h>
#include <stdio.h>
#include "submanager.h"


void notify(char *topic, char *msg, int sockfd, struct sub *subscribers[], int *sub_count) {
    for (int i = 0; i < *sub_count; i++) {
        if (strcmp(subscribers[i]->topic, topic) == 0 && subscribers[i]->sockfd != sockfd) {
            if (send(subscribers[i]->sockfd, msg, strlen(msg), 0) == -1) {
                perror("send");
            }
        }
    }
}
