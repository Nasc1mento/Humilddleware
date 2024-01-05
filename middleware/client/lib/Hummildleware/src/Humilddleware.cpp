//
// Created by afreis on 11/25/23.
//
#include "Humilddleware.h"
#include "Configuration.h"
#include <string.h>


char HOST[16];
uint16_t PORT;
Engine Humilddleware::engine;

void Humilddleware::connect(const char host[16], const uint16_t port) {
    strcpy(HOST, host);
    PORT = port;
    engine = Engine();
}

Component* Humilddleware::attached(Component* component) {
    return Humilddleware::engine.attached(component);
}

ClientProxy* Humilddleware::proxy() {
    return (ClientProxy*)Humilddleware::engine.starter();
}

