//
// Created by afreis on 10/26/23.
//

#ifndef HUMILDDLEWARE_UTIL_H
#define HUMILDDLEWARE_UTIL_H

struct sub {
    char *topic;
    int sockfd;
};

extern int sub_count;
extern struct sub *subscribers[100];


#endif //HUMILDDLEWARE_UTIL_H
