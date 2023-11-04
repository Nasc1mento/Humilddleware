//
// Created by afreis on 10/26/23.
//

#ifndef HUMILDDLEWARE_SUBSCRIPTION_H
#define HUMILDDLEWARE_SUBSCRIPTION_H

struct subscriber {
    int fd;
    struct subscriber *next;
};

struct topic {
    char *name;
    struct subscriber *sub_list;
    struct topic *next;
};

extern struct topic *topics;


#endif //HUMILDDLEWARE_SUBSCRIPTION_H
