#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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
 
    acpt = accept(listener, (struct sockaddr*) NULL, NULL);
 
    while(1)
    {
 
        bzero(str, 100);
 
        read(acpt, str, 100);
 
        printf("Echo: %s", str);
 
        write(acpt, str, strlen(str) + 1);
 
    }
}
