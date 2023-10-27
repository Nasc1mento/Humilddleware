#ifndef HUMILDDLEEWARE_CLPS_ENGINE_H
#define HUMILDDLEEWARE_CLPS_ENGINE_H

int getfd(const char *host, const char *port);
void publish(char *topic, char * msg);
void subscribe(char *msg);
void unsubscribe(char * topic);


#endif // HUMILDDLEEWARE_CLPS_ENGINE_H