#include "globalValues.hpp"

TrafficLightState states[QNT_DEFAULT_STATES], nightModeStates[QNT_NIGHT_MODE_STATES];
TrafficLightState emergencyModeState, currentState;

bool inoutNightMode = false, inoutEmergencyMode = false;
bool pedestrianButton1Pressed = false, pedestrianButton2Pressed = false;
bool passageSensorPressed = false;

int qntCarsTriggeredSensor1 = 0, qntCarsTriggeredSensor2 = 0;
int qntCarsTriggerSpeedSensor1 = 0, qntCarsTriggerSpeedSensor2 = 0;