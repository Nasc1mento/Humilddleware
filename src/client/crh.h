#ifndef HUMILDDLEWARE_CLPS_CHR_H
#define HUMILDDLEWARE_CLPS_CHR_H


int crh_run(const char *host, const char *port);

void sendm(int sockfd, char *msg);

char *recvm(int sockfd);


#endif // HUMILDDLEWARE_CLPS_CHR_H