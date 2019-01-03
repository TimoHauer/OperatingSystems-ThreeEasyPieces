#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#define ZYKLEN 200

double Lesen(int samples, size_t bytes);
void time_array(struct timeval times[ZYKLEN]);
double Systemcall(int samples, size_t bytes);


int main(int argc, char *argv[])
{
    printf("Systemcall mit 0-byte lesen: %.3fms\n", Systemcall(ZYKLEN, 0));
    printf("Systemcall mit 1-byte lesen: %.3fms\n", Systemcall(ZYKLEN, 1));
    printf("File lesen mit 0-byte: %.3fms\n", Lesen(ZYKLEN, 0));
    printf("File lesen mit 1-byte: %.3fms\n", Lesen(ZYKLEN, 1));
    return 0;
}

double Lesen(int zyklen, size_t nbyte)
{
    char c;
    suseconds_t diff;
    long vergangen = 0;
    struct timeval start, ende;
    int zeit1, zeit2;
    FILE *file;

    for (int i = 0; i < zyklen; i++) {
        file = fopen("ausgabe.txt", "r");
        if (file == NULL) {
            fprintf(stderr, "öffnen fehlgeschlagen!\n");
            exit(1);
        }
        zeit1 = gettimeofday(&start, NULL);
        fread(&c, 1, nbyte, file);
        zeit2 = gettimeofday(&ende, NULL);
        
        if (zeit1 < 0 || zeit2 < 0) {
            fprintf(stderr, "fehlgeschlagen!\n");
            exit(1);
        }
        diff = ende.tv_usec - start.tv_usec;
        vergangen += (int) diff;

        /* close the file */
        fclose(file);
    }
    return (double) vergangen / (double) zyklen;
}

double Systemcall(int zyklen, size_t bytes)
{
    int datei;
    long vergangen = 0;
    int zeit1, zeit2;
    struct timeval start, ende;
    suseconds_t diff;
    char puffer;

    for (int i = 0; i < zyklen; i++) {
        datei = open("ausgabe.txt", O_RDONLY|O_CREAT);
        if (datei == -1) {
            fprintf(stderr, "öffnen fehlgeschlagen!\n");
            exit(1);
        }
        zeit1 = gettimeofday(&start, NULL);
        read(datei, &puffer, bytes);
        zeit2 = gettimeofday(&ende, NULL);        
        if (zeit1 < 0 || zeit2 < 0) {
            fprintf(stderr, "fehlgeschlagen!\n");
            exit(1);
        }

        diff = ende.tv_usec - start.tv_usec;
        vergangen += (int) diff;

        close(datei);
    }
    return (double) vergangen / (double) zyklen;
}