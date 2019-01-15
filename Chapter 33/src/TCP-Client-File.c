#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{

    if(argc < 2)
    {
        printf("wrong input!\n");
        exit(-1);
    }

    int mysock;
    char bekommen[100];
    struct sockaddr_in serverAdresse;

    mysock = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serverAdresse, sizeof serverAdresse);

    serverAdresse.sin_family = AF_INET;
    serverAdresse.sin_port = htons(50000);
 
    inet_pton(AF_INET, "127.0.0.1", &(serverAdresse.sin_addr));
 
    connect(mysock, (struct sockaddr *)&serverAdresse, sizeof(serverAdresse));
    bzero(bekommen, 100);
 
    write(mysock, argv[1], strlen(argv[1])+1);
    read(mysock, bekommen, 100);
    printf("%s\n", bekommen);

    return 0;
}
