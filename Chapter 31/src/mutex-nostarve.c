#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {
    sem_t t1;
    sem_t t2;
    sem_t lock;
    int room1, room2;
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m) {
    sem_init(&m->t1, 0, 1);
    sem_init(&m->t2, 0, 0);
    sem_init(&m->lock, 0, 1);
    m->room1 = m->room2 = 0;
}

void ns_mutex_acquire(ns_mutex_t *m, int id) {
    sem_wait(&m->lock);
    printf("child %d tries to acquire the mutex\n", id);
    m->room1++;
    sem_post(&m->lock);
    sem_wait(&m->t1);
    m->room2++;             //
    sem_wait(&m->lock);
    m->room1--;
    if (m->room1 == 0) {
        sem_post(&m->lock);
        sem_post(&m->t2);
    } else {
        sem_post(&m->lock);
        sem_post(&m->t1);
    }
    sem_wait(&m->t2);
    m->room2 -= 1;
    printf("child %d acquired the mutex\n", id);
}

void ns_mutex_release(ns_mutex_t *m) {
    if (m->room2 == 0) {
        sem_post(&m->t1);
    } else {
        sem_post(&m->t2);
    }
}

typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

ns_mutex_t ns_mutex;

void *worker(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    ns_mutex_acquire(&ns_mutex, t->thread_id);
    printf("child %d works\n", t->thread_id);
    ns_mutex_release(&ns_mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_child = atoi(argv[1]);
    pthread_t pc[num_child];
    tinfo_t t[num_child];
    ns_mutex_init(&ns_mutex);
    printf("parent: begin\n");
    int i;
    for (i = 0; i < num_child; i++) {
        t[i].thread_id = i;
        Pthread_create(&pc[i], NULL, worker, &t[i]);
    }
    for (i = 0; i < num_child; i++)
        Pthread_join(pc[i], NULL);
    printf("parent: end\n");
    return 0;
}

