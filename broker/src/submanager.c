//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include <string.h>
#include "submanager.h"

struct sub * subs;

void inssub(char * topic, int sockfd)
{
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
    sub * temp = subs;
    sub * sub_list = NULL;

    while(temp != NULL) {
        if (strcmp(temp->topic, topic) == 0) {
            if (sub_list == NULL) {
                sub_list = malloc(sizeof(sub));
                sub_list->topic = malloc(strlen(topic) + 1);
                strcpy(sub_list->topic, topic);
                sub_list->sockfd = temp->sockfd;
                sub_list->next = NULL;
            } else {
                sub * newsub = malloc(sizeof(sub));
                newsub->topic = malloc(strlen(topic) + 1);
                strcpy(newsub->topic, topic);
                newsub->sockfd = temp->sockfd;
                newsub->next = NULL;
                sub * temp2 = sub_list;
                while (temp2->next != NULL) {
                    temp2 = temp2->next;
                }
                temp2->next = newsub;
            }
        }
        temp = temp->next;
    }
}

int is_subscribed(char * topic, int sockfd)
{
    sub *temp = subs;

    while (temp != NULL && (strcmp(temp->topic, topic) != 0 || temp->sockfd != sockfd))
    {
        temp = temp->next;
    }

    if (temp == NULL) {return 0;}

    return 1;
}