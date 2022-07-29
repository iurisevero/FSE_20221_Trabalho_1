#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <wiringPi.h>
#include <iostream>

#include "staticFunctions.hpp"
#include "globalValues.hpp"
// #include "handlers.hpp"

using namespace std;

void configuraPinos(){
    // Define entradas
    pinMode(BOTAO_PEDESTRE_1,       INPUT);
    pinMode(BOTAO_PEDESTRE_2,       INPUT);
    pinMode(SENSOR_PASSAGEM_1,      INPUT);
    pinMode(SENSOR_PASSAGEM_2,      INPUT);
    pinMode(SENSOR_VELOCIDADE_1_A,  INPUT);
    pinMode(SENSOR_VELOCIDADE_1_B,  INPUT);
    pinMode(SENSOR_VELOCIDADE_2_A,  INPUT);
    pinMode(SENSOR_VELOCIDADE_2_B,  INPUT);

    // Configura entradas PullUpDown
    pullUpDnControl(BOTAO_PEDESTRE_1,       PUD_DOWN);
    pullUpDnControl(BOTAO_PEDESTRE_2,       PUD_DOWN);
    pullUpDnControl(SENSOR_PASSAGEM_1,      PUD_UP);
    pullUpDnControl(SENSOR_PASSAGEM_2,      PUD_UP);
    pullUpDnControl(SENSOR_VELOCIDADE_1_A,  PUD_UP);
    pullUpDnControl(SENSOR_VELOCIDADE_1_B,  PUD_UP);
    pullUpDnControl(SENSOR_VELOCIDADE_2_A,  PUD_UP);
    pullUpDnControl(SENSOR_VELOCIDADE_2_B,  PUD_UP);

    // Configura pinos dos LEDs como saídas
    pinMode(SEMAFORO_1_VERDE,       OUTPUT);
    pinMode(SEMAFORO_1_AMARELO,     OUTPUT);
    pinMode(SEMAFORO_1_VERMELHO,    OUTPUT);
    pinMode(SEMAFORO_2_VERDE,       OUTPUT);
    pinMode(SEMAFORO_2_AMARELO,     OUTPUT);
    pinMode(SEMAFORO_2_VERMELHO,    OUTPUT);
}

// States
/*

S1 = semáforo 1; S2 = semáforo 2
|---------------------------------------|
|   StateMode   |  State  | State num   |
|               | S1   S2 |             |
|---------------------------------------|
|    Default    | 001 001 |      0      |
|               | 100 001 |      1      |
|               | 010 001 |      2      |
|               | 001 001 |      3      |
|               | 001 100 |      4      |
|               | 001 010 |      5      |
|---------------------------------------|
|     Night     | 010 010 |      0      |
|               | 000 000 |      1      |
|---------------------------------------|
|   Emergency   | 100 001 |      0      |
|---------------------------------------|
|    (Colors)     GYR GYR               |
|---------------------------------------|

*/

void setTrafficLightStates(){
    states[0].state   = 0b100100;  // 001001
    states[0].minTime = 1000;
    states[0].maxTime = 1000;

    states[1].state   = 0b100001;  // 100001
    states[1].minTime = 10000;
    states[1].maxTime = 20000;
    
    states[2].state   = 0b100010;  // 010001
    states[2].minTime = 3000;
    states[2].maxTime = 3000;
    
    states[3].state   = 0b100100;  // 001001
    states[3].minTime = 1000;
    states[3].maxTime = 1000;
    
    states[4].state   = 0b001100;  // 001100
    states[4].minTime = 5000;
    states[4].maxTime = 10000;
    
    states[5].state   = 0b010100;  // 001010
    states[5].minTime = 3000;
    states[5].maxTime = 3000;

    nightModeStates[0].state   = 0b000000; // 000000
    nightModeStates[0].minTime = 500;
    nightModeStates[0].maxTime = 500;

    nightModeStates[1].state   = 0b010010; // 010010
    nightModeStates[1].minTime = 500;
    nightModeStates[1].maxTime = 500;

    emergencyModeState.state   = 0b100001; // 100001
    emergencyModeState.minTime = -1;
    emergencyModeState.maxTime = -1;
}

uint64_t setState(bitset<6> state){
    digitalWrite(SEMAFORO_1_VERDE,      state[0]);
    digitalWrite(SEMAFORO_1_AMARELO,    state[1]);
    digitalWrite(SEMAFORO_1_VERMELHO,   state[2]);
    digitalWrite(SEMAFORO_2_VERDE,      state[3]);
    digitalWrite(SEMAFORO_2_AMARELO,    state[4]);
    digitalWrite(SEMAFORO_2_VERMELHO,   state[5]);
    return getTimeMs();
}

int main(int argc, char **argv)
{
    bool onNightMode = false, onEmergencyMode = false;

    if(wiringPiSetup () == -1)
        return 1 ;
    
    configuraPinos();
    setTrafficLightStates();

    setState(nightModeStates[0].state); // just for test

    wiringPiISR(BOTAO_PEDESTRE_1,       INT_EDGE_BOTH,    &handlePedestrianButton1);
    wiringPiISR(BOTAO_PEDESTRE_2,       INT_EDGE_BOTH,    &handlePedestrianButton2);
    wiringPiISR(SENSOR_PASSAGEM_1,      INT_EDGE_BOTH,    &handlePassageSensor1);
    wiringPiISR(SENSOR_PASSAGEM_2,      INT_EDGE_BOTH,    &handlePassageSensor2);
    wiringPiISR(SENSOR_VELOCIDADE_1_A,  INT_EDGE_FALLING, &handleSpeedSensor1A);
    wiringPiISR(SENSOR_VELOCIDADE_1_B,  INT_EDGE_FALLING, &handleSpeedSensor1B);
    wiringPiISR(SENSOR_VELOCIDADE_2_A,  INT_EDGE_FALLING, &handleSpeedSensor2A);
    wiringPiISR(SENSOR_VELOCIDADE_2_B,  INT_EDGE_FALLING, &handleSpeedSensor2B);

    debug(digitalRead(BOTAO_PEDESTRE_1     ));
    debug(digitalRead(BOTAO_PEDESTRE_1     ));
    debug(digitalRead(BOTAO_PEDESTRE_2     ));
    debug(digitalRead(BOTAO_PEDESTRE_2     ));
    debug(digitalRead(SENSOR_PASSAGEM_1    ));
    debug(digitalRead(SENSOR_PASSAGEM_1    ));
    debug(digitalRead(SENSOR_PASSAGEM_2    ));
    debug(digitalRead(SENSOR_PASSAGEM_2    ));
    debug(digitalRead(SENSOR_VELOCIDADE_1_A));
    debug(digitalRead(SENSOR_VELOCIDADE_1_A));
    debug(digitalRead(SENSOR_VELOCIDADE_1_B));
    debug(digitalRead(SENSOR_VELOCIDADE_1_B));
    debug(digitalRead(SENSOR_VELOCIDADE_2_A));
    debug(digitalRead(SENSOR_VELOCIDADE_2_A));
    debug(digitalRead(SENSOR_VELOCIDADE_2_B));
    debug(digitalRead(SENSOR_VELOCIDADE_2_B));

    int nextStateNum = 0;
    TrafficLightState currentState;
    while(1){
        // Emergency Mode
        if(inoutEmergencyMode){
            onEmergencyMode = !onEmergencyMode;
            debug(onEmergencyMode);
            if(onEmergencyMode) setState(emergencyModeState.state);
            inoutEmergencyMode = false;
        }

        if(!onEmergencyMode){
            currentState = (onNightMode? nightModeStates[nextStateNum] : states[nextStateNum]);
            uint64_t stateStartTime = setState(currentState.state);
            debug(stateStartTime);               
            delay(currentState.minTime);

            // Handle pedestrian's buttons and passage's sensors
            while((int)(getTimeMs() - stateStartTime) < currentState.maxTime){
                debug(getTimeMs() - stateStartTime);
                if(pedestrianButton1Pressed && currentState.state == 0b100001){
                    pedestrianButton1Pressed = false;
                    break;
                }

                if((pedestrianButton2Pressed || passageSensorPressed) &&
                currentState.state == 0b001100){
                    pedestrianButton2Pressed = false;
                    passageSensorPressed = false;
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
                debug(onNightMode);
                nextStateNum = 0;
                inoutNightMode = false;
            }
        }
    }
}
