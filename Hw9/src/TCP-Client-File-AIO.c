#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <aio.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("wrong input!\n");
        exit(-1);
    }

    struct aiocb aiocb;
    int mysock;
    char bekommen[50];
    struct sockaddr_in serverAdresse;

    mysock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&aiocb, 0, sizeof(struct aiocb));
    bzero(&serverAdresse, sizeof serverAdresse);

    serverAdresse.sin_family = AF_INET;
    serverAdresse.sin_port = htons(50000);
 
    inet_pton(AF_INET, "127.0.0.1", &(serverAdresse.sin_addr));
 
    connect(mysock, (struct sockaddr *)&serverAdresse, sizeof(serverAdresse));
    bzero(bekommen, 50);
 
    write(mysock, argv[1], strlen(argv[1])+1);
        
    int err, ret;
    aiocb.aio_fildes = mysock;
    aiocb.aio_buf = bekommen;
    aiocb.aio_nbytes = 50;
    if (aio_read(&aiocb) == -1)
    {
        perror("aio_read() fehlgeschlagen!\n");
        exit(-1);
    }
    while ((err = aio_error(&aiocb)) == EINPROGRESS)
    {
        printf("receiving data...\n");
    }
    err = aio_error(&aiocb);
    ret = aio_return(&aiocb);
    if (err != 0) 
    {
        perror("aio_error() fehlgeschlagen!\n");
        exit(-1);
    }
    if ((ret != strlen(bekommen) + 1) && (ret != 50)) 
    {
        perror("aio_ret() fehlgeschlagen!\n");
        exit(-1);
    }
    printf("Data received!\n");
    printf("%s\n", bekommen);

    return 0;
}
