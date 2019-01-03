#include <stdio.h>
#include "vector.h"

typedef struct threadargs
{
    vector *vec;
    int data;
} threadargs;

void *task(void *argsT)
{
    threadargs *args = (threadargs *) argsT;
    add(args->vec, args->data);
    return NULL;
}

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Fehlerhafte Eingabe!\n");
        return 1;
    }
    int anzahl = strtol(argv[1], NULL, 10);

    pthread_t threads[anzahl];
    double zeitMessung;
    int messung;
    vector vector;
    init(&vector);
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
        arguments[i].vec = &vector;
        arguments[i].data = i*i;
       pthread_create(&threads[i], NULL, task, &arguments[i]);
    }
    for(i = 0; i < anzahl; i++)
    {
       pthread_join(threads[i], NULL);
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