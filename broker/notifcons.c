#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "notifcons.h"
#include "subscription.h"
#include "submanager.h"

void notify(char *topic, char *msg, int sockfd) {
    size_t len = strlen(msg);
    struct topic* current_topic = topics;

    while (current_topic != NULL) {
        if (strcmp(current_topic->name, topic) == 0) {
            struct subscriber *current_subscriber = current_topic->sub_list;
            while (current_subscriber != NULL) {
                printf("sending to %d\n", current_subscriber->fd);
                if (send(current_subscriber->fd, msg, len, 0) == -1) {
                    unssub(topic, current_subscriber->fd);
                    perror("send");
                }
                current_subscriber = current_subscriber->next;
            }
            return;
        }
        current_topic = current_topic->next;
    }

}
