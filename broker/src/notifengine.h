//
// Created by afreis on 10/19/23.
//

#ifndef SIMPLEMIDDLEWARE_NOTIFENGINE_H
#define SIMPLEMIDDLEWARE_NOTIFENGINE_H

void run();
void publish(char * topic, char * msg);
void subscribe(char * topic);
void unsubscribe(char * topic);

#endif //SIMPLEMIDDLEWARE_NOTIFENGINE_H
