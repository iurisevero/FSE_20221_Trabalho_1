#include "generalFunctions.hpp"
#include "globalValues.hpp"

#include <wiringPi.h>
#include <string.h>
#include <thread>

uint64_t getTimeMs(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

uint64_t setState(std::bitset<6> state){
    digitalWrite(trafficLight1Green,  state[0]);
    digitalWrite(trafficLight1Yellow, state[1]);
    digitalWrite(trafficLight1Red,    state[2]);
    digitalWrite(trafficLight2Green,  state[3]);
    digitalWrite(trafficLight2Yellow, state[4]);
    digitalWrite(trafficLight2Red,    state[5]);
    return getTimeMs();
}

void playSoundThread(const char * sound){
    std::thread play([&sound]{system(strcat((char *)"cvlc --play-and-exit ", sound));});
}

void addToMainRoadSpeedAverage(long int speed){
    smphTrafficInfo.acquire();
    float totalCarsMainRoad = qntCarsTriggerSpeedSensor1 + qntCarsTriggerSpeedSensor2;
    mainRoadSpeedAverage = (
        ((mainRoadSpeedAverage * totalCarsMainRoad) + speed) / (totalCarsMainRoad + 1)
    );
    smphTrafficInfo.release();
}

void addToCarsLastMinute(){
    smphTrafficInfo.acquire();
    carsLastMinute++;
    smphTrafficInfo.release();
}

void calculateCarsPerMinuteAverage(){
    smphTrafficInfo.acquire();
    carsPerMinuteAverage = (
        ((carsPerMinuteAverage * countCarsPerMinute) + carsLastMinute) / (countCarsPerMinute + 1)
    );
    smphTrafficInfo.release();
}