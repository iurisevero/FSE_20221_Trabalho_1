#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>
#include <thread>

#include "globalValues.hpp"
#include "generalFunctions.hpp"
#include "trafficLightController.hpp"
#include "tcpServer.hpp"
#include "tcpClient.hpp"

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

void calculateCarsMin(){
    while(1){
        delay(60000);
        calculateCarsPerMinuteAverage();
        smphTrafficInfo.acquire();
        carsLastMinute = 0;
        smphTrafficInfo.release();
    }
}

void printInfo(){
    while(1){
        cerr << endl;
        cerr << "qntCarsTriggeredSensor1: " << qntCarsTriggeredSensor1 << endl;
        cerr << "qntCarsTriggeredSensor2: " << qntCarsTriggeredSensor2 << endl;
        cerr << "qntCarsTriggerSpeedSensor1: " << qntCarsTriggerSpeedSensor1 << endl;
        cerr << "qntCarsTriggerSpeedSensor2: " << qntCarsTriggerSpeedSensor2 << endl;
        cerr << "passRedLight: " << passRedLight << endl;
        cerr << "speeding: " << speeding << endl;
        cerr << "mainRoadSpeedAverage: " << mainRoadSpeedAverage << endl;
        cerr << "countCarsPerMinute: " << countCarsPerMinute << endl;
        cerr << "carsLastMinute: " << carsLastMinute << endl;
        cerr << "carsPerMinuteAverage: " << carsPerMinuteAverage << endl;
        cerr << endl;
        delay(5000);
    }
}

int main(int argc, char **argv)
{
    if (argc != 5) {
		printf("Use: %s <Cross> <Port> <Central Server IP> <Central Server Port>\n", argv[0]);
        printf("At make run use: `make run CROSS= PORT= CENTRALSERVERIP= CENTRALSERVERPORT=\n");
		exit(1);
	}

    setPinsConfigurationValues(argv[1]);
    setTcpClientServerValues(argv[2], argv[3], argv[4]);

    if(wiringPiSetup () == -1)
        return 1 ;
    
    setPins();
    setState(nightModeStates[0].state); // just for test
    delay(1000);

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

    smphTrafficInfo.release();

    thread runTcpServerThread(runTcpServer, port);
    // thread printInfoThread(printInfo);
    // thread calculateCarsMinThread(calculateCarsMin);
    // thread trafficLightControllerThread(runTrafficLight);
    // trafficLightControllerThread.join();
    runTcpServerThread.join();
}
