#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <iostream> 
#include <iterator> 
#include <map> 
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;


double calculateIndexOfCoincidence(string message);
void displayFrequencyAnalysis(string message);
string determineCipherAndCrackCipher(string message);
double calculateShiftedIndexOfCoincidence(char* message);
double calculateKasiskiTest(char* message);


#endif