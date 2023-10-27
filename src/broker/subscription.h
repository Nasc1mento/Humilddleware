//
// Created by afreis on 10/26/23.
//

#ifndef HUMILDDLEWARE_SUBSCRIPTION_H
#define HUMILDDLEWARE_SUBSCRIPTION_H

#define BACKLOG 100

struct sub {
    char *topic;
    int sockfd;
};

extern int sub_count;
extern struct sub *subscribers[BACKLOG];


#endif //HUMILDDLEWARE_SUBSCRIPTION_H
