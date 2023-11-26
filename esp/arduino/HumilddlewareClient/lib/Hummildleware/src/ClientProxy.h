//
// Created by afreis on 10/27/23.
//
#ifndef HUMILDDLEWARE_CLIENTPROXY_H
#define HUMILDDLEWARE_CLIENTPROXY_H

#include "Component.h"
#include "Invocation.h"


class ClientProxy: public Component {
  public:
    void run(struct Invocation) override;
    void publish(const char *, const char *);
    void subscribe(const char *);
    void unsubscribe(const char *);
};


#endif // HUMILDDLEWARE_CLIENTPROXY_H
