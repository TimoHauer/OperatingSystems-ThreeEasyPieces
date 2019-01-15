#include"netinet/in.h"
#include"sys/socket.h"
#include"stdio.h"
#include"string.h"
#include"time.h"
#include <stdlib.h>
#include <unistd.h>
int main()
{
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sockfd,conntfd;
	int len,ch, binding;
	char str[100];
	time_t zeit;
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
	server.sin_port = htons(50000);
	server.sin_addr.s_addr = htonl(0);

	binding = bind(sockfd, (struct sockaddr*)&server, sizeof(server));

	if(binding < 0)
	{
		printf("Fehler beim binden des Sockets!\n");
		exit(-1);
	}

	printf("Socket erfolgreich gebunden!\n");

	listen(sockfd, 50000);

	for(;;)
	{
		len = sizeof(ch);
		conntfd = accept(sockfd, (struct sockaddr*)&client, &len);
		printf("Accepted\n");
		zeit = time(NULL);
		snprintf(str, sizeof(str), "%s", ctime(&zeit));
		printf("%s", str);
		write(conntfd, str, 100);
	}

	return 0;
}
