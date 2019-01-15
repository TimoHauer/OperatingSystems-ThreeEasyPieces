#ifndef COUNTER_H
#define COUNTER_H

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct counter {
    int data;
    pthread_mutex_t lock;
} counter;

void init(counter *c) {
    c->data = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter *c) {
    pthread_mutex_lock(&c->lock);
    c->data++;
    pthread_mutex_unlock(&c->lock);
}

void decrement(counter *c) {
    pthread_mutex_lock(&c->lock);
    c->data--;
    pthread_mutex_unlock(&c->lock);
}

int getVaule(counter *c) {
    pthread_mutex_lock(&c->lock);
    int data = c->data;
    pthread_mutex_unlock(&c->lock);
    return data;
}

#endif