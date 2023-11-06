//
// Created by afreis on 10/27/23.
//
#include <sys/_stdint.h>
#include "CRH.h"


void CRH::connect(const char host[16], const uint16_t port) {
    if (this->client.connect(host, port)) {
        Serial.println("Conectou");
    } else {
        Serial.println("Não conectou");
    }
}

void CRH::send(char *message) {
    this->client.print(message);
}

void CRH::recv(char *buf) {
    int bytes_read = this->client.readBytesUntil('\n', buf, MAXDATASIZE);
    buf[bytes_read] = '\0';
}
