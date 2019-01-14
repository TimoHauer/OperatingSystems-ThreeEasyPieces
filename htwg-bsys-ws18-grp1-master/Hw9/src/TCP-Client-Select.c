#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
	
#define SIZE 100
		
void empfangen(int i, int sockfd)
{
	char senden[SIZE];
	char bekommen[SIZE];
	int bekommen_bytes;
	if (i == 0){
		fgets(senden, SIZE, stdin);
		if (strcmp(senden , "quit\n") == 0) {
			exit(0);
		}else
			send(sockfd, senden, strlen(senden), 0);
	}else {
		bekommen_bytes = recv(sockfd, bekommen, SIZE, 0);
		bekommen[bekommen_bytes] = ' ';
		printf("%s\n" , bekommen);
		//fflush(stdout);
	}
}
		
		
void anfrage(int *sockfd, struct sockaddr_in *server)
{
	if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket fehlerhaft");
		exit(1);
	}
	server->sin_family = AF_INET;
	server->sin_port = htons(50000);
	server->sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(server->sin_zero, ' ', sizeof server->sin_zero);
	
	if(connect(*sockfd, (struct sockaddr *)server, sizeof(struct sockaddr)) < 0) {
		perror("Verbindungsfehler");
		exit(1);
	}
}
	
int main()
{
	int sockfd, fdmax, i;
	struct sockaddr_in server;
	fd_set master;
	fd_set read_fds;
	
	anfrage(&sockfd, &server);
	FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(0, &master);
    FD_SET(sockfd, &master);
	fdmax = sockfd;
	
	while(1){
		read_fds = master;
		if(select(fdmax+1, &read_fds, NULL, NULL, NULL) < 0){
			perror("select fehlerhaft");
			exit(4);
		}
		
		for(i=0; i <= fdmax; i++ )
			if(FD_ISSET(i, &read_fds))
				empfangen(i, sockfd);
	}
	close(sockfd);
	return 0;
}
