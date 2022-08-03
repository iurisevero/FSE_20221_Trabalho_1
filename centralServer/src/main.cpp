#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <csignal>


#include "globalValues.hpp"
#include "tcpServer.hpp"
#include "tcpClient.hpp"
#include "serverUI.hpp"

using namespace std;

void readConfiguration(){
    ifstream confFile(confPath);
    string line;
    while(getline(confFile, line)){
        size_t delimiter = line.find(":");
        string _ip = line.substr(0, delimiter);
        string _port = line.substr(delimiter+1);
        distributedServersIP.push_back(_ip);
        distributedServersPort.push_back(atoi(_port.c_str()));
    }
}

void signalHandler(int signum){
    printf("Interrupt signal (%d) received.\n", signum);
    printf("Stopping program.... It may take a little seconds while the threads are finished\n");
    exitAllThreads = true;
    printf("Please insert any char followed by enter to continue the finalization...\n");
}

int main(int argc, char **argv)
{
    if (argc != 2) {
		printf("Use: %s <Port>\n", argv[0]);
        printf("At make run use: `make run PORT=\n");
		exit(1);
	}

    port = atoi(argv[1]);
    readConfiguration();

    signal(SIGINT, signalHandler); 

    thread showUIThread(showUI);
    thread runTcpServerThread(runTcpServer, port);
    
    showUIThread.join();
    if(runTcpServerThread.joinable()){
        exitAllThreads = true;
        clientSocketConnection("127.0.0.1", port, "{}");
        runTcpServerThread.join();
    }

    printf("Execution stopped successfully!\n");
    return 0;
}
