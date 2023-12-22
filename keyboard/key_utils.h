#ifndef KEY_UTILS_H
#define KEY_UTILS_H
#include <string>
#include  <vector>
#include <iostream>
#include <fstream>


#define GREEN_BG "\033[32m"
#define YELLOW_BG "\033[33m"
#define GRAY_BG "\033[90m"
#define RESET "\033[0m"


std::vector<std::string> readKeyboardState(){
    std::vector<std::string> currentState;
    std::ifstream file("keyboard_state.txt");
    if (file.is_open()){
        std::string line;
        while (getline(file, line)){
            currentState.push_back(line);
        }
        file.close();
    }
    return currentState;
}

void displayKeyboard(){
    std::vector<std::string> currentState = readKeyboardState();
    std::vector<std::vector<char>> keyboard = {
        {'Q',' ', 'W',' ', 'E',' ','R',' ', 'T',' ', 'Y',' ', 'U',' ', 'I',' ', 'O',' ', 'P'},
        {' ','A',' ', 'S',' ', 'D',' ', 'F',' ', 'G',' ', 'H',' ', 'J',' ', 'K',' ', 'L'},
        {' ',' ','Z',' ', 'X',' ', 'C',' ', 'V',' ', 'B',' ', 'N',' ', 'M'}
    };
    

    for (const auto &row : keyboard){
        for (const auto &key : row){
            //check if key has color in file
            std::string foundColor = "";
            for (const auto &line : currentState){
                if (line.find(key) != std::string::npos){
                    if (line.find("1") != std::string::npos){
                        foundColor = GREEN_BG;
                    } else if(line.find("2") != std::string::npos){
                        foundColor = YELLOW_BG;
                    } else if(line.find("3") != std::string::npos){
                        foundColor = GRAY_BG;
                    }
                    //break;
                }
            }
            std::cout << foundColor << key << RESET;
        }
        std::cout << std::endl;

    }

}

#endif 
