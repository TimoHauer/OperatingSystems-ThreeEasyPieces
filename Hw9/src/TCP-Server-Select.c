#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
    
#define PORT 50000
#define SIZE 100

void SendenAlle(int j, int i, int sockfd, int bekommen_bytes, char *bekommen, fd_set *master)
{
    if (FD_ISSET(j, master)){
        if (j != sockfd && j != i) {
            if (send(j, bekommen, bekommen_bytes, 0) < 0) {
                perror("send fehler");
            }
        }
    }
}
        
void empfangen(int i, fd_set *master, int sockfd, int max)
{
    int bekommen_bytes, j;
    char bekommen[SIZE];
    
    if ((bekommen_bytes = recv(i, bekommen, SIZE, 0)) <= 0) {
        if (bekommen_bytes == 0) {
            printf("socket %d hat die Verbindung verlassen\n", i);
        }else {
            perror("recive fehler");
        }
        close(i);
        FD_CLR(i, master);
    }else {
        for(j = 0; j <= max; j++){
            SendenAlle(j, i, sockfd, bekommen_bytes, bekommen, master );
        }
    }   
}
        
void annehmen(fd_set *master, int *max, int sockfd, struct sockaddr_in *client)
{
    socklen_t adresse;
    int neuerfd;
    
    adresse = sizeof(struct sockaddr_in);
    if((neuerfd = accept(sockfd, (struct sockaddr *)client, &adresse)) < 0) {
        perror("accept fehler");
        exit(1);
    }else {
        FD_SET(neuerfd, master);
        if(neuerfd > *max){
            *max = neuerfd;
        }
        printf("neue verbindung von %s bei socket %d auf port %d \n",inet_ntoa(client->sin_addr), neuerfd, ntohs(client->sin_port));
    }
}
    
void request(int *sockfd, struct sockaddr_in *server)
{
    int eins = 1;
        
    if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket fehler");
        exit(1);
    }
        
    server->sin_family = AF_INET;
    server->sin_port = htons(50000);
    server->sin_addr.s_addr = INADDR_ANY;
    memset(server->sin_zero, ' ', sizeof server->sin_zero);
        
    if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &eins, sizeof(int)) < 0) {
        perror("setsockopt fehler");
        exit(1);
    }
        
    if (bind(*sockfd, (struct sockaddr *)server, sizeof(struct sockaddr)) < 0) {
        perror("Verbindungsfehler");
        exit(1);
    }
    if (listen(*sockfd, 10) < 0) {
        perror("listen fehler");
        exit(1);
    }
    printf("\nTCPServer wartet auf Clients\n");
    fflush(stdout);
}
int main()
{
    fd_set master;
    fd_set read_fds;
    int fdmax, i;
    int sockfd= 0;
    struct sockaddr_in my_addr, client;
    
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    request(&sockfd, &my_addr);
    FD_SET(sockfd, &master);
    
    fdmax = sockfd;
    while(1){
        read_fds = master;
        if(select(fdmax+1, &read_fds, NULL, NULL, NULL) < 0){
            perror("select fehler");
            exit(4);
        }
        
        for (i = 0; i <= fdmax; i++){
            if (FD_ISSET(i, &read_fds)){
                if (i == sockfd)
                    annehmen(&master, &fdmax, sockfd, &client);
                else
                    empfangen(i, &master, sockfd, fdmax);
            }
        }
    }
    return 0;
}
