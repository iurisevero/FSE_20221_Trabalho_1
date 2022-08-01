#include "trafficLightController.hpp"
#include "globalValues.hpp"
#include "generalFunctions.hpp"
#include "handlers.hpp"

#include <iostream>
#include <wiringPi.h>

// States
/*

S1 = semáforo 1 (via secundária); S2 = semáforo 2 (via principal)
|---------------------------------------|
|   StateMode   |  State  | State num   |
|               | S1   S2 |             |
|---------------------------------------|
|    Default    | 001 001 |      0      |
|               | 001 100 |      1      |
|               | 001 010 |      2      |
|               | 001 001 |      3      |
|               | 100 001 |      4      |
|               | 010 001 |      5      |
|---------------------------------------|
|     Night     | 010 010 |      0      |
|               | 000 000 |      1      |
|---------------------------------------|
|   Emergency   | 001 100 |      0      |
|---------------------------------------|
|    (Colors)     GYR GYR               |
|---------------------------------------|

*/

void setTrafficLightStates(){
    states[0].state   = 0b100100;  // 001 001
    states[0].minTime = 1000;
    states[0].maxTime = 1000;

    states[1].state   = 0b001100;  // 001 100
    states[1].minTime = 10000;
    states[1].maxTime = 20000;
    
    states[2].state   = 0b010100;  // 001 010
    states[2].minTime = 3000;
    states[2].maxTime = 3000;
    
    states[3].state   = 0b100100;  // 001 001
    states[3].minTime = 1000;
    states[3].maxTime = 1000;
    
    states[4].state   = 0b100001;  // 100 001
    states[4].minTime = 5000;
    states[4].maxTime = 10000;
    
    states[5].state   = 0b100010;  // 010 001
    states[5].minTime = 3000;
    states[5].maxTime = 3000;

    nightModeStates[0].state   = 0b000000; // 000 000
    nightModeStates[0].minTime = 500;
    nightModeStates[0].maxTime = 500;

    nightModeStates[1].state   = 0b010010; // 010 010
    nightModeStates[1].minTime = 500;
    nightModeStates[1].maxTime = 500;

    emergencyModeState.state   = 0b001100; // 001 100
    emergencyModeState.minTime = -1;
    emergencyModeState.maxTime = -1;
}

void runTrafficLight(){
    setTrafficLightStates();

    wiringPiISR(pedestrianButton1, INT_EDGE_BOTH, &handlePedestrianButton1);
    wiringPiISR(pedestrianButton2, INT_EDGE_BOTH, &handlePedestrianButton2);
    wiringPiISR(passSensor1,       INT_EDGE_BOTH, &handlePassageSensor1);
    wiringPiISR(passSensor2,       INT_EDGE_BOTH, &handlePassageSensor2);
    wiringPiISR(speedSensor1A,     INT_EDGE_BOTH, &handleSpeedSensor1A);
    wiringPiISR(speedSensor1B,     INT_EDGE_BOTH, &handleSpeedSensor1B);
    wiringPiISR(speedSensor2A,     INT_EDGE_BOTH, &handleSpeedSensor2A);
    wiringPiISR(speedSensor2B,     INT_EDGE_BOTH, &handleSpeedSensor2B);

    bool onNightMode = false, onEmergencyMode = false;
    int nextStateNum = 0;
    while(1){
        // Emergency Mode
        if(inoutEmergencyMode){
            onEmergencyMode = !onEmergencyMode;
            std::cerr << "onEmergencyMode: " << onEmergencyMode << std::endl;
            if(onEmergencyMode) setState(emergencyModeState.state);
            inoutEmergencyMode = false;
        }

        if(!onEmergencyMode){
            currentState = (onNightMode? nightModeStates[nextStateNum] : states[nextStateNum]);
            uint64_t stateStartTime = setState(currentState.state);
            std::cerr << "stateStartTime: " << stateStartTime << std::endl;

            // play buzzer
            // if(currentState.state == 0b010100 || currentState.state == 0b100010)
            //     playSoundThread(redLightAlarm);

            delay(currentState.minTime);

            // Handle pedestrian's buttons and passage's sensors
            while((int)(getTimeMs() - stateStartTime) < currentState.maxTime){
                std::cerr << "getTimeMs() - stateStartTime: " << getTimeMs() - stateStartTime << std::endl;
                if(pedestrianButton1Pressed && currentState.state == 0b100001){
                    pedestrianButton1Pressed = false;
                    break;
                }

                if((pedestrianButton2Pressed || passageSensorPressed) &&
                currentState.state == 0b001100){
                    pedestrianButton2Pressed = false;
                    break;
                }

                // 1s delay to avoid CPU overuse during this check
                delay(1000);
            }
            // If the button is pressed with the light red, it will not affect next states
            if(currentState.state == 0b001100) pedestrianButton1Pressed = false;
            if(currentState.state == 0b100001) pedestrianButton2Pressed = false;

            nextStateNum = (nextStateNum + 1) % (onNightMode? QNT_NIGHT_MODE_STATES : QNT_DEFAULT_STATES);

            // Night Mode
            if(inoutNightMode && (currentState.state == 0b100100 || currentState.state.none())){
                onNightMode = !onNightMode;
                std::cerr << "onNightMode: " << onNightMode << std::endl;
                nextStateNum = 0;
                inoutNightMode = false;
            }
        }
    }
}