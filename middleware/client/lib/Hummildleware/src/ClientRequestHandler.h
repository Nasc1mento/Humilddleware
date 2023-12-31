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
    WiFiClient client;
    void run(struct Invocation inv) override;   
    void connect();
    void send(const char*);
    void recv(char *buf);
};


#endif //HUMILDDLEWARE_CRH_H
