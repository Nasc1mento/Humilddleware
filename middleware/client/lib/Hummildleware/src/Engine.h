//
// Created by afreis on 11/25/23.
//
#ifndef HUMILDDLEWARE_ENGINE_H
#define HUMILDDLEWARE_ENGINE_H

#include <stdlib.h>
#include "ClientProxy.h"
#include "Component.h"
#include "Invocation.h"

struct List {
    Component* component;
    List* next;
};

class Engine {
    public:
        List* components;
        Engine();
        void run(struct Invocation invocation);
        void load_components();
        ClientProxy* starter();
        Component* attached(Component* component);
};

#endif // ENGINE_H