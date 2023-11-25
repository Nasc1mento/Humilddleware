//
// Created by afreis on 11/25/23.
//
#ifndef ENGINE_H
#define ENGINE_H

#include <Arduino.h>
#include "ClientRequestHandler.h"
#include "ClientProxy.h"
#include "Component.h"

struct List {
    Component* component;
    Component* next;
};

class Engine {
    public:
        Engine();
        void run();
        List* load_components();
        Component* attached();     
};

#endif // ENGINE_H