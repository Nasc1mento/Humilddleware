//
// Created by afreis on 10/27/23.
//
#include "ClientRequestHandler.h"
#include "Configuration.h"

ClientRequestHandler::ClientRequestHandler() {
    this->connect();
}

void ClientRequestHandler::connect() {
    if (!this->client.connect(HOST, PORT)) {
        Serial.println("Connection failed");
    }
}

void ClientRequestHandler::run(struct Invocation inv) {
    const char* op = inv.op;
    char buf[MAXDATASIZE];
    sprintf(buf, "%s %s %s", op, inv.topic, inv.msg);

    if (strcmp(op, "PUBLISH") == 0) {
        this->send(buf);
    } else if (strcmp(op, "SUBSCRIBE") == 0) {
        this->send(buf);
        this->recv(buf);
    } else if (strcmp(op, "UNSUBSCRIBE") == 0) {
        this->send(buf);
    }
}

void ClientRequestHandler::send(const char *message) {
    this->client.print(message);
}

void ClientRequestHandler::recv(char *buf) {
    while (this->client.available()) {
        char r = this->client.readBytesUntil('\n', buf, MAXDATASIZE);
        buf[r] = '\0';
        Serial.println(buf);
    }
}

