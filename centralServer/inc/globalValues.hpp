#ifndef _GLOBAL_VALUES_H_
#define _GLOBAL_VALUES_H_

#include <vector>
#include <string>

extern const char * confPath;

extern bool exitAllThreads;

extern std::vector<std::string> distributedServersIP;
extern std::vector<unsigned short> distributedServersPort;
extern unsigned short port;

extern int qntCarsTriggeredSensor1, qntCarsTriggeredSensor2;
extern int qntCarsTriggerSpeedSensor1, qntCarsTriggerSpeedSensor2;
extern int speeding, passRedLight;
extern float mainRoadSpeedAverage, carsPerMinuteAverage;

#endif /* _GLOBAL_VALUES_H_ */