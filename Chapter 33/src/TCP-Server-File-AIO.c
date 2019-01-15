#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <aio.h>
#include <errno.h>

int main()
{
    char str[100];
    int listener, acpt;
    struct aiocb aiocb;
 
    struct sockaddr_in serverAdresse;
 
    memset(&aiocb, 0, sizeof(struct aiocb));
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
 
        int err, ret;
        aiocb.aio_fildes = acpt;
        aiocb.aio_buf = file;
        aiocb.aio_nbytes = strlen(file) + 1;
        if (aio_write(&aiocb) == -1)
        {
            perror("aio_write() fehlgeschlagen!\n");
            exit(-1);
        }
        while ((err = aio_error(&aiocb)) == EINPROGRESS)
        {
            printf("sending data back...\n");
        }
        fflush(stdout);
        err = aio_error(&aiocb);
        ret = aio_return(&aiocb);
        if (err != 0)
        {
            perror("aio_error() fehlgeschlagen!\n");
            exit(-1);
        }
        if (ret != strlen(file) + 1) 
        {
            perror("aio_ret() fehlgeschlagen!\n");
            exit(-1);
        }
        printf("Completed!\n");
        }
    }
    return 0;
}
