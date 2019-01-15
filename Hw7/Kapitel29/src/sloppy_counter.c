#include <stdio.h>
#include "sloppy_counter.h"

typedef struct threadargs
{
    sloppycounter *zaehler;
    int id;
    int anzahl;
} threadargs;

void *task(void *argsT)
{
    threadargs *args = (threadargs *) argsT;
    int i;
    for(i = 0; i < args->anzahl; i++)
    {
        sloppyUpdate(args->zaehler, args->id, 1);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "Fehlerhafte Eingabe!");
        return 1;
    }
    int anzahl = strtol(argv[1], NULL, 10);
    int loops = strtol(argv[2], NULL, 10);
    int threshhold = strtol(argv[3], NULL, 10);

    pthread_t threads[anzahl];
    double zeitMessung;
    int messung;
    sloppycounter zaehler;
    init(&zaehler,threshhold);
    threadargs arguments[anzahl];
    struct timeval start, ende;
    long zeit[anzahl];

    messung = gettimeofday(&start, NULL);
    if(messung != 0)
    {
        fprintf(stderr, "Fehlerhafte Zeit!");
        return 1;
    }

    int i;
    for(i = 0; i < anzahl; i++)
    {
        arguments[i].id = i;
        arguments[i].zaehler = &zaehler;
        arguments[i].anzahl = loops;
       pthread_create(&threads[i], NULL, task, &arguments[i]);
    }
    for(i = 0; i < anzahl; i++)
    {
       pthread_join(threads[i], (void**) &zeit[i]);
    }
    messung = gettimeofday(&ende, NULL);
    if(messung != 0)
    {
        fprintf(stderr, "Fehlerhafte Zeit!");
        return 1;
    }

    zeitMessung = (ende.tv_sec - start.tv_sec) * 1000000 + ende.tv_usec - start.tv_usec;

    printf("%f\n", zeitMessung);
    return 0;
}