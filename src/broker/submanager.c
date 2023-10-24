//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include <string.h>
#include "submanager.h"

// TODO: List está resetando sempre que o fd manda um mensagem, não entra no else do inssub
// O fork está criando um novo processo que copia a lista de subscribers, mas não está conseguindo alterar a lista do processo pai
// acho q é isso. Opções: *Pthread* ou SHM

void inssub(char *topic, int sockfd, struct sub *subscribers[], int *sub_count) {
    struct sub *new_sub = malloc(sizeof(struct sub));
    new_sub->topic = topic;
    new_sub->sockfd = sockfd;
    subscribers[*sub_count] = new_sub;
    *sub_count+=1;
    printf("Subscribed to %s\n", topic);
}

void unssub(char *topic, int sockfd, struct sub *subscribers[], int *sub_count) {
    int i;
    for (i = 0; i < sizeof(subscribers); i++) {
        if (strcmp(subscribers[i]->topic, topic) == 0 && subscribers[i]->sockfd == sockfd) {
            subscribers[i] = NULL;
            printf("Unsubscribed from %s\n", topic);
            *sub_count-=1;
            return;
        }
    }
    printf("Not subscribed to %s\n", topic);
}