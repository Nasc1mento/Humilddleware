#ifndef HUMILDDLEEWARE_CLPS_ENGINE_H
#define HUMILDDLEEWARE_CLPS_ENGINE_H

int getfd();
void publish(char *topic, char * msg, int sockfd);
void subscribe(char *msg, int sockfd);
void unsubscribe(char * topic, int sockfd);


#endif // HUMILDDLEEWARE_CLPS_ENGINE_H