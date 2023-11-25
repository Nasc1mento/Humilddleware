//
// Created by afreis on 10/27/23.
//
#include "ClientRequestHandler.h"


ClientRequestHandler::ClientRequestHandler() {
    
}

void ClientRequestHandler::run() const {
    
}

void ClientRequestHandler::connect(const char host[16], const uint16_t port) {
    if (this->client.connect(host, port)) {
        Serial.println("Conectou");
    } else {
        Serial.println("Não conectou");
    }
}

void ClientRequestHandler::send(char *message) {
    this->client.print(message);
}

void ClientRequestHandler::recv(char *buf) {
    int bytes_read = this->client.readBytesUntil('\n', buf, MAXDATASIZE);
    buf[bytes_read] = '\0';
}

