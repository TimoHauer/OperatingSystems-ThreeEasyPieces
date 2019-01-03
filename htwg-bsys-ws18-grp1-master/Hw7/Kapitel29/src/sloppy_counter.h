#ifndef SLOPPYCOUNTER_H
#define SLOPPYCOUNTER_H

#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#define NUMCPUS 8

typedef struct sloppycounter {
    int global;
    pthread_mutex_t globallock;
    int local[NUMCPUS];
    pthread_mutex_t locallock[NUMCPUS];
    int threshold;
} sloppycounter;

void init(sloppycounter *c, int threshold) {
    c->global = 0;
    c->threshold = threshold;
    pthread_mutex_init(&c->globallock, NULL);
    int i;
    for(i = 0; i < NUMCPUS; i++)
    {
        c->local[i] = 0;
        pthread_mutex_init(&c->locallock[i], NULL);
    }
}

void sloppyUpdate(sloppycounter *c, int threadID, int amt) 
{
    int cpu = threadID % NUMCPUS;
    pthread_mutex_lock(&c->locallock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) 
    {
        pthread_mutex_lock(&c->globallock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->globallock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(&c->locallock[cpu]);
}

int get(sloppycounter *c) 
{
    pthread_mutex_lock(&c->globallock);
    int val = c->global;
    pthread_mutex_unlock(&c->globallock);
    return val;
}

#endif