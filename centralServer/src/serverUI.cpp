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
        if(exitAllThreads){
            printf("Finish showUI\n");
            return;
        }
    }
}

void handleMenu(){
    string input;
    printMenu();
    cin >> input;
    if(input == "1")
        printTrafficInfo();
    else if(input == "2"){
        inoutEmergencyMode();
        outputMessage("Emergency Mode Triggered");
    }
    else if(input == "3"){
        inoutNightMode();
        outputMessage("Night Mode Triggered");
    }
    else if(input == "4")
        exitAllThreads = true;
    else
        outputMessage("Invalid input. Please insert one of the shown options.");
}

void printMenu(){
    printTitle("Main Menu");
    cout << "1 - Show traffic informations" << endl;
    cout << "2 - Activate / Deactivate Emergency Mode" << endl;
    cout << "3 - Activate / Deactivate Night Mode" << endl;
    cout << "4 - Exit" << endl;
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
        sumMap(qntCarsTriggerSpeedSensor1), sumMap(speeding)
    );
    printf(
        "| Main Road 2 |          %03d |\t| Pass Red Light |        %03d |\n",
        sumMap(qntCarsTriggerSpeedSensor2), sumMap(passRedLight)
    );
    printf(
        "| Sideline 1  |          %03d |\t+--------------+--------------+\n",
        sumMap(qntCarsTriggeredSensor1)
    );
    printf(
        "| Sideline 2  |          %03d |\tMain Road Speed Average: %03.2f\n",
        sumMap(qntCarsTriggeredSensor2), sumMapAverage(mainRoadSpeedAverage)
    );
    printf(
        "+-------------+--------------+\tCars per Minute Average: %03.2f\n",
        sumMapAverage(carsPerMinuteAverage)
    );
    cout << endl << "Press enter key to return to main menu." << endl;
    limpaLixo();
    char c;
    scanf("%[^\n]", &c);
}

void printTitle(string title){
    int N = 59 - title.size();
    cout << "+" << string(30, '-') << "+" << string(30, '-') << "+" << endl;
    cout << "+" << string(N / 2, '-') << " " << title << " " <<  string(N / 2 + (N%2), '-') << "+" << endl;
    cout << "+" << string(30, '-') << "+" << string(30, '-') << "+" << endl;
}

void outputMessage(string s){
    cout << s << endl;
    system("sleep 1");
}

void limpaLixo(){
    while(scanf("%*c"));
}
