#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "analysis.h"
#include "cipher.h"


using namespace std;

int verbose = 0;



int main(int argc, char** argv){

    if(argc < 2){
        fprintf(stderr, "Usage: crackcipher [-v] <path>\n");
        exit(1);

    } else if(strcmp(argv[1], "-v") == 0){
        verbose = 1;
        fprintf(stderr, "Verbose mode not implemented yet. Please execute without verbose flag.\n");
        exit(1);
    }

    ifstream fileInput;
    if(verbose == 1){
        fprintf(stderr, "Executing in verbose mode.\n");
        fileInput.open(argv[2]);
    } else {
        fprintf(stderr, "Executing in non-verbose mode.\n");
        fileInput.open(argv[1]);
    }
    
    if(fileInput.fail()){
        fprintf(stderr, "Error: File not found. Progam will now exit.\n");
        exit(1);
    }

    string fileText { istreambuf_iterator<char>(fileInput), istreambuf_iterator<char>() };
    fprintf(stdout, "File opened successfuly. Starting to decipher...\n");
    

    
    double indexOfCoincidence = calculateIndexOfCoincidence(fileText);
    
    
    if(indexOfCoincidence > 0.055){
        fprintf(stdout, "Possible monoalphabetic encryption detected due to high IoC.\n"); 
    } else {
        fprintf(stdout, "Possible polyalphabetic encryption detected due to low IoC.\n");
    }
   
    
    fprintf(stdout, "Starting Frequency Analysis...\n");
    displayFrequencyAnalysis(fileText);

    
    
}





