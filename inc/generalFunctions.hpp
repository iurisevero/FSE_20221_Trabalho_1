#ifndef GENERAL_FUNCTIONS_H_
#define GENERAL_FUNCTIONS_H_
#include <chrono>
#include <bitset>

uint64_t getTimeMs();
uint64_t setState(std::bitset<6> state);
void playSoundThread(char * sound);
void addToMainRoadSpeedAverage(long int speed);
void addToCarsLastMinute();
void calculateCarsPerMinuteAverage();

#endif /* GENERAL_FUNCTIONS_H_ */