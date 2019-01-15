#include "list.h"
#include <stdio.h>


typedef struct threadargs
{
    list *liste;
    int data;
    int anzahl;
} threadargs;

void *hinzufuegen(void *argsT)
{
	threadargs *args = (threadargs *) argsT;
	int i;
	for(i = 0; i < args->anzahl; i++)
	{
		add(args->liste,args->data);
	}
    return NULL;
}

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		fprintf(stderr, "Fehlerhafte Eingabe!\n");
		return 1;
	}
	int anzahl = strtol(argv[1], NULL, 10);
	int loops = strtol(argv[2], NULL, 10);
	pthread_t threads[anzahl];
	threadargs argsT[anzahl];
	list liste;
	struct timeval start, ende;
	init(&liste);

	double zeitMessung;
    int messung;

    messung = gettimeofday(&start, NULL);
    if(messung != 0)
    {
        fprintf(stderr, "Fehlerhafte Zeit!");
        return 1;
    }

	int i;
	for(i = 0; i < anzahl; i++)
	{
		argsT[i].liste = &liste;
		argsT[i].data = i*i;
		argsT[i].anzahl = loops;
		pthread_create(&threads[i], NULL, hinzufuegen, &argsT[i]);
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