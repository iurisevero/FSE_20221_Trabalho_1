#include <nlohmann/json.hpp>

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

void updateTrafficInfo(char * buffer){
    nlohmann::json receivedMessage =  nlohmann::json::parse(buffer);
    if(receivedMessage.contains("qntCarsTriggeredSensor1"))
        qntCarsTriggeredSensor1 = receivedMessage["qntCarsTriggeredSensor1"];
    if(receivedMessage.contains("qntCarsTriggeredSensor2"))
        qntCarsTriggeredSensor2 = receivedMessage["qntCarsTriggeredSensor2"];
    if(receivedMessage.contains("qntCarsTriggerSpeedSensor1"))
        qntCarsTriggerSpeedSensor1 = receivedMessage["qntCarsTriggerSpeedSensor1"];
    if(receivedMessage.contains("qntCarsTriggerSpeedSensor2"))
        qntCarsTriggerSpeedSensor2 = receivedMessage["qntCarsTriggerSpeedSensor2"];
    if(receivedMessage.contains("speeding"))
        speeding = receivedMessage["speeding"];
    if(receivedMessage.contains("passRedLight"))
        passRedLight = receivedMessage["passRedLight"];
    if(receivedMessage.contains("mainRoadSpeedAverage"))
        mainRoadSpeedAverage = receivedMessage["mainRoadSpeedAverage"];
    if(receivedMessage.contains("carsPerMinuteAverage"))
        carsPerMinuteAverage = receivedMessage["carsPerMinuteAverage"];
}