//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include <string.h>
#include "submanager.h"

// TODO: List está resetando sempre que o fd manda um mensagem, não entra no else do inssub
// TODO: FAZER ACIMA
// Estudar extern e static pra ver se consigo resolver isso
// Se n der certo, implementar a lista de subs dentro do humilde.c para ver se funciona
struct sub *subs;

void inssub(char *topic, int sockfd) {
    if (subs == NULL) {
        struct sub *newsub = malloc(sizeof(subs));
        newsub->topic = malloc(strlen(topic) + 1);
        strcpy(newsub->topic, topic);
        newsub->sockfd = sockfd;
        newsub->next = NULL;
        subs = newsub;
    } else {
        printf("inssub else\n");
        struct sub *temp = subs;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        struct sub *newsub = malloc(sizeof(subs));
        newsub->topic = malloc(strlen(topic) + 1);
        strcpy(newsub->topic, topic);
        newsub->sockfd = sockfd;
        newsub->next = NULL;
        temp->next = newsub;
    }
}

void remsub(char *topic, int sockfd) {
    struct sub *temp = subs;
    struct sub *prev = NULL;

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

struct sub *get_subs(char *topic) {
    // TODO: retornar subs que tem o topic igual ao passado por parâmetro
    return subs;
}

int is_subscribed(char *topic, int sockfd) {
    struct sub *temp = subs;

    while (temp != NULL && (strcmp(temp->topic, topic) != 0 || temp->sockfd != sockfd)) {
        temp = temp->next;
    }

    if (temp == NULL) { return 0; }

    return 1;
}