//
// Created by afreis on 10/27/23.
//
#include <string.h>
#include "ClientProxy.h"
#include "Humilddleware.h"

void ClientProxy::run(struct Invocation invocation) {}

void ClientProxy::publish(const char *topic, const char *msg) {
    struct Invocation inv = { "PUBLISH", topic, msg };
    Humilddleware::attached(this)->run(inv);
}

void ClientProxy::subscribe(const char *topic) {
   struct Invocation inv = { "SUBSCRIBE", topic, NULL };
    Humilddleware::attached(this)->run(inv);
}

void ClientProxy::unsubscribe(const char *topic) {
    struct Invocation inv = { "UNSUBSCRIBE", topic, NULL };
    Humilddleware::attached(this)->run(inv);
}


