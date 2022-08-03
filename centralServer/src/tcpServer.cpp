// Adaptation from https://gitlab.com/fse_fga/embarcados_exemplos_c/-/blob/master/sockets/sockets_tcp/servidor_tcp.c

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

#include "tcpServer.hpp"
#include "generalFunctions.hpp"
#include "globalValues.hpp"

void runTcpServer(unsigned short serverPort) {
	int socketServer;
	int socketClient;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	unsigned int clientLength;

	// Open Socket
	if((socketServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Server socket failure\n");

	// Mount sockaddr_in structure
	memset(&serverAddr, 0, sizeof(serverAddr)); // Reset data structure
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(serverPort);

	// Bind
	if(bind(socketServer, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
		printf("Bind failed\n");

	// Listen
	if(listen(socketServer, 10) < 0)
		printf("Listen failed\n");		

	while(1) {
		clientLength = sizeof(clientAddr);
		if((socketClient = accept(socketServer, 
			                      (struct sockaddr *) &clientAddr, 
			                      &clientLength)) < 0)
			printf("Accept failed\n");
				
		treatCustomerTCP(
			inet_ntoa(clientAddr.sin_addr),
			socketClient
		);
		close(socketClient);

		if(exitAllThreads) break;
	}
	close(socketServer);
	printf("Finish TCP Server\n");
	return;
}

void treatCustomerTCP(char * _ip, int socketClient) {
	char buffer[1000];
	int sizeReceived;

	if((sizeReceived = recv(socketClient, buffer, 1000, 0)) < 0)
		printf("Error in recv()\n");

	if(send(socketClient, buffer, sizeReceived, 0) != sizeReceived)
		printf("Error in send()\n");

	buffer[sizeReceived] = '\0';
	updateTrafficInfo(_ip, buffer);
}
