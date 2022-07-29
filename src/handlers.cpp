#include "handlers.hpp"
#include <wiringPi.h>

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
    defaultPedestrianButton1 = digitalRead(BOTAO_PEDESTRE_1);
    defaultPedestrianButton2 = digitalRead(BOTAO_PEDESTRE_2);
    defaultPassageSensor1    = digitalRead(SENSOR_PASSAGEM_1);
    defaultPassageSensor2    = digitalRead(SENSOR_PASSAGEM_2);
    defaultSpeedSensor1A     = digitalRead(SENSOR_VELOCIDADE_1_A);
    defaultSpeedSensor1B     = digitalRead(SENSOR_VELOCIDADE_1_B);
    defaultSpeedSensor2A     = digitalRead(SENSOR_VELOCIDADE_2_A);
    defaultSpeedSensor2B     = digitalRead(SENSOR_VELOCIDADE_2_B);
}

// Handler example
// void handler(){
//     printf("Botão pedestre 1\n");
//     uint64_t pressedTime = getTimeMs();
//     int counter = 0;
//     while(getTimeMs() - pressedTime < 400){
//         debug(getTimeMs() - pressedTime);
//         int read = digitalRead(BOTAO_PEDESTRE_1);
//         debug(read);
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
//     debug(pedestrianButton1Pressed);
// }

// Pedestrian Button 1 Handles
void handlePedestrianButton1(){
    printf("Botão pedestre 1\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(BOTAO_PEDESTRE_1) == defaultPedestrianButton1? -1 : 1);
        if(counter == 5){
            pedestrianButton1Pressed = true;
            break;
        }
    }
    debug(pedestrianButton1Pressed);
}

// Pedestrian Button 2 Handles
void handlePedestrianButton2(){
    printf("Botão pedestre 2\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(BOTAO_PEDESTRE_2) == defaultPedestrianButton2? -1 : 1);
        if(counter == 5){
            pedestrianButton2Pressed = true;
            break;
        }
    }
    debug(pedestrianButton2Pressed);
}

// Passage sensor 1 Handles
void handlePassageSensor1(){
    printf("Sensor de passagem 1\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(SENSOR_PASSAGEM_1) == defaultPassageSensor1? -1 : 1);
        if(counter == 5){
            passageSensorPressed = true;
            break;
        }
        else if(counter == -5){
            passageSensorPressed = false;
            break;
        }
    }
    debug(passageSensorPressed);
}

// Passage sensor 2 Handles
void handlePassageSensor2(){
    printf("Sensor de passagem 2\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(SENSOR_PASSAGEM_2) == defaultPassageSensor2? -1 : 1);
        if(counter == 5){
            passageSensorPressed = true;
            break;
        }
        else if(counter == -5){
            passageSensorPressed = false;
            break;
        }
    }
    debug(passageSensorPressed);
}

// Speed sensor 1 Handles
uint64_t speedSensor1BTriggerTime;
void handleSpeedSensor1A(){
    printf("Sensor de velocidade 1 A\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(SENSOR_VELOCIDADE_1_A) == defaultSpeedSensor1A? -1 : 1);
        if(counter == 5){
            uint64_t deltaT = getTimeMs() - speedSensor1BTriggerTime;
            printf("deltaT: %llu ; Speed: %d km / h\n", deltaT, 3600 / deltaT);
            break;
        }
    }
}

void handleSpeedSensor1B(){
    printf("Sensor de velocidade 1 B\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(SENSOR_VELOCIDADE_1_B) == defaultSpeedSensor1B? -1 : 1);
        if(counter == 5){
            speedSensor1BTriggerTime = getTimeMs();
            break;
        }
    }
    debug(speedSensor1BTriggerTime);
}


// Speed sensor 2 Handles
uint64_t speedSensor2ATriggerTime;
void handleSpeedSensor2B(){
    printf("Sensor de velocidade 2 B\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(SENSOR_VELOCIDADE_2_B) == defaultSpeedSensor2B? -1 : 1);
        if(counter == 5){
            uint64_t deltaT = getTimeMs() - speedSensor2ATriggerTime;
            printf("deltaT: %llu ; Speed: %d km / h\n", deltaT, 3600 / deltaT);
            break;
        }
    }
}

void handleSpeedSensor2A(){
    printf("Sensor de velocidade 2 A\n");
    uint64_t pressedTime = getTimeMs();
    int counter = 0;
    while(getTimeMs() - pressedTime < 400){
        counter += (digitalRead(SENSOR_VELOCIDADE_2_A) == defaultSpeedSensor2A? -1 : 1);
        if(counter == 5){
            speedSensor2ATriggerTime = getTimeMs();
            break;
        }
    }
    debug(speedSensor2ATriggerTime);
}