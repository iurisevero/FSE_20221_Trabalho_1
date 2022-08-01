#ifndef _GLOBAL_VALUES_H_
#define _GLOBAL_VALUES_H_

#include "semaphore.hpp"

#include <bitset>

// Sound Paths
extern const char * redLightAlarm;
extern const char * infractionAlarm ;

extern semaphore smphTrafficInfo;

typedef struct {
    std::bitset<6> state;
    int minTime;
    int maxTime;
} TrafficLightState;

#define QNT_DEFAULT_STATES 6
#define QNT_NIGHT_MODE_STATES 2

extern TrafficLightState states[QNT_DEFAULT_STATES], nightModeStates[QNT_NIGHT_MODE_STATES];
extern TrafficLightState emergencyModeState, currentState;
extern bool inoutNightMode, inoutEmergencyMode;
extern bool pedestrianButton1Pressed, pedestrianButton2Pressed;
extern bool passageSensorPressed;

extern int qntCarsTriggeredSensor1, qntCarsTriggeredSensor2;
extern int qntCarsTriggerSpeedSensor1, qntCarsTriggerSpeedSensor2;
extern int speeding, passRedLight;
extern float mainRoadSpeedAverage;
extern int carsLastMinute, countCarsPerMinute;
extern float carsPerMinuteAverage;

extern int trafficLight1Green, trafficLight1Yellow, trafficLight1Red;
extern int trafficLight2Green, trafficLight2Yellow, trafficLight2Red;
extern int pedestrianButton1, pedestrianButton2;
extern int passSensor1, passSensor2;
extern int speedSensor1A, speedSensor1B, speedSensor2A, speedSensor2B;

void setPinsConfigurationValues(char* cross);

#endif /* _GLOBAL_VALUES_H_ */