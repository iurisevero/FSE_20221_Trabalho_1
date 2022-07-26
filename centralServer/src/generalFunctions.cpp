#include <nlohmann/json.hpp>
#include <string>
#include <map>
#include <utility>

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

void updateTrafficInfo(char * _ip, char * buffer){
    try{
        nlohmann::json receivedMessage =  nlohmann::json::parse(buffer);
        int _port = receivedMessage["port"];
        std::string ipStr(_ip);
        ipStr.append(std::to_string(_port));
        ipStr.push_back('\0');
        if(receivedMessage.contains("qntCarsTriggeredSensor1"))
            qntCarsTriggeredSensor1[ipStr] = receivedMessage["qntCarsTriggeredSensor1"];
        if(receivedMessage.contains("qntCarsTriggeredSensor2"))
            qntCarsTriggeredSensor2[ipStr] = receivedMessage["qntCarsTriggeredSensor2"];
        if(receivedMessage.contains("qntCarsTriggerSpeedSensor1"))
            qntCarsTriggerSpeedSensor1[ipStr] = receivedMessage["qntCarsTriggerSpeedSensor1"];
        if(receivedMessage.contains("qntCarsTriggerSpeedSensor2"))
            qntCarsTriggerSpeedSensor2[ipStr] = receivedMessage["qntCarsTriggerSpeedSensor2"];
        if(receivedMessage.contains("speeding"))
            speeding[ipStr] = receivedMessage["speeding"];
        if(receivedMessage.contains("passRedLight"))
            passRedLight[ipStr] = receivedMessage["passRedLight"];
        if(receivedMessage.contains("mainRoadSpeedAverage"))
            mainRoadSpeedAverage[ipStr] = receivedMessage["mainRoadSpeedAverage"];
        if(receivedMessage.contains("carsPerMinuteAverage"))
            carsPerMinuteAverage[ipStr] = receivedMessage["carsPerMinuteAverage"];
    }
    catch(nlohmann::json_v3_11_1::detail::parse_error e){
        printf("Error %d while trying to parse: %s\n", e.id, buffer);
    }
    catch(nlohmann::json_v3_11_1::detail::type_error e){
        printf("Error %d while trying to parse: %s\n", e.id, buffer);
    }
    catch(nlohmann::json_v3_11_1::detail::other_error e){
        printf("Error %d while trying to parse: %s\n", e.id, buffer);
    }
}

int sumMap(std::map<std::string, int> m){
    int sum = 0;
    for(std::pair<std::string, int> keyValue : m){
        sum += keyValue.second;
    }
    return sum;
}

float sumMap(std::map<std::string, float> m){
    float sum = 0;
    for(std::pair<std::string, float> keyValue : m){
        sum += keyValue.second;
    }
    return sum;
}

int sumMapAverage(std::map<std::string, int> m){
    int sum = 0;
    for(std::pair<std::string, int> keyValue : m){
        sum += keyValue.second;
    }
    return sum / (m.size()==0? 1 : m.size());
}

float sumMapAverage(std::map<std::string, float> m){
    float sum = 0;
    for(std::pair<std::string, float> keyValue : m){
        sum += keyValue.second;
    }
    return sum / (m.size()==0? 1 : m.size());
}