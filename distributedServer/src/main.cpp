#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <iostream>
#include <thread>
#include <csignal>
#include <nlohmann/json.hpp>

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

void everyMinInfo(){
    while(1){
        delay(60000);
        nlohmann::json trafficInfo;
        smphTrafficInfo.acquire();
        calculateCarsPerMinuteAverage();
        trafficInfo["carsLastMinute"] = carsLastMinute;
        trafficInfo["carsPerMinuteAverage"] = carsPerMinuteAverage;
        trafficInfo["mainRoadSpeedAverage"] = mainRoadSpeedAverage;
        trafficInfo["speeding"] = speeding;
        trafficInfo["passRedLight"] = passRedLight;
        carsLastMinute = 0;
        smphTrafficInfo.release();
        clientSocketConnection(centralServerIP, centralServerPort, trafficInfo.dump().c_str());

        if(exitAllThreads) return;
    }
}

void every2SecInfo(){
    while(1){
        delay(2000);
        nlohmann::json trafficInfo;
        smphTrafficInfo.acquire();
        trafficInfo["qntCarsTriggeredSensor1"] = qntCarsTriggeredSensor1;
        trafficInfo["qntCarsTriggeredSensor2"] = qntCarsTriggeredSensor2;
        trafficInfo["qntCarsTriggerSpeedSensor1"] = qntCarsTriggerSpeedSensor1;
        trafficInfo["qntCarsTriggerSpeedSensor2"] = qntCarsTriggerSpeedSensor2;
        smphTrafficInfo.release();
        clientSocketConnection(centralServerIP, centralServerPort, trafficInfo.dump().c_str());

        if(exitAllThreads) return;
    }
}

void signalHandler(int signum){
    printf("Interrupt signal (%d) received.\n", signum);
    printf("Stopping program.... It may take a little seconds while the threads are finished\n");
    exitAllThreads = true;
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

    signal(SIGINT, signalHandler); 
    smphTrafficInfo.release();

    thread runTcpServerThread(runTcpServer, port);
    thread every2SecInfoThread(every2SecInfo);
    thread everyMinInfoThread(everyMinInfo);
    thread trafficLightControllerThread(runTrafficLight);
    trafficLightControllerThread.join();
    everyMinInfoThread.join();
    every2SecInfoThread.join();
    if(runTcpServerThread.joinable()){
        exitAllThreads = true;
        clientSocketConnection("127.0.0.1", port, "{}");
    }
    runTcpServerThread.join();

    printf("Execution stopped successfully!\n");
    return 0;
}
