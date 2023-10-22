#ifndef HUMILDDLEEWARE_CLPS_ENGINE_H
#define HUMILDDLEEWARE_CLPS_ENGINE_H

int getfd();
void pub(char *topic, char * msg, int sockfd);
void sub(char *msg, int sockfd);
void unsub(char * topic, int sockfd);


#endif // HUMILDDLEEWARE_CLPS_ENGINE_H