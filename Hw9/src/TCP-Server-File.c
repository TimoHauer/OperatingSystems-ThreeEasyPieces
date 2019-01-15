#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
char* readFile(char *filename)
{
    char ch;
    char filename[] = str;
    char file[50] = {0};
    int i = 0;
    FILE *fp;
    fp = fopen(filename, "r");
 
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(-1);
    }

    printf("The contents of %s file are:\n", filename);
 
    while((ch = fgetc(fp)) != EOF)
    {
        file[i] = ch;
        i++;
    }
    fclose(fp);

    return file;
}
*/

int main()
{
    char str[100];
    int listener, acpt;

 
    struct sockaddr_in serverAdresse;
 
    listener = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero(&serverAdresse, sizeof(serverAdresse));
 
    serverAdresse.sin_family = AF_INET;
    serverAdresse.sin_addr.s_addr = htons(INADDR_ANY);
    serverAdresse.sin_port = htons(50000);
 
    bind(listener, (struct sockaddr *) &serverAdresse, sizeof(serverAdresse));
 
    listen(listener, 10);
 
 
    while(1)
    {
        acpt = accept(listener, (struct sockaddr*) NULL, NULL);
        bzero(str, 100);
 
        if (read(acpt, str, 100) > 0)
        {
        char ch;
        char filename[strlen(str)+1];
        strcpy(filename, str);
        char file[50] = {0};
        int i = 0;
        FILE *fp;
        fp = fopen(filename, "r");
 
        if (fp == NULL)
        {
            perror("Error while opening the file.\n");
            exit(-1);
        }
 
        while((ch = fgetc(fp)) != EOF)
        {
            file[i] = ch;
            i++;
        }
 
        printf("sending data back!\n");
        write(acpt, file, strlen(file) + 1);
        }
    }
    return 0;
}
