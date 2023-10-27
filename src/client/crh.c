#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "crh.h"

#define PORT "4444" // the port client will be connecting to
#define MAXDATASIZE 536 // max number of bytes we can get at once

// get sockaddr, IPv4 or IPv6:
static void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// TODO: dar uma olhadinha aqui depois
int crh_run() {
    int sockfd;

    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    const char *host = "127.0.0.1"; // Change to const char

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(host, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv)); // Use gai_strerror to get a string representation of the error
        return 1;
    }

    p = servinfo;

    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
        perror("client: socket");
        return -1; // Handle the error appropriately
    }

    if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
        perror("client: connect");
        close(sockfd);
        return -1; // Handle the error appropriately
    }

    printf("client: connected\n");
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    return sockfd;
}

void sendm (int sockfd, char * msg) {
    int numbytes;
    if ((numbytes = send(sockfd, msg, strlen(msg), 0)) == -1) {
        perror("send");
        exit(1);
    }
}

char * recvm(int sockfd) {
    int numbytes;
    char * buf = malloc(sizeof(char) * MAXDATASIZE);
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    buf[numbytes] = '\0';

    return buf;
}

