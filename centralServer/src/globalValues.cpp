#include "globalValues.hpp"

const char * confPath = ".conf";

bool exitAllThreads = false;

std::vector<std::string> distributedServersIP;
std::vector<unsigned short> distributedServersPort;
unsigned short port;

std::map<std::string, int> qntCarsTriggeredSensor1, qntCarsTriggeredSensor2;
std::map<std::string, int> qntCarsTriggerSpeedSensor1, qntCarsTriggerSpeedSensor2;
std::map<std::string, int> speeding, passRedLight;
std::map<std::string, float> mainRoadSpeedAverage, carsPerMinuteAverage;