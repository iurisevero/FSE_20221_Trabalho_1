#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <string>

void runTcpServer(unsigned short serverPort);
void treatCustomerTCP(char * _ip, std::string _port, int socketClient);

#endif /* _TCP_SERVER_H_ */