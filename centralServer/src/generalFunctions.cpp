#include "generalFunctions.hpp"
#include "globalValues.hpp"
#include "tcpClient.hpp"

void inoutEmergencyMode(){
    char * message = "{\"inoutEmergencyMode\":true}"; 
    sendMessageToAllDistributedServers(message);
}

void inoutNightMode(){
    char * message = "{\"inoutNightMode\":true}"; 
    sendMessageToAllDistributedServers(message);
}

void sendMessageToAllDistributedServers(char * message){
    for(int i=0; i < distributedServersIP.size(); ++i){
        clientSocketConnection(
            distributedServersIP[i].c_str(),
            distributedServersPort[i],
            message
        );
    }
}