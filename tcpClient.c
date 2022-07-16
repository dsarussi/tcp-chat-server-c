#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

void main(){

	char* isMove;
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	printf("[+]Client Socket Created Sucessfully.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Connected to Server.\n");

	printf("Move has detected: Y/N ");

	if(isMove == 'Y'){
		for (int i = 1; i <= 5; i++) {
			printf("%d move detector has been triggered !!\n", i);
		}
		printf("move has detected in the house!!\n");
	}
	else if (isMove == 'N') {
		printf("no movement in the house\n");
	}
	else{
	printf("invalid answer\n");
	}
	recv(clientSocket, buffer, 1024, 0);
	printf("[+]Closing the connection.\n");

}
