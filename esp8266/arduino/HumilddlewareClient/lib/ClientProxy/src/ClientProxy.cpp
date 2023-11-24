//
// Created by afreis on 10/27/23.
//
#include "ClientProxy.h"
#include "ClientRequestHandler.h"

ClientProxy::ClientProxy() {

}

void ClientProxy::connect(const char host[16], const uint16_t port) {
    this->crh.connect(host, port);
}

void ClientProxy::publish(char *topic, char *msg) {
    char r[MAXDATASIZE];
    sprintf(r, "%s %s %s", "PUBLISH", topic, msg);
    this->crh.send(r);
}


void ClientProxy::subscribe(char *topic) {
    char r[MAXDATASIZE];
    sprintf(r, "%s %s", "SUBSCRIBE", topic);
    this->crh.send(r);
    while (1) {
        char buf[MAXDATASIZE];
        this->crh.recv(buf);
        Serial.println(buf);
    }
}

void ClientProxy::unsubscribe(char *topic) {
    char r[MAXDATASIZE];
    sprintf(r, "%s %s", "UNSUBSCRIBE", topic);
    this->crh.send(r);
}
