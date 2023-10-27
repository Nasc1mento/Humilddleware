//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include <string.h>
#include "submanager.h"
#include "util.h"


void inssub(char *topic, int sockfd) {
    printf("Inssub\n");
    int i;
    for (i = 0; i < sizeof(subscribers); i++) {
        if (subscribers[i] == NULL) {
            subscribers[i] = malloc(sizeof(struct sub));
            subscribers[i]->topic = topic;
            subscribers[i]->sockfd = sockfd;
            sub_count+=1;
            return;
        }
    }
    printf("Subscribers list is full\n");
}

void unssub(char *topic, int sockfd) {
    int i;
    for (i = 0; i < sizeof(subscribers); i++) {
        if (strcmp(subscribers[i]->topic, topic) == 0 && subscribers[i]->sockfd == sockfd) {
            subscribers[i] = NULL;
            sub_count-=1;
            printf("Unsubscribed from %s\n", topic);
            return;
        }
    }
    printf("Not subscribed to %s\n", topic);
}

