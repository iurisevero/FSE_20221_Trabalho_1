#include "globalValues.hpp"

#include <string.h>

// Sound Paths
const char * redLightAlarm = "sound/redLight.mp3";
const char * infractionAlarm = "sound/infraction.mp3";

semaphore smphTrafficInfo;

TrafficLightState states[QNT_DEFAULT_STATES], nightModeStates[QNT_NIGHT_MODE_STATES];
TrafficLightState emergencyModeState, currentState;

bool exitAllThreads = false;

bool inoutNightMode = false, inoutEmergencyMode = false;

bool pedestrianButton1Pressed = false, pedestrianButton2Pressed = false;
bool passageSensorPressed = false;

int qntCarsTriggeredSensor1 = 0, qntCarsTriggeredSensor2 = 0;
int qntCarsTriggerSpeedSensor1 = 0, qntCarsTriggerSpeedSensor2 = 0;
int speeding = 0, passRedLight = 0;
float mainRoadSpeedAverage = 0.0f;
int carsLastMinute = 0, countCarsPerMinute = 0;
float carsPerMinuteAverage = 0.0f;

int trafficLight1Green, trafficLight1Yellow, trafficLight1Red;
int trafficLight2Green, trafficLight2Yellow, trafficLight2Red;
int pedestrianButton1, pedestrianButton2;
int passSensor1, passSensor2;
int speedSensor1A, speedSensor1B, speedSensor2A, speedSensor2B;

void setPinsConfigurationValues(char* cross){
    if(strcmp(cross, "2") == 0){
        trafficLight1Green =   8; // Saída
        trafficLight1Yellow =  9; // Saída
        trafficLight1Red =    14; // Saída
        trafficLight2Green =  30; // Saída
        trafficLight2Yellow = 21; // Saída
        trafficLight2Red =    22; // Saída
        pedestrianButton1 =   12; // Entrada
        pedestrianButton2 =   13; // Entrada
        passSensor1 =          7; // Entrada
        passSensor2 =          0; // Entrada
        speedSensor1A =        2; // Entrada
        speedSensor1B =        3; // Entrada
        speedSensor2A =       23; // Entrada
        speedSensor2B =       24; // Entrada
    } else{
        trafficLight1Green =  31; // Saída
        trafficLight1Yellow = 25; // Saída
        trafficLight1Red =    29; // Saída
        trafficLight2Green =  28; // Saída
        trafficLight2Yellow = 27; // Saída
        trafficLight2Red =    26; // Saída
        pedestrianButton1 =   10; // Entrada
        pedestrianButton2 =   11; // Entrada
        passSensor1 =         15; // Entrada
        passSensor2 =         16; // Entrada
        speedSensor1A =        1; // Entrada
        speedSensor1B =        4; // Entrada
        speedSensor2A =        5; // Entrada
        speedSensor2B =        6; // Entrada
    }
}

char * centralServerIP;
unsigned short port, centralServerPort;

void setTcpClientServerValues(char * _port, char * _centralServerIP, char * _centralServerPort){
    centralServerIP = (char *) malloc(strlen(_centralServerIP) + 1);
    strcpy(centralServerIP, _centralServerIP);
    port = atoi(_port);
    centralServerPort = atoi(_centralServerPort);
}