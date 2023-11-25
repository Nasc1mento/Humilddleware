//
// Created by afreis on 10/27/23.
//
#ifndef HUMILDDLEWARE_CLIENTPROXY_H
#define HUMILDDLEWARE_CLIENTPROXY_H

#include <Arduino.h>
#include "ClientRequestHandler.h"

class ClientProxy: public Component {
  public:
    void run() const override;
    ClientProxy();
    void connect(const char host[16], const uint16_t port);
    void publish(char *topic, char *msg);
    void subscribe(char *topic);
    void unsubscribe(char *topic);
  private:
    ClientRequestHandler crh;
};


#endif //HUMILDDLEWARE_CLIENTPROXY_H
