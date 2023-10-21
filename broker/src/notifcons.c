//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include "notifcons.h"
#include "submanager.h"

void notify(char *topic, char *msg, int sockfd) {
    if (is_subscribed(topic, sockfd) == 0) {
        inssub(topic, sockfd);
    }

    struct sub *sub_list = get_subs(topic);


    while (sub_list != NULL) {
//        if (sub_list->sockfd != sockfd)
//        {
            if (send(sub_list->sockfd, msg, strlen(msg), 0) < 0) {
                perror("send");
            }
//        }

        sub_list = sub_list->next;
    }
}
