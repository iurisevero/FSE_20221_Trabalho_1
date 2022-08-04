#ifndef GENERAL_FUNCTIONS_H_
#define GENERAL_FUNCTIONS_H_

#include <map>
#include <string>

void inoutEmergencyMode();
void inoutNightMode();
void sendMessageToAllDistributedServers(char * message);
void updateTrafficInfo(char * _ip, char * buffer);
int sumMap(std::map<std::string, int> m);
float sumMap(std::map<std::string, float> m);
int sumMapAverage(std::map<std::string, int> m);
float sumMapAverage(std::map<std::string, float> m);

#endif /* GENERAL_FUNCTIONS_H_ */