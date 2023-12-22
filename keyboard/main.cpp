#include <iostream>
#include <string>
#include  <vector>
#include <thread>
#include <chrono>
#include "key_utils.h"

using namespace std;
#define GREEN_BG "\033[32m"
#define YELLOW_BG "\033[33m"
#define GRAY_BG "\033[90m"
#define RESET "\033[0m"

int main(int argc, char* argv[]) {
    system("clear");

    while(true){
        displayKeyboard();
         std::this_thread::sleep_for(std::chrono::seconds(1)); //redo every second
         system("clear");
    }
    
    return 0;
}
