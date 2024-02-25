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
        return;
    }

    struct topic* currenttopic = topics;

    while (currenttopic != NULL) {
        if (strcmp(currenttopic->name, topicname) == 0) {
            struct subscriber* current_sub = currenttopic->sub_list;
            while (current_sub->next != NULL) {
                if (current_sub->fd == sockfd) {
                    return;
                }
                current_sub = current_sub->next;
            }

            struct subscriber *s = (struct subscriber*) malloc(sizeof (struct subscriber));
            s->fd = sockfd;
            s->next = NULL;
            current_sub->next = s;
            return;
        }

        if (currenttopic->next == NULL) {
            struct topic* t = (struct topic*)malloc(sizeof(struct topic));
            t->name = strdup(topicname);
            t->next = NULL;
            struct subscriber *s = (struct sub*)malloc(sizeof (struct subscriber));
            s->fd = sockfd;
            s->next = NULL;
            t->sub_list = s;
            currenttopic->next = t;
            return;
        }
        currenttopic = currenttopic->next;
    }
}

// Função interrompendo o programa de forma inesperada
// TODO: Estudar sobre concoorrência e mutex
void unssub(char *topic, int sockfd) {
    struct topic* currenttopic = topics;
    while (currenttopic != NULL) {
        if (strcmp(currenttopic->name, topic) == 0) {
            struct subscriber* current_sub = currenttopic->sub_list;
            if (current_sub->fd == sockfd) {
                currenttopic->sub_list = current_sub->next;
                free(current_sub);
                current_sub = NULL;
                return;
            }
            while (current_sub->next != NULL) {
                if (current_sub->next->fd == sockfd) {
                    struct subscriber* s = current_sub->next;
                    current_sub->next = current_sub->next->next;
                    free(s);
                    s = NULL;
                    return;
                }
                current_sub = current_sub->next;
            }
        }
        currenttopic = currenttopic->next;
    }
}


