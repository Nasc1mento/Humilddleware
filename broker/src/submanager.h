//
// Created by afreis on 10/19/23.
//

#ifndef SIMPLEMIDDLEWARE_SUBMANAGER_H
#define SIMPLEMIDDLEWARE_SUBMANAGER_H

typedef struct{
    char * topic;
    int sockfd;
    struct sub * next;
} sub;

void inssub(char * topic, int sockfd);
void remsub(char * topic, int sockfd);
sub * get_subs(char * topic);
int is_subscribed(char * topic, int sockfd);

#endif //SIMPLEMIDDLEWARE_SUBMANAGER_H
