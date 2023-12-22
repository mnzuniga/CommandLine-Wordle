#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    bool gameRunning = true;
    string gameState;
    system("clear");
    while (gameRunning){
        printMenu();
        getline(cin, gameState);
        if (gameState == "1"){
            playWordle();
            escapeClear();
        }
        else if (gameState == "2"){
            howToPlay();
            escapeClear();
        }
        else if (gameState == "3"){
            showStatsSummary();
            escapeClear();
        }
        else if (gameState == "4"){
            clearStats();
            escapeClear();
        }
        else if(gameState == "5") {
            system("clear");
            cout << "Thanks for playing!" << endl;
            gameRunning = false;
        }
        else{
            system("clear");
            cout << "Invalid Option." << endl;
        }
    }

    return 0;
} 
