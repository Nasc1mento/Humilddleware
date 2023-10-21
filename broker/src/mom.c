//
// Created by afreis on 10/19/23.
//

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "notifengine.h"

#define PORT "4444"
#define BUFFER 1024
#define BACKLOG 10


void run()
{
    struct sockaddr_storage their_addr;
    struct addrinfo hints, *res;
    int sockfd, newfd;
    socklen_t addr_size;
    char * buffer[BUFFER];
    int bytes_recv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PORT, &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    bind(sockfd, res->ai_addr, res->ai_addrlen);

    listen(sockfd, BACKLOG);


    addr_size = sizeof their_addr;
    newfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    bytes_recv = recv(newfd, buffer, sizeof buffer, 0);

    if (bytes_recv == -1)
    {
        perror("recv");
        close(sockfd);
        exit(0);
    }

    buffer[bytes_recv] = "\0";
    char * op, * topic, * msg;
    op = strtok(buffer, " ");
    topic = strtok(NULL, " ");
    msg = strtok(NULL, " ");

    printf("op: %s, topic: %s, msg: %s", op, topic, msg);
    request(op, topic, msg, newfd);
}


