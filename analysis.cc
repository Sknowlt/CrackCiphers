#include "analysis.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>


double calculateIndexOfCoincidence(char* message){

    double result = 0.0;
    int characterFrequency[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int N = strlen(message);
    int currChar;

    for(int i = 0; i <strlen(message); i++){
        currChar = message[i] - 65;
        characterFrequency[currChar]++;
    }

    for(int j = 0; j < 26; j++){
        result += ((double)(characterFrequency[j] * (characterFrequency[j]-1))/ (double)(N * (N-1)));
    }

    return result;
}

//TODO
void displayFrequencyAnalysis(char* message){

}

//TODO
double calculateShiftedIndexOfCoincidence(char* message){

    return 0.0;

}

//TODO
double calculateKasiskiTest(char* message){

    return 0.0;

}