#ifndef HUMILDDLEWARE_CLPS_CHR_H
#define HUMILDDLEWARE_CLPS_CHR_H

#define MAXDATASIZE 536

int crh_run(const char host[INET6_ADDRSTRLEN], const char port[6]);

void sendm(int sockfd, char *msg);

void recvm(int sockfd, char buf[MAXDATASIZE]);

#endif // HUMILDDLEWARE_CLPS_CHR_H