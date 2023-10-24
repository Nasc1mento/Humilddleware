//
// Created by afreis on 10/18/23.
//

#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include "notifcons.h"
#include "submanager.h"
#include "shared/marshaller.h"

void notify(char *topic, char *msg, int sockfd) {
    if (is_subscribed(topic, sockfd) == 0) {
        inssub(topic, sockfd);
    }

    struct sub *sub_list = get_subs(topic);


    while (sub_list != NULL) {
//        if (sub_list->sockfd != sockfd)
//        {
            size_t len = strlen(msg);
            unsigned char *byteArray = malloc(sizeof(unsigned char) * len);
            marshall(msg, byteArray, strlen(msg));
            if (send(sub_list->sockfd, byteArray, strlen(byteArray), 0) == -1) {
                perror("send");
            }
            free(byteArray);
//        }

        sub_list = sub_list->next;
    }
}
