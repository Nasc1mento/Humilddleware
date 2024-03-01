#ifndef SIMPLEMIDDLEWARE_SUBMANAGER_H
#define SIMPLEMIDDLEWARE_SUBMANAGER_H

#include "subscription.h"

void inssub(char* topic, int sockfd);

void unssub(char* topic, int sockfd);


#endif //SIMPLEMIDDLEWARE_SUBMANAGER_H
