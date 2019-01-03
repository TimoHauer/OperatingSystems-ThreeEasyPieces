#include <stdio.h>
#include "counter.h"

typedef struct threadargs
{
    counter *zaehler;
    int anzahl;
} threadargs;

void *task(void *argsT)
{
    threadargs *args = (threadargs *) argsT;
    int i;

    for(i = 0; i <= args->anzahl; i++)
    {
        increment(args->zaehler);
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

    pthread_t threads[anzahl];
    double zeitMessung;
    int messung;
    counter zaehler;
    init(&zaehler);
    threadargs arguments;
    arguments.zaehler = &zaehler;
    arguments.anzahl = loops;
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
       pthread_create(&threads[i], NULL, task, &arguments);
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