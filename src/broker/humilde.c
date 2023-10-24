//
// Created by afreis on 10/19/23.
//
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include "notifengine.h"
#include "humilde.h"
#include "shared/marshaller.h"
#include "submanager.h"

#define PORT "4444"
#define BUFFER 1024
#define BACKLOG 10

// Based on: https://beej.us/guide/bgnet/html/split-wide/client-server-background.html#a-simple-stream-server
void sigchld_handler(int s) {
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

// Based on: https://beej.us/guide/bgnet/html/split-wide/client-server-background.html#a-simple-stream-server
// get sockaddr, IPv4 or IPv6:
static void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

// Based on: https://beej.us/guide/bgnet/html/split-wide/client-server-background.html#a-simple-stream-server
void srh_run() {
    struct sub sublist[BACKLOG];
    unsigned int *sub_count = 0;
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    char *buffer[BUFFER];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while (1) {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,get_in_addr((struct sockaddr *) &their_addr),s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            //
            while(1) {
                int bread = recv(new_fd, buffer, BUFFER, 0);
                if (bread == 0)
                    break;
                if (bread < 0) {
                    perror("recv");
                    exit(1);
                }
                size_t len = strlen(buffer);
                unsigned char *byteArray = malloc(sizeof(unsigned char) * len);
                unmarshall(buffer, byteArray, strlen(buffer));
                printf("server: received '%s'\n", buffer);

                request(buffer, new_fd, sublist, &sub_count);
                printf("sub_count: %d\n", sub_count);
            }

            close(new_fd);
            exit(0);

            //
        }
        close(new_fd);  // parent doesn't need this
    }
}


