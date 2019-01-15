#include"netinet/in.h"
#include"sys/socket.h"
#include"stdio.h"
#include"time.h"
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
int main()
{
	struct sockaddr_in server, client;
	int n, sockfd;
	int len, con;
	char buffer[100];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		printf("Fehler beim erstellen des Sockets!\n");
		exit(-1);
	}
	else {
		printf("Socket geöffnet!\n");
	}

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(50000);


	if(connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		printf("Verbindung fehlgeschlagen!\n");
		exit(-1);
	}

	printf("Verbindung hergestellt!\n");

	if(n = read(sockfd, buffer, sizeof(buffer))<0)
	{
		printf("Fehler beim lesen!\n");
		exit(-1);
	}
	else
	{
		printf("Nachricht gelesen: %s", buffer);
	}

	return 0;
}
