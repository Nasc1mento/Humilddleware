#ifndef HUMILDDLEEWARE_CLPS_ENGINE_H
#define HUMILDDLEEWARE_CLPS_ENGINE_H

#include <netinet/in.h>
#include "crh.h"

int getfd(const char host[INET6_ADDRSTRLEN], const char port[6]);
void publish(char *topic, char * msg);
void subscribe(char *topic);
void unsubscribe(char * topic);


#endif // HUMILDDLEEWARE_CLPS_ENGINE_H