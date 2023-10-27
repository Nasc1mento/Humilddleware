//
// Created by afreis on 10/23/23.
//
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "broker/srh.h"
#include "client/proxy.h"

//
//static void* broker() {
//    srh_run();
//    return NULL;
//}

//static void* publisher() {
//    sleep(1); // deixar o broker desbrokear
//    int fd = getfd();
//    while (1 && fd != -1) {
//        char *topic = "topic1";
//        char *msg = "msg1";
//        pub(topic, msg, fd);
//        sleep(1);
//    }
//    return NULL;
//}
//
//static void* subscriber() {
//    sleep(2);
//    int fd = getfd();
//    sub("topic1", fd);
//}

int main() {
//    pthread_t broker_thread, publisher_thread, subscriber_thread;
//
//    if (pthread_create(&broker_thread, NULL, broker, NULL) != 0) {
//        perror("pthread:broker");
//        exit(1);
//    }
//
//    if (pthread_create(&publisher_thread, NULL, publisher, NULL) != 0) {
//        perror("pthread:publisher");
//        exit(1);
//    }

//    if (pthread_create(&subscriber_thread, NULL, subscriber, NULL) != 0) {
//        perror("pthread:subscriber");
//        exit(1);
//    }

//    pthread_join(broker_thread, NULL);
//    pthread_join(publisher_thread, NULL);
//    pthread_join(subscriber_thread, NULL);

    srh_run();
    return 0;
}
