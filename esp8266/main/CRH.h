
//
// Created by afreis on 10/27/23.
//

#ifndef HUMILDDLEWARE_CRH_H
#define HUMILDDLEWARE_CRH_H
#define MAXDATASIZE 536
#include <Arduino.h>
#include <WiFiClient.h>
#include <sys/_stdint.h>


class CRH {
  public:
    void connect(const char host[16], const uint16_t port);
    void send(char *message);
    void recv(char *buf);
  private:
    WiFiClient client;
};


#endif //HUMILDDLEWARE_CRH_H
