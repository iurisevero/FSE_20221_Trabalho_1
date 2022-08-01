// Adaptation from https://gitlab.com/fse_fga/embarcados_exemplos_c/-/blob/master/sockets/sockets_tcp/cliente_tcp.c

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void clientSocketConnection(char * IP_Server, unsigned short serverPort, char * message){
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[16];
	unsigned int sizeMessage;

	int bytesRecebidos;
	unsigned int totalBytesRecebidos;

	// Create Socket
	if((clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Error in socket()\n");

	// Build struct sockaddr_in
	memset(&serverAddr, 0, sizeof(serverAddr)); // Reset data structure
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(IP_Server);
	serverAddr.sin_port = htons(serverPort);

	// Connect
	if(connect(clientSocket, (struct sockaddr *) &serverAddr, 
							sizeof(serverAddr)) < 0)
		printf("Error in connect()\n");

	sizeMessage = strlen(message);

	if(send(clientSocket, message, sizeMessage, 0) != sizeMessage)
		printf("Error in send: number of bytes sent different than expected\n");

	totalBytesRecebidos = 0;
	while(totalBytesRecebidos < sizeMessage) {
		if((bytesRecebidos = recv(clientSocket, buffer, 16-1, 0)) <= 0)
			printf("Did not receive total bytes sent\n");
		totalBytesRecebidos += bytesRecebidos;
		buffer[bytesRecebidos] = '\0';
		printf("%s\n", buffer);
	}
	close(clientSocket);
}