//
// Created by afreis on 11/26/23.
//
#ifndef HUMILDDLEWARE_H
#define HUMILDDLEWARE_H
#include "Engine.h"
#include "ClientProxy.h"


class Humilddleware {    
    public:
        static Engine engine;
        static void connect(const char host[16], const uint16_t port);
        static Component* attached(Component*);
        static ClientProxy* proxy();
};

#endif //HUMILDDLEWARE_H