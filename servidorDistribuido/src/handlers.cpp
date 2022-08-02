#include "handlers.hpp"
#include "globalValues.hpp"
#include "generalFunctions.hpp"

#include <wiringPi.h>
#include <iostream>

// Default inputs
int defaultPedestrianButton1;
int defaultPedestrianButton2;
int defaultPassageSensor1;
int defaultPassageSensor2;
int defaultSpeedSensor1A;
int defaultSpeedSensor1B;
int defaultSpeedSensor2A;
int defaultSpeedSensor2B;

void setDefaultInputValues(){
    defaultPedestrianButton1 = digitalRead(pedestrianButton1);
    defaultPedestrianButton2 = digitalRead(pedestrianButton2);
    defaultPassageSensor1    = digitalRead(passSensor1);
    defaultPassageSensor2    = digitalRead(passSensor2);
    defaultSpeedSensor1A     = digitalRead(speedSensor1A);
    defaultSpeedSensor1B     = digitalRead(speedSensor1B);
    defaultSpeedSensor2A     = digitalRead(speedSensor2A);
    defaultSpeedSensor2B     = digitalRead(speedSensor2B);
}

// Handler example
// void handler(){
//     printf("Botão pedestre 1\n");
//     uint64_t pressedTime = getTimeMs();
//     int counter = 0;
//     while(getTimeMs() - pressedTime < 400){
//     std::cerr << "getTimeMs() - pressedTime: " << getTimeMs() - pressedTime << std::endl;
//         int read = digitalRead(pedestrianButton1);
//         std::cerr << "read: " << read << std::endl;
//         counter += (read == defaultPassageSensor1? -1 : 1);
//         if(counter == 5){
//             pedestrianButton1Pressed = true;
//             break;
//         }
//         else if(counter == -5){
//             pedestrianButton1Pressed = false;
//             break;
//         }
//     }
//     std::cerr << "pedestrianButton1Pressed: " << pedestrianButton1Pressed << std::endl;
// }

// Pedestrian Button 1 Handles
void handlePedestrianButton1(){
    printf("Botão pedestre 1\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(pedestrianButton1) == defaultPedestrianButton1? -1 : 1);
        if(counter == 5){
            pedestrianButton1Pressed = true;
            break;
        }
    }
    std::cerr << "pedestrianButton1Pressed: " << pedestrianButton1Pressed << std::endl;
}

// Pedestrian Button 2 Handles
void handlePedestrianButton2(){
    printf("Botão pedestre 2\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(pedestrianButton2) == defaultPedestrianButton2? -1 : 1);
        if(counter == 5){
            pedestrianButton2Pressed = true;
            break;
        }
    }
    std::cerr << "pedestrianButton2Pressed: " << pedestrianButton2Pressed << std::endl;
}

// Passage sensor 1 Handles
void handlePassageSensor1(){
    printf("Sensor de passagem 1\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(passSensor1) == defaultPassageSensor1? -1 : 1);
        if(counter == 5){
            passageSensorPressed = true;
            break;
        }
        else if(counter == -5){
            passageSensorPressed = false;
            qntCarsTriggeredSensor1++;
            addToCarsLastMinute();
            if(currentState.state[2] == 1){
                smphTrafficInfo.acquire();
                passRedLight++;
                smphTrafficInfo.release();
                playSoundThread(infractionAlarm);
            }
            break;
        }
    }
    std::cerr << "passageSensorPressed: " << passageSensorPressed << std::endl;
}

// Passage sensor 2 Handles
void handlePassageSensor2(){
    printf("Sensor de passagem 2\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(passSensor2) == defaultPassageSensor2? -1 : 1);
        if(counter == 5){
            passageSensorPressed = true;
            break;
        }
        else if(counter == -5){
            passageSensorPressed = false;
            qntCarsTriggeredSensor2++;
            addToCarsLastMinute();
            if(currentState.state[2] == 1){
                smphTrafficInfo.acquire();
                passRedLight++;
                smphTrafficInfo.release();
                playSoundThread(infractionAlarm);
            }
            break;
        }
    }
    std::cerr << "passageSensorPressed: " << passageSensorPressed << std::endl;
}

// Speed sensor 1 Handles
uint64_t speedSensor1BTriggerTime = UINT64_MAX;
void handleSpeedSensor1A(){
    printf("Sensor de velocidade 1 A\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(speedSensor1A) == defaultSpeedSensor1A? -1 : 1);
        if(counter == 5){
            long int deltaT = getTimeMs() - speedSensor1BTriggerTime;
            long int speed = 3600 / deltaT;
            std::cerr << "deltaT: " << deltaT << "; speed: " << speed << std::endl;
            if(speed > 0){
                if(speed > 60){
                    smphTrafficInfo.acquire();
                    speeding++;
                    smphTrafficInfo.release();
                    playSoundThread(infractionAlarm);
                }
                if(currentState.state[5] == 1){
                    smphTrafficInfo.acquire();
                    passRedLight++;
                    smphTrafficInfo.release();
                    playSoundThread(infractionAlarm);
                }
                addToMainRoadSpeedAverage(speed); 
            }
            qntCarsTriggerSpeedSensor1++;
            addToCarsLastMinute();

            speedSensor1BTriggerTime = UINT64_MAX;
            break;
        }
    }
}

void handleSpeedSensor1B(){
    printf("Sensor de velocidade 1 B\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(speedSensor1B) == defaultSpeedSensor1B? -1 : 1);
        if(counter == 5){
            speedSensor1BTriggerTime = getTimeMs();
            break;
        }
    }
    std::cerr << "speedSensor1BTriggerTime: " << speedSensor1BTriggerTime << std::endl;
}


// Speed sensor 2 Handles
uint64_t speedSensor2ATriggerTime = UINT64_MAX;
void handleSpeedSensor2B(){
    printf("Sensor de velocidade 2 B\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(speedSensor2B) == defaultSpeedSensor2B? -1 : 1);
        if(counter == 5){
            long int deltaT = getTimeMs() - speedSensor2ATriggerTime;
            long int speed = 3600 / deltaT;
            std::cerr << "deltaT: " << deltaT << "; speed: " << speed << std::endl;
            if(speed > 0){
                if(speed > 60){
                    smphTrafficInfo.acquire();
                    speeding++;
                    smphTrafficInfo.release();
                    playSoundThread(infractionAlarm);
                }
                if(currentState.state[5] == 1){
                    smphTrafficInfo.acquire();
                    passRedLight++;
                    smphTrafficInfo.release();
                    playSoundThread(infractionAlarm);
                }
                addToMainRoadSpeedAverage(speed); 
            }
            qntCarsTriggerSpeedSensor2++;
            addToCarsLastMinute();

            speedSensor2ATriggerTime = UINT64_MAX;
            break;
        }
    }
}

void handleSpeedSensor2A(){
    printf("Sensor de velocidade 2 A\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(speedSensor2A) == defaultSpeedSensor2A? -1 : 1);
        if(counter == 5){
            speedSensor2ATriggerTime = getTimeMs();
            break;
        }
    }
    std::cerr << "speedSensor2ATriggerTime: " << speedSensor2ATriggerTime << std::endl;
}