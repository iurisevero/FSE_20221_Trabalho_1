#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "serverUI.hpp"
#include "globalValues.hpp"
#include "generalFunctions.hpp"

using namespace std;

void showUI(){
    while(1){
        handleMenu();
        if(exitAllThreads) return;
    }
}

void handleMenu(){
    string input;
    printMenu();
    cin >> input;
    if(input == "1")
        printTrafficInfo();
    else if(input == "2")
        inoutEmergencyMode();
    else if(input == "3")
        inoutNightMode();
    else
        invalidInput();
}

void printMenu(){
    printTitle("Main Menu");
    cout << "1 - Show traffic informations" << endl;
    cout << "2 - Activate / Deactivate Emergency Mode" << endl;
    cout << "3 - Activate / Deactivate Night Mode" << endl;
    cout << "OBS: Emergency mode overlap Night mode, but don't stop it" << endl;
    cout << "Insert your option: ";
}

void printTrafficInfo(){
    printTitle("Traffic Info");

    printf("+-------------+--------------+\t+--------------+--------------+\n"); // 65 caracteres
    printf("|             | Passing Cars |\t|          Infractions        |\n");
    printf("+-------------+--------------+\t+--------------+--------------+\n");
    printf(
        "| Main Road 1 |          %03d |\t| Speeding       |        %03d |\n",
        qntCarsTriggerSpeedSensor1, speeding
    );
    printf(
        "| Main Road 2 |          %03d |\t| Pass Red Light |        %03d |\n",
        qntCarsTriggerSpeedSensor2, passRedLight
    );
    printf(
        "| Sideline 1  |          %03d |\t+--------------+--------------+\n",
        qntCarsTriggeredSensor1
    );
    printf(
        "| Sideline 2  |          %03d |\tMain Road Speed Average: %3.2f\n",
        qntCarsTriggeredSensor2, mainRoadSpeedAverage
    );
    printf(
        "+-------------+--------------+\tCars per Minute Average: %3.2f\n",
        carsPerMinuteAverage
    );
}

void printTitle(string title){
    int N = 63 - title.size();
    cout << string(N, '-') << " " << title << " " <<  string(N, '-') << endl;
}

void invalidInput(){
    cout << "Invalid input. Please insert one of the shown options." << endl;
    system("sleep 1");
}
