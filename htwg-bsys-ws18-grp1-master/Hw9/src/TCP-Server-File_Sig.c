#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

char filecache[100];

void clearFilecache()
{
    bzero(&filecache, sizeof(filecache));
}
void handle(int arg)
{
    printf("abc%s\n", filecache);
    clearFilecache();
    printf("Filecache cleared!\n");
}
int main()
{
    char str[100];
    int listener, acpt;
    char filecache[100];
 
    struct sockaddr_in serverAdresse;
 
    clearFilecache();
    
    listener = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero(&serverAdresse, sizeof(serverAdresse));
 
    serverAdresse.sin_family = AF_INET;
    serverAdresse.sin_addr.s_addr = htons(INADDR_ANY);
    serverAdresse.sin_port = htons(50000);
 
    bind(listener, (struct sockaddr *) &serverAdresse, sizeof(serverAdresse));
 
    listen(listener, 10);
    signal(SIGHUP, handle);
    while(1)
    {
        acpt = accept(listener, (struct sockaddr*) NULL, NULL);
        bzero(str, 100);
 
        if (read(acpt, str, 100) > 0)
        {
            strcpy(filecache, str);
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
                if (i == 50)
                    break;
            }
 
            printf("sending data back!\n");
            write(acpt, file, strlen(file) + 1);
        }
    }
    return 0;
}
