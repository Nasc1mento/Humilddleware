//
// Created by afreis on 10/27/23.
//

#include <stddef.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "srh.h"
#include "proxy.h"

static void *run_broker(void *args) {
    srh_run();
    return NULL;
}

static void *run_subscriber(void *args) {
    sleep(2);
    getfd("127.0.0.1", "4444");
    subscribe("topico1");
    return NULL;
}

static void *run_publisher(void *args) {
    sleep(1); // deixar o broker desbrokear
    int fd = getfd("127.0.0.1", "4444");
    while (1 && fd != -1) {
        char *topic = "topic1";
        char *msg = "msg1";
        publish(topic, msg);
        sleep(1);
    }
    return NULL;
}

void run_test() {
    pthread_t broker_thread, publisher_thread, subscriber_thread;


    if (pthread_create(&broker_thread, NULL, run_broker, NULL) != 0) {
        perror("pthread:broker");
        exit(1);
    }

    if (pthread_create(&publisher_thread, NULL, run_publisher, NULL) != 0) {
        perror("pthread:publisher");
        exit(1);
    }

    if (pthread_create(&subscriber_thread, NULL, run_subscriber, NULL) != 0) {
        perror("pthread:subscriber");
        exit(1);
    }

    pthread_join(broker_thread, NULL);
    pthread_join(publisher_thread, NULL);
    pthread_join(subscriber_thread, NULL);
}