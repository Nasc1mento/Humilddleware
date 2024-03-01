#include <stdio.h>
#include <string.h>
#include "notifcons.h"
#include "submanager.h"

void request(char *buffer, int sockfd) {
    char *op = strtok(buffer, " ");
    if (strcmp(op, "1") == 0) {
        char *topic = strtok(NULL, " ");
        printf("Topic: %s\n", topic);
        inssub(topic, sockfd);
    } else if (strcmp(op, "2") == 0) {
        char *topic = strtok(NULL, " ");
        char *msg = strtok(NULL, " ");
        notify(topic, msg, sockfd);
    } else if (strcmp(op, "3") == 0) {
        char *topic = strtok(NULL, " ");
        unssub(topic, sockfd);
    } else {
        printf("Invalid operation");
    }
}
