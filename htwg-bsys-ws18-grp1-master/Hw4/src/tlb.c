#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

double messung(int groesse, int seiten, int versuche);

int main(int argc, char *argv[])
{
	cpu_set_t cpuset;
	int groesse, versuche;
	long seiten;
	double zeit;

	CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);

        if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset)) {
        	fprintf(stderr, "CPU setzen hat nicht funktioniert\n");
        	exit(1);
        }

        if (argc != 3) {
        	fprintf(stderr, "Ungültige eingabe!\n");
        	exit(1);
        }
        groesse = getpagesize();
        seiten = strtol(argv[1], NULL, 10);
    	versuche = strtol(argv[2], NULL, 10);

    	if (!seiten || !versuche) {
    		fprintf(stderr, "Ungültige eingabe!\n");
    		exit(1);
    	}

    	zeit = messung(groesse, seiten, versuche);
    	printf("%ld,\t%d,\t%f,\n",seiten,versuche,zeit);
}

double messung(int groesse, int seiten, int versuche)
{
	struct timeval start, ende;
	int sprung, anzahl;
	suseconds_t diff;
	int *data;

	sprung = groesse/sizeof(int);
	anzahl = groesse*seiten / sizeof(int);
	data = (int*) calloc(anzahl, sizeof(int));

	for(int i = 0; i < versuche; i++)
	{
		for(int j = 0; j < seiten*sprung; j+=sprung)
		{
			data[j] += 1;
		}
	}

	diff = (ende.tv_sec - start.tv_sec) * 1000000 + ende.tv_usec - start.tv_usec;
	free(data);
	return diff/ (double) (seiten*versuche);

}
