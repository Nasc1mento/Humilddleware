//
// Created by afreis on 10/18/23.
//



#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "notifcons.h"
#include "subscription.h"

void notify(char *topic, char *msg, int sockfd) {
    for (int i = 0; i < sub_count; i++) {
        if (strcmp(subscribers[i]->topic, topic) == 0 && subscribers[i]->sockfd != sockfd) {
            if (send(subscribers[i]->sockfd, msg, strlen(msg), 0) == -1) {
                perror("send");
            }
        }
    }
}
