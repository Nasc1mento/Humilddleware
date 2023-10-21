//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include <string.h>
#include "humilde.h"
#include "notifcons.h"
#include "submanager.h"

void notify(char * topic, char * msg, int sockfd)
{
    if (is_subscribed(topic, sockfd) == 0) {
        inssub(topic, sockfd);
    }

    struct sub *sub_list = get_subs(topic);


    while (sub_list != NULL)
    {
        printf("Topic: %s\n", sub_list->topic);
        if (sub_list->sockfd != sockfd)
        {
            printf("aaaaaaaaaaaaa");
            send(sub_list->sockfd, msg, strlen(msg), 0);
        }
        struct sub *to_free = sub_list;
        sub_list = sub_list->next;
        free(to_free->topic);
        free(to_free);
    }
}
