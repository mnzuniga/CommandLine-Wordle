#include <igloo/igloo.h>
#include <cstdlib>
#include <iostream>
#include "utils.h"
using namespace igloo;

std::string exec(std::string command) {
   char buffer[128];
   std::string result = "";

   // Open pipe to file
   FILE* pipe = popen((command + " 2>&1").c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   result.erase(result.find_last_not_of(" \t\n\r\f\v") + 1);
   return result;
}

Context(TestWordle){
    static void SetUpContext(){
        exec("g++ main.cpp -o temp");
    }
    static void TearDownContext() {
        system("rm -rf temp");
    }

    Spec(TestDoesContainLetter){
        std::string word = "CLEAN";
        char letter = 'E';
        int doesContain = contains(word, letter);
        int expected = 2;
        Assert::That(doesContain, Equals(expected));
    }
    Spec(TestDoesNotContainLetter){
        std::string word = "CLEAN";
        char letter = 'D';
        int doesContain = contains(word, letter);
        int expected = -1;
        Assert::That(doesContain, Equals(expected));
    }
    Spec(TestDoesContainNumber){
        std::vector<int> numbers;
        numbers.push_back(2);
        numbers.push_back(4);
        int value = 4;
        bool doesContain = contains(numbers, value);
        bool expected = true;
        Assert::That(doesContain, Equals(expected));
    }
    Spec(TestDoesNotContainNumber){
        std::vector<int> numbers;
        numbers.push_back(2);
        numbers.push_back(4);
        int value = 5;
        bool doesContain = contains(numbers, value);
        bool expected = false;
        Assert::That(doesContain, Equals(expected));
    }
    Spec(CheckAttemptAllColors){
        std::string solution = "SLATE";
        std::string attempt = "STEAK";
        std::string result = checkAttempt(solution, attempt);
        std::string expected = "";
        expected += green('S') + ' ';
        expected += yellow('T') + ' ';
        expected += yellow('E') + ' ';
        expected += yellow('A') + ' ';
        expected += gray('K') + ' ';
        Assert::That(result, Equals(expected));
    }
    Spec(CheckLogicColors){
        std::string solution = "SLATE";
        std::string attempt = "SLEEP";
        std::string result = checkAttempt(solution, attempt);
        std::string expected = "";
        expected += green('S') + ' ';
        expected += green('L') + ' ';
        expected += yellow('E') + ' ';
        expected += gray('E') + ' ';
        expected += gray('P') + ' ';
        Assert::That(result, Equals(expected));
    }

};

int main(int argc, const char* argv[]){
    TestRunner::RunAllTests(argc, argv);
}
