#include "globalValues.hpp"

const char * confPath = ".conf";

bool exitAllThreads = false;

std::vector<std::string> distributedServersIP;
std::vector<unsigned short> distributedServersPort;
unsigned short port;

int qntCarsTriggeredSensor1, qntCarsTriggeredSensor2;
int qntCarsTriggerSpeedSensor1, qntCarsTriggerSpeedSensor2;
int speeding, passRedLight;
float mainRoadSpeedAverage, carsPerMinuteAverage;