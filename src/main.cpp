#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <wiringPi.h>
#include <iostream>
#include <ctime>

#define debug(x) cerr << #x << ": " << x << endl;

#define QNT_DEFAULT_STATES 6
#define QNT_NIGHT_MODE_STATES 2

/* 
 * Configuração dos pinos dos LEDs e Botão
*/

// Cruzamento 1

// #define SEMAFORO_1_VERDE        31 // Saída
// #define SEMAFORO_1_AMARELO      25 // Saída
// #define SEMAFORO_1_VERMELHO     29 // Saída
// #define SEMAFORO_2_VERDE        28 // Saída
// #define SEMAFORO_2_AMARELO      27 // Saída
// #define SEMAFORO_2_VERMELHO     26 // Saída
// #define BOTAO_PEDESTRE_1        10 // Entrada
// #define BOTAO_PEDESTRE_2        11 // Entrada
// #define SENSOR_PASSAGEM_1       15 // Entrada
// #define SENSOR_PASSAGEM_2       16 // Entrada
// #define SENSOR_VELOCIDADE_1_A    1 // Entrada
// #define SENSOR_VELOCIDADE_1_B    4 // Entrada
// #define SENSOR_VELOCIDADE_2_A    5 // Entrada
// #define SENSOR_VELOCIDADE_2_B    6 // Entrada

// Cruzamento 2

#define SEMAFORO_1_VERDE         8 // Saída
#define SEMAFORO_1_AMARELO       9 // Saída
#define SEMAFORO_1_VERMELHO     14 // Saída
#define SEMAFORO_2_VERDE        30 // Saída
#define SEMAFORO_2_AMARELO      21 // Saída
#define SEMAFORO_2_VERMELHO     22 // Saída
#define BOTAO_PEDESTRE_1        12 // Entrada
#define BOTAO_PEDESTRE_2        13 // Entrada
#define SENSOR_PASSAGEM_1        7 // Entrada
#define SENSOR_PASSAGEM_2        0 // Entrada
#define SENSOR_VELOCIDADE_1_A    2 // Entrada
#define SENSOR_VELOCIDADE_1_B    3 // Entrada
#define SENSOR_VELOCIDADE_2_A   23 // Entrada
#define SENSOR_VELOCIDADE_2_B   24 // Entrada

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

typedef struct {
    bitset<6> state;
    int minTime;
    int maxTime;
} TrafficLightState;

TrafficLightState states[QNT_DEFAULT_STATES], nightModeStates[QNT_NIGHT_MODE_STATES], emergencyModeState;
bool inoutNightMode = false, inoutEmergencyMode = false;
bool pedestrianButton1Pressed = false, pedestrianButton2Pressed = false;
bool passageSensorPressed = false;

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

time_t setState(bitset<6> state){
    digitalWrite(SEMAFORO_1_VERDE,      state[0]);
    digitalWrite(SEMAFORO_1_AMARELO,    state[1]);
    digitalWrite(SEMAFORO_1_VERMELHO,   state[2]);
    digitalWrite(SEMAFORO_2_VERDE,      state[3]);
    digitalWrite(SEMAFORO_2_AMARELO,    state[4]);
    digitalWrite(SEMAFORO_2_VERMELHO,   state[5]);
    return time(nullptr);
}

void handlePedestrianButton1(){
    printf("Botão pedestre 1\n");
    pedestrianButton1Pressed = true;
}

void handlePedestrianButton2(){
    printf("Botão pedestre 2\n");
    pedestrianButton2Pressed = true;
}

void handlePassageSensor1Falling(){
    printf("Sensor de passagem 1 falling\n");
    passageSensorPressed = true;
}

void handlePassageSensor2Falling(){
    printf("Sensor de passagem 2 falling\n");
    passageSensorPressed = true;
}

void handlePassageSensor1Rising(){
    printf("Sensor de passagem 1 rising\n");
    passageSensorPressed = false;
}

void handlePassageSensor2Rising(){
    printf("Sensor de passagem 2 rising\n");
    passageSensorPressed = false;
}

int main(int argc, char **argv)
{
    bool onNightMode = false, onEmergencyMode = false;

    if(wiringPiSetup () == -1)
        return 1 ;
    
    configuraPinos();
    setTrafficLightStates();

    setState(nightModeStates[0].state); // just for test

    wiringPiISR(BOTAO_PEDESTRE_1,   INT_EDGE_RISING,    &handlePedestrianButton1);
    wiringPiISR(BOTAO_PEDESTRE_2,   INT_EDGE_RISING,    &handlePedestrianButton2);
    wiringPiISR(SENSOR_PASSAGEM_1,  INT_EDGE_FALLING,   &handlePassageSensor1Falling);
    wiringPiISR(SENSOR_PASSAGEM_2,  INT_EDGE_FALLING,   &handlePassageSensor2Falling);
    wiringPiISR(SENSOR_PASSAGEM_1,  INT_EDGE_RISING,    &handlePassageSensor1Rising);
    wiringPiISR(SENSOR_PASSAGEM_2,  INT_EDGE_RISING,    &handlePassageSensor2Rising);

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
            time_t stateStartTime = setState(currentState.state);
            debug(stateStartTime);               
            delay(currentState.minTime);

            // Handle pedestrian's buttons and passage's sensors
            while(time(nullptr) - stateStartTime < currentState.maxTime / 1000){
                debug(time(nullptr) - stateStartTime);
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

                // Delay d 1s pra evitar consumo desnecessário da CPU durante essa verificação
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
