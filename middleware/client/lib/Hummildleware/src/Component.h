//
// Created by afreis on 11/25/23.
//
#ifndef COMPONENT_H
#define COMPONENT_H

#include "Invocation.h"

class Component {
    public:
        virtual void run(struct Invocation) = 0;
};

#endif // COMPONENT_H