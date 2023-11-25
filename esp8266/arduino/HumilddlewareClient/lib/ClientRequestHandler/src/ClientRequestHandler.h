//
// Created by afreis on 10/27/23.
//
#ifndef HUMILDDLEWARE_CRH_H
#define HUMILDDLEWARE_CRH_H

#include <Arduino.h>
#include <WiFiClient.h>
#include "Component.h"

#define MAXDATASIZE 536

class ClientRequestHandler: public Component{
  public:
    ClientRequestHandler();
    void run() const override;
    void connect(const char host[16], const uint16_t port);
    void send(char *message);
    void recv(char *buf);
  private:
    WiFiClient client;
};


#endif //HUMILDDLEWARE_CRH_H
