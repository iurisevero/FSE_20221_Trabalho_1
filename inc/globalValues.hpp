#ifndef _GLOBAL_VALUES_H_
#define _GLOBAL_VALUES_H_

#include <bitset>

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

typedef struct {
    std::bitset<6> state;
    int minTime;
    int maxTime;
} TrafficLightState;

extern TrafficLightState states[QNT_DEFAULT_STATES], nightModeStates[QNT_NIGHT_MODE_STATES];
extern TrafficLightState emergencyModeState, currentState;
extern bool inoutNightMode, inoutEmergencyMode;
extern bool pedestrianButton1Pressed, pedestrianButton2Pressed;
extern bool passageSensorPressed;
extern int qntCarsTriggeredSensor1, qntCarsTriggeredSensor2;
extern int qntCarsTriggerSpeedSensor1, qntCarsTriggerSpeedSensor2;

#endif /* _GLOBAL_VALUES_H_ */