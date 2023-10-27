//
// Created by afreis on 10/27/23.
//

#ifndef HUMILDDLEWARE_CLIENTPROXY_H
#define HUMILDDLEWARE_CLIENTPROXY_H

#include "CRH.h"

class ClientProxy{
  public:
    ClientProxy();
    void connect(const char* host, const char* port);
    void publish(char *topic, char *msg);
    void subscribe(char *topic);
    void unsubscribe(char *topic);
  private:
    CRH crh;
};


#endif //HUMILDDLEWARE_CLIENTPROXY_H
