//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include <string.h>
#include "submanager.h"
#include "subscription.h"


int sub_count = 0;
struct sub *subscribers[BACKLOG] = {NULL};

void inssub(char *topic, int sockfd) {
    printf("Inssub\n");
    int i;
    for (i = 0; i < BACKLOG; i++) {
        if (subscribers[i] == NULL) {
            subscribers[i] = (struct sub*)malloc(sizeof(struct sub));
            subscribers[i]->sockfd = sockfd;
            subscribers[i]->topic = strdup(topic);
            sub_count += 1;
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
            sub_count -= 1;
            printf("Unsubscribed from %s\n", topic);
            return;
        }
    }
    printf("Not subscribed to %s\n", topic);
}

