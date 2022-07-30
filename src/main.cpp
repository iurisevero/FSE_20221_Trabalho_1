#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>
#include <thread>

#include "globalValues.hpp"
#include "generalFunctions.hpp"
#include "trafficLightController.hpp"

using namespace std;

void setPins(){
    // Define inputs
    pinMode(pedestrianButton1, INPUT);
    pinMode(pedestrianButton2, INPUT);
    pinMode(passSensor1,       INPUT);
    pinMode(passSensor2,       INPUT);
    pinMode(speedSensor1A,     INPUT);
    pinMode(speedSensor1B,     INPUT);
    pinMode(speedSensor2A,     INPUT);
    pinMode(speedSensor2B,     INPUT);

    // Define inputs PullUpDown
    pullUpDnControl(pedestrianButton1, PUD_DOWN);
    pullUpDnControl(pedestrianButton2, PUD_DOWN);
    pullUpDnControl(passSensor1,       PUD_UP);
    pullUpDnControl(passSensor2,       PUD_UP);
    pullUpDnControl(speedSensor1A,     PUD_UP);
    pullUpDnControl(speedSensor1B,     PUD_UP);
    pullUpDnControl(speedSensor2A,     PUD_UP);
    pullUpDnControl(speedSensor2B,     PUD_UP);

    // Define output Leds
    pinMode(trafficLight1Green,  OUTPUT);
    pinMode(trafficLight1Yellow, OUTPUT);
    pinMode(trafficLight1Red,    OUTPUT);
    pinMode(trafficLight2Green,  OUTPUT);
    pinMode(trafficLight2Yellow, OUTPUT);
    pinMode(trafficLight2Red,    OUTPUT);
}

void printInfo(){
    while(1){
        cerr << "qntCarsTriggeredSensor1: " << qntCarsTriggeredSensor1 << endl;
        cerr << "qntCarsTriggeredSensor2: " << qntCarsTriggeredSensor2 << endl;
        cerr << "qntCarsTriggerSpeedSensor1: " << qntCarsTriggerSpeedSensor1 << endl;
        cerr << "qntCarsTriggerSpeedSensor2: " << qntCarsTriggerSpeedSensor2 << endl;
        delay(60000);
    }
}

int main(int argc, char **argv)
{
    if(argc < 2){
        printf("Invalid execution. Please inform the selected cross\n");
        printf("For cross 1 run `$make run CROSS=1` or `$make run CROSS=2` for cross 2;\n");
        return -1;
    }
    setPinsConfigurationValues(argv[1]);

    if(wiringPiSetup () == -1)
        return 1 ;
    
    setPins();
    setState(nightModeStates[0].state); // just for test

    cerr << "digitalRead(pedestrianButton1     ): " << digitalRead(pedestrianButton1     ) << endl;
    cerr << "digitalRead(pedestrianButton1     ): " << digitalRead(pedestrianButton1     ) << endl;
    cerr << "digitalRead(pedestrianButton2     ): " << digitalRead(pedestrianButton2     ) << endl;
    cerr << "digitalRead(pedestrianButton2     ): " << digitalRead(pedestrianButton2     ) << endl;
    cerr << "digitalRead(passSensor1    ): " << digitalRead(passSensor1    ) << endl;
    cerr << "digitalRead(passSensor1    ): " << digitalRead(passSensor1    ) << endl;
    cerr << "digitalRead(passSensor2    ): " << digitalRead(passSensor2    ) << endl;
    cerr << "digitalRead(passSensor2    ): " << digitalRead(passSensor2    ) << endl;
    cerr << "digitalRead(speedSensor1A): " << digitalRead(speedSensor1A) << endl;
    cerr << "digitalRead(speedSensor1A): " << digitalRead(speedSensor1A) << endl;
    cerr << "digitalRead(speedSensor1B): " << digitalRead(speedSensor1B) << endl;
    cerr << "digitalRead(speedSensor1B): " << digitalRead(speedSensor1B) << endl;
    cerr << "digitalRead(speedSensor2A): " << digitalRead(speedSensor2A) << endl;
    cerr << "digitalRead(speedSensor2A): " << digitalRead(speedSensor2A) << endl;
    cerr << "digitalRead(speedSensor2B): " << digitalRead(speedSensor2B) << endl;
    cerr << "digitalRead(speedSensor2B): " << digitalRead(speedSensor2B) << endl;

    thread printInfoThread(printInfo);
    thread trafficLightController(runTrafficLight);
    trafficLightController.join();
}
