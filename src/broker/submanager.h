//
// Created by afreis on 10/19/23.
//

#ifndef SIMPLEMIDDLEWARE_SUBMANAGER_H
#define SIMPLEMIDDLEWARE_SUBMANAGER_H

typedef struct sub {
    char *topic;
    int sockfd;
};

void inssub(char *topic, int sockfd, struct sub *subscribers[], int *sub_count);

void unssub(char *topic, int sockfd, struct sub *subscribers[], int *sub_count);

#endif //SIMPLEMIDDLEWARE_SUBMANAGER_H
