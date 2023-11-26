//
// Created by afreis on 11/25/23.
//
#include "Engine.h"
#include "ClientProxy.h"
#include "ClientRequestHandler.h"


Engine::Engine() {
    this->components = (struct List* ) malloc(sizeof(struct List));
    this->load_components();
}

void Engine::run(struct Invocation invocation) {
    struct List* l = this->components;
    while (l->component != NULL) {
        l->component->run(invocation);
        l = l->next;
    }
}

void Engine::load_components() {
    struct List* l = this->components;
    l->component = (Component*) new ClientProxy();
    l->next = (struct List*) malloc(sizeof(struct List));
    l = l->next;
    l->component = (Component*) new ClientRequestHandler();
    l->next = (struct List*) malloc(sizeof(struct List));
    l = l->next;
    l->component = NULL;
    l->next = NULL;
}

ClientProxy* Engine::starter() {
    return (ClientProxy*)this->components->component;
}

Component* Engine::attached(Component* component) {
    struct List* l = this->components;
    while (l->next != NULL) {
        if (l->component == component) {
            return l->next->component;
        }
        l = l->next;
    }
    return NULL;
}