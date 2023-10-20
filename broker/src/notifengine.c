//
// Created by afreis on 10/19/23.
//
#include <stdio.h>
#include "notifcons.h"
#include "submanager.h"

void request(char *op, char *topic, char *msg, int sockfd)
{

    if (op == "SUBSCRIBE")
    {
        inssub(topic, sockfd);
    }
    else if (op == "PUBLISH")
    {
        notify(op, topic, msg, sockfd);
    }
    else if (op == "UNSUBSCRIBE")
    {
        remsub(topic, sockfd);
    }
    else
    {
        printf("Invalid operation");
    }

}
