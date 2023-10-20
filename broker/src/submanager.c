//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include <string.h>
#include "submanager.h"

struct sub * subs;

void inssub(char * topic, int sockfd) {
    if (subs == NULL) {
        sub * newsub = malloc(sizeof(sub));
        newsub->topic = malloc(strlen(topic) + 1);
        newsub->sockfd = sockfd;
        newsub->next = NULL;
        subs = newsub;
    } else {
        sub *temp = subs;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        sub * newsub = malloc(sizeof(sub));
        newsub->topic = malloc(strlen(topic) + 1);
        newsub->sockfd = sockfd;
        newsub->next = NULL;
        temp->next = newsub;
    }
}

void remsub(char * topic, int sockfd) {
    sub *temp = subs;
    sub *prev = NULL;

    while (temp != NULL && (strcmp(temp->topic, topic) != 0 || temp->sockfd != sockfd)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return;
    }

    if (prev == NULL) {
        subs = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp->topic);
    free(temp);
}

sub * get_subs(char * topic)
{
    return subs;
}

int is_subscribed(char * topic, int sockfd)
{
    sub *temp = subs;

    while (temp != NULL && (strcmp(temp->topic, topic) != 0 || temp->sockfd != sockfd)) {
        temp = temp->next;
    }

    if (temp == NULL) {
        return 0;
    }

    return 1;
}