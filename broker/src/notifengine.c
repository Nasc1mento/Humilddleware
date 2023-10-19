//
// Created by afreis on 10/19/23.
//
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include "mom.h"
#include "notifcons.h"

#define PORT "4444"
#define BACKLOG 10
#define BUFFERSZ 1024

// TODO: mover código de socket para "middleware" e ouvir em loop isso aí,
void run ()
{
    struct sockaddr_storage their_addr;
    struct addrinfo hints, *res;
    socklen_t addr_size;
    int status;
    int sockfd, newfd;
    int bytes_recv;
    char* buffer[BUFFERSZ];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo(NULL, PORT, &hints, &res) != 0)) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(0);
    }
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    listen(sockfd, BACKLOG);

    addr_size = sizeof their_addr;
    newfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    printf("%d", newfd);
    bytes_recv = recv(newfd, buffer, sizeof buffer, 0);

    if (bytes_recv == -1)
    {
        perror("recv");
        close(sockfd);
        exit(0);
    }

    buffer[bytes_recv] = "\0";
    printf("msg: %s", buffer);

    close(sockfd);


}

void publish(char* topic, char * msg)
{
    invocation i;
    i.op = "PUBLISH";
    i.topic = topic;
    i.msg = msg;

    notify(&i);
}


void subscribe(char * topic)
{
    invocation i;
    i.op = "SUBSCRIBE";
    i.topic = topic;
    i.msg = NULL;

    notify(&i);
}

void unsubscribe(char * topic)
{
    invocation i;
    i.op = "UNSUBSCRIBE";
    i.topic = topic;
    i.msg = NULL;

    notify(&i);
}