#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>

#define GREEN_BG "\033[32m"
#define YELLOW_BG "\033[33m"
#define GRAY_BG "\033[90m"
#define RESET "\033[0m"

std::string green(char letter){
    std::string result = GREEN_BG;
    result += letter;
    result += RESET;

    return result;
}

std::string yellow(char letter){
    std::string result = YELLOW_BG;
    result += letter;
    result += RESET;

    return result;
}

std::string gray(char letter){
    std::string result = GRAY_BG;
    result += letter;
    result += RESET;

    return result;
}

int contains(std::string word, char letter){ 
    for (int i = 0; i < word.length(); i++){
        if (word[i] == letter){
            return i;
        }
    }
    return -1;
}

bool contains(std::vector<int> numbers, int value){
    for (int i = 0; i < numbers.size(); i++ ){
        if (numbers[i]==value){
            return true;
        }
    }
    return false;
}

std::vector<std::string> findAllowedWords(){
    std::ifstream allowedFile("allowed.txt");
    std::vector<std::string> allowedWords;
    std::string word;

    while (getline(allowedFile, word)) {
        for (char &c : word){
            c = std::toupper(c);
        }
        allowedWords.push_back(word);
    }
    allowedFile.close();

    std::ifstream wordsFile("words.txt");
    std::string word2;

    while (getline(wordsFile, word2)) {
        for (char &c : word2){
            c = std::toupper(c);
        }
        allowedWords.push_back(word2);
    }
    wordsFile.close();

    return allowedWords; //both files together !! 
}

std::string checkAttempt(std::string solution, std::string attempt){
    std::string result= "" ;
    std::vector<int> greenPosition;
    std::vector<int> yellowPosition;
    std::string solutionChanged = solution; //make shallow copies so i can edit them 
    std::string attemptChanged = attempt;

    std::string filePath = "../keyboard/keyboard_state.txt";
    std::ofstream outputFile(filePath, std::ios_base::app );


    for (int i = 0; i < attempt.length(); i++){
        if (attempt[i] == solution[i]){
            solutionChanged[i] = '-';
            attemptChanged[i] = '*';
            greenPosition.push_back(i);
            outputFile << "1: " << attempt[i] << std::endl;
        }
    }
     for (int i = 0; i < attempt.length(); i++){
        int pos = contains(solutionChanged, attemptChanged[i]);
        if (pos != -1){
            solutionChanged[pos] = '-';
            yellowPosition.push_back(i);
            outputFile << "2: " << attempt[i] << std::endl;

        }
    }
    for (int i = 0; i < attempt.length(); i++){
        if (contains(greenPosition, i)){
            result+= green(attempt[i]);

        }
        else if (contains(yellowPosition, i)){
            result += yellow(attempt[i]);

        }
        else{
            result += gray(attempt[i]) ;
            outputFile << "3: " << attempt[i] << std::endl;

        }
        if (i < attempt.length()){
            result+= " ";
        }
    }
    outputFile.close();

    return result;
}

std:: string generateWord(std::string filename){
    std::string line;
    std::vector<std::string> lines;

    std::srand(std::time(0));
    int total_lines = 0;
    std::ifstream file(filename);
    if (!file.is_open()){
        return "";
    }
    while(std::getline(file, line)){
        total_lines++;
        lines.push_back(line);
    }
    std::string solution = lines[std::rand()%total_lines];
    file.close();

    return solution;
}

std::string generateUppercaseWord(std::string filename){
    std::string word = generateWord(filename);
    for (char &c : word){
        c = std::toupper(c);
    }
    return word;
}

void statsUpdate(const std::string& solution, int won, int c) {
    std::string win;
    std::ofstream file("stats.txt", std::ios::app);
    if (won == 0){
        win = "No";
        
    }else{
        win = "Yes";
    }

    if (file.is_open()) {

        file << solution << "           " << c << "      " << win << std::endl;
        
        file.close();
    }
}

void clearKeyboard(){
    std::ofstream file("../keyboard/keyboard_state.txt", std::ios::trunc);
}

void playWordle(){
    std::string solution;
    bool set = false; //set word to test word HERE !!!!!!!!!!!!!!!!!!!!!!!!

    if (set){
        solution = "CROWN";
    }
    else{
        solution = generateUppercaseWord("words.txt");
    }
    
    std::string originalSolution = solution;

    std::vector<std::string> allowedWords = findAllowedWords();
    clearKeyboard();

    int c = 0;
    bool won = false;
    while(c <= 5){
        std::cout << "Enter 5 letter words: ";
        std::string attempt;
        std::getline(std::cin, attempt);
        for (char &c : attempt){
            c = std::toupper(c);
        }

        if (attempt.length() != 5) {
            std::cout << "Attempt must be exactly 5 letters long." << std::endl;
            continue;
        } else {
            bool wordExists = false;
            for (const std::string& allowedWord : allowedWords) {
                if (attempt == allowedWord) {
                    wordExists = true;
                    break;
                }
            }
            if (!wordExists) {
                std::cout << "Invalid word. Please enter a real 5-letter word." << std::endl;
                continue;
            }
        }
        c++;
        std::cout << checkAttempt(solution, attempt) <<std::endl;
        if (attempt == solution){
            won = true;
            std::cout << " *｡'*､ *｡'*､ *｡'*､" << std::endl;
            std::cout << "*｡'*､You win!*｡'*､" << std::endl;
            std::cout << "* ｡'*､ *｡'*､ *｡'*､" << std::endl;
            break;
        }
    }
    if (!won){
        std::cout << "Sorry, better luck next time lol" << std::endl << "The word was: " << solution;
        //c= c-1;
    }

    std::cout << std::endl;

    statsUpdate(solution, won, c); // for stats summary 
}

void printMenu(){
    std::cout << "=========================" << std::endl << "   ✧WELCOME TO WORDLE✧" << std::endl;
    std::cout << "=========================" << std::endl << std::endl << "1. Play Wordle" << std::endl << "2. How to Play";
    std::cout << std::endl << "3. Statistics Summary" << std::endl << "4. Reset Statistics";
    std::cout << std::endl << "5. Exit" << std::endl << std::endl << "Select an option:";


}
void howToPlay(){
    std::cout << "=============================================" << std::endl;
    std::cout << "                ✧HOW TO PLAY✧"<< std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "Guess the Wordle in 6 tries." << std::endl;
    std::cout << "HOW TO PLAY:" << std::endl << "- Each guess must be a valid 5 letter word." << std::endl << "- The color of the tiles will change to show" << std::endl << "you how close your guess was to the word." << std::endl;
    std::cout << GREEN_BG << " ---" << RESET << "  ---  ---  ---  ---" << std::endl;
    std::cout << GREEN_BG << "| W |" << RESET << "| E || A || R || Y |" << std::endl;
    std::cout << GREEN_BG << " ---" << RESET << "  ---  ---  ---  ---" << std::endl;
    std::cout << "\"W\" is in the word and in the correct spot." << std::endl;
    std::cout << " ---  " << YELLOW_BG << "---" << RESET << "  ---  ---  ---" << std::endl;
    std::cout << "| P |" << YELLOW_BG << "| I |" << RESET << "| L || L || S |" << std::endl;
    std::cout << " ---  " << YELLOW_BG << "---" << RESET << "  ---  ---  ---"  << std::endl;
    std::cout << "\"I\" is in the word but in the wrong spot." << std::endl;
    std::cout << " ---  ---  ---  " << GRAY_BG << "---" << RESET << "  ---"<< std::endl;
    std::cout << "| V || A || G |" << GRAY_BG << "| U |" << RESET << "| E |" << std::endl;
    std::cout <<" ---  ---  ---  " << GRAY_BG << "---" << RESET << "  ---" << std::endl;
    std::cout << "\"U\" is not in the word in any spot." << std::endl << std::endl;

}

void escapeClear(){
    std::cout << "Press [ENTER] to return to the Main Menu!" << std::endl;
    std::string line;

    std::getline(std::cin, line);
    //std:: cin >> line;
    if(!line.empty()){
          while(std::cin.peek() != '\n'){
            std::cin.ignore();
        }
    }
  
    system("clear");
}

void showStatsSummary(){
    system("clear");
    int attempts, totalAttempts = 0, correctAttempts = 0;
    int timesPlayed = 0, avgAttempts = 0, currentStreak = 0, longestStreak = 0;
    float winPercentage = 0;
    std::string word;
    std::string result;
    std::vector<std::string> detailedStats;

    std::ifstream inputFile("stats.txt");
    if(!inputFile.is_open()){
        std::cerr << "L" << std::endl;
        return;
    }

    while (inputFile >> word >> attempts >> result){
        timesPlayed++;
        totalAttempts+= attempts;
        if (result == "Yes"){
            correctAttempts++;
            currentStreak++;
        } else {
            currentStreak = 0; 

        }
        if (currentStreak > longestStreak){
            longestStreak = currentStreak;
        }
        detailedStats.push_back(word+ "\t"+ "\t"+ std::to_string(attempts)+ "\t"+result);


    }
    if (timesPlayed > 0){
        avgAttempts = totalAttempts/timesPlayed;
        winPercentage = static_cast<float>(correctAttempts)/timesPlayed*100;
    }
    std::cout << "==========================" << std::endl;
    std::cout << "    STATISTICS SUMMARY" << std::endl;
    std::cout << "==========================" << std::endl;
    std::cout << "Times Played:            " << timesPlayed << std::endl;
    std::cout << "Average Attempts:        " << avgAttempts << std::endl;
    std::cout << "Win Percentage:      " << std::fixed << std::setprecision(0)<< winPercentage << "%" << std::endl;
    std::cout << "Current Streak:          " << currentStreak << std::endl;
    std::cout << "Longest Streak:          " << longestStreak << std::endl << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "WORD     ATTEMPTS      WIN" << std::endl;
    std::cout << "--------------------------" << std::endl;
    for (const auto& detailedStat : detailedStats){
        std::cout << detailedStat << std::endl;
    }
    std::cout <<std::endl;
    inputFile.close();
}

void clearStats(){
    std::ofstream file("stats.txt", std::ios::trunc);
    std::cout << "Statistics cleared successfully!" << std::endl;
}


#endif 
