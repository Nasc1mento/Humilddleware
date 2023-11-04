//
// Created by afreis on 10/18/23.
//
#include <string.h>
#include <malloc.h>
#include "submanager.h"
#include "subscription.h"

struct topic *topics = NULL;


void inssub(char *topicname, int sockfd) {
    if (topics == NULL) {
        struct topic* t = (struct topic*)malloc(sizeof(struct topic));
        t->name = strdup(topicname);
        t->next = NULL;
        struct subscriber *s = (struct sub*)malloc(sizeof (struct subscriber));
        s->fd = sockfd;
        s->next = NULL;
        t->sub_list = s;
        topics = t;
        printf("Subscribed to topic: %s\n",topics->name );
        return;
    }
    printf("morra\n");
    struct topic* currenttopic = topics;

    while (currenttopic != NULL) {
        if (strcmp(currenttopic->name, topicname) == 0) {
            struct subscriber* current_sub = currenttopic->sub_list;
            while (current_sub->next != NULL) {
                if (current_sub->fd == sockfd) {
                    printf("Already subscribed!!!\n");
                    return;
                }
                current_sub = current_sub->next;
            }

            struct subscriber *s = (struct subscriber*) malloc(sizeof (struct subscriber));
            s->fd = sockfd;
            s->next = NULL;
            current_sub->next = s;
            printf("Subscribed aaaaaaaaaaaaaaaaato topic: %s", topicname);
            return;
        } else if (currenttopic->next == NULL) {
            struct topic* t = (struct topic*)malloc(sizeof(struct topic));
            t->name = strdup(topicname);
            t->next = NULL;
            struct subscriber *s = (struct sub*)malloc(sizeof (struct subscriber));
            s->fd = sockfd;
            s->next = NULL;
            t->sub_list = s;
            currenttopic->next = t;
            printf("Subscribed to topic: %s\n",t->name );
            return;
        }
        currenttopic = currenttopic->next;
    }
}

void unssub(char *topic, int sockfd) {

}


