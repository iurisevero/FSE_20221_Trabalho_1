#ifndef _GLOBAL_VALUES_H_
#define _GLOBAL_VALUES_H_

#include <vector>
#include <string>
#include <map>

extern const char * confPath;

extern bool exitAllThreads;

extern std::vector<std::string> distributedServersIP;
extern std::vector<unsigned short> distributedServersPort;
extern unsigned short port;

extern std::map<std::string, int> qntCarsTriggeredSensor1, qntCarsTriggeredSensor2;
extern std::map<std::string, int> qntCarsTriggerSpeedSensor1, qntCarsTriggerSpeedSensor2;
extern std::map<std::string, int> speeding, passRedLight;
extern std::map<std::string, float> mainRoadSpeedAverage, carsPerMinuteAverage;

#endif /* _GLOBAL_VALUES_H_ */