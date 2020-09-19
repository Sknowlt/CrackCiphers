#include "analysis.h"
#include <iostream> 
#include <iterator> 
#include <map> 
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;



double calculateIndexOfCoincidence(string message){
    double result = 0.0;
    int characterFrequency[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int N = message.length();
    int currChar;
    for(int i = 0; i < message.length(); i++){
        currChar = message[i] - 65;
        characterFrequency[currChar]++;
    }
    for(int j = 0; j < 26; j++){
        result += ((double)(characterFrequency[j] * (characterFrequency[j]-1))/ (double)(N * (N-1)));
    }
    return result;
}


void displayFrequencyAnalysis(string message){

    map<char, int>monograms;
    map<string, int>digrams;
    map<char, int>::iterator monoIterator;
    map<string, int>::iterator diIterator;
    
    for(int i = 0; i < message.length()-1; i++){
        if(monograms.find(message.at(i)) == monograms.end()){
            monograms.insert({message.at(i), 0});
        } else {
            monoIterator = monograms.find(message.at(i));
            monoIterator->second++;
        }
        
        string digram = message.substr(i,2);
        if(digrams.find(digram) == digrams.end()){
            digrams.insert({digram, 1});
        } else {
            diIterator = digrams.find(digram);
            diIterator->second++;
        }
        digram.clear();
    }

    if(monograms.find(message.back()) == monograms.end()){
        monograms.insert({message.back(), 0});
    } else {
        monoIterator = monograms.find(message.back());
        monoIterator->second++;
    }

    int printTracker = 0;
    fprintf(stdout, "\nThe monograms (in percentages) are as follow:\n");    
    for(auto &monos : monograms){
        printTracker++;
        if(printTracker == 5){
            fprintf(stdout, "%15c - %-.4f\n",monos.first, ((double) monos.second/(double)message.length()) * 100);
            printTracker = 0;
        } else {
            fprintf(stdout, "%15c - %-.4f",monos.first, ((double) monos.second/(double)message.length()) * 100);
        }
    }
    
    printTracker = 0;

    fprintf(stdout, "\n\nThe digrams (in percentages) are as follow:\n");
    for(auto &dis : digrams){
        
        printTracker++;
        if(printTracker == 5){
            fprintf(stdout, "%15s - %-.4f\n",dis.first.c_str(),((double) dis.second/(double)message.length()) * 100);
            printTracker = 0;
        } else {
            fprintf(stdout, "%15s - %-.4f",dis.first.c_str(), ((double) dis.second/(double)message.length()) * 100);
        }
        
    }

    fprintf(stdout, "\n");

}

//TODO
double calculateShiftedIndexOfCoincidence(char* message){

    return 0.0;

}

//TODO
double calculateKasiskiTest(char* message){

    return 0.0;

}