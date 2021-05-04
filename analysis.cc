#include "analysis.h"
#include "cipher.h"
#include <iostream> 
#include <iterator> 
#include <map> 
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>


using namespace std;

map<char, int>monograms;
vector<pair<char,int>> monogramsSortedByValue;
map<string, int>digrams;
vector<pair<string,int>> digramsSortedByValue;
map<char, int>::iterator monoIterator;
map<string, int>::iterator diIterator;


bool cmpDescValueMono(pair<char, int>& pair1, pair<char, int>& pair2){
    return pair1.second > pair2.second;
}

bool cmpDescValueDi(pair<string, int>& pair1, pair<string, int>& pair2){
    return pair1.second > pair2.second;
}

double calculateIndexOfCoincidence(string message){
    fprintf(stdout, "Calculating Index of Coincidence...\n\n");
    
    

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
    fprintf(stdout, "Index of Coincidence: %f\n\n", result);
    return result;
}





void calculateFrequencyAnalysis(string message){
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

    for(auto &monos : monograms){
        monogramsSortedByValue.push_back(monos);
    }
    sort(monogramsSortedByValue.begin(), monogramsSortedByValue.end(), cmpDescValueMono);

    for(auto &dis : digrams){
        digramsSortedByValue.push_back(dis);
    }
    sort(digramsSortedByValue.begin(), digramsSortedByValue.end(), cmpDescValueDi);


}





void displayFrequencyAnalysis(string message){

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

    fprintf(stdout, "\n\n");

}


void determineCipherAndCrackCipher(string message){
    
    double indexOfCoincidence = calculateIndexOfCoincidence(message);
    calculateFrequencyAnalysis(message);
    displayFrequencyAnalysis(message);
    if(indexOfCoincidence > 0.065){
        fprintf(stdout,"Possible monoalphabetic cipher detected due to a high index of coincidence.\n");
        fprintf(stdout,"The following ciphers may be possible: Shift, Substitution, and Permutation.\n");
        fprintf(stdout,"Checking for possible shift cipher.\n");
        
        //Note: The following alphabet by decreasing frequency was found at the following site.
        //http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
        string alphaByFreq = "ETAOINSRHDLUCMFYWGPBVKXQJZ";
        
        int potentialShift = ((int)monogramsSortedByValue.at(0).first - (int)alphaByFreq.at(0)) % 26;
        if(potentialShift < 0){
            potentialShift += 26;
        }
        int shiftMatches = 0;
        int shift = 0;
        for(int i = 0; i < 26; i++){
            shift = ((int)monogramsSortedByValue.at(i).first - (int)alphaByFreq.at(i)) % 26;
            if(shift < 0){
                shift += 26;
            }
            if(shift == potentialShift){
                shiftMatches++;
            }
        }
        
        if(shiftMatches >= 8){
            fprintf(stdout,"Shift Checking has yielded a strong chance that the cipher is a shift cipher with a key of %d.\n\n", potentialShift);
            string plaintext = decryptShiftCipher(message, potentialShift);
            fprintf(stdout, "Plain Text after deciphering shift cipher with a key of %d:\n\n", potentialShift);
            
            string isValid;
            int validLock = 0;
            while(!validLock){
                fprintf(stdout, "%s\n\nIs this a valid deciphered text? Enter y or n for yes or no respectively.\n", plaintext.c_str());
                cin >> isValid;
                if(isValid.compare("y") == 0 || isValid.compare("Y") == 0){
                    fprintf(stdout, "The decryption has succeeded. Program will now exit.\n");
                    validLock = 1;
                } else if(isValid.compare("n") == 0 || isValid.compare("N") == 0){
                    fprintf(stdout, "The decryption has failed. Program will now exit.\n\n");
                    validLock = 1;
                }
            }
        }else{
            fprintf(stdout, "Shift Checking has yielded that the cipher is unlikely to be a shift cipher.\n");
            fprintf(stdout, "Checking for possible substitution cipher...\nPlease Note: Substitution cipher cracking will be done manually.\nPlease enter a possible 26 character key in the order of character substitutions:\n");
            string subKey;
            cin >> subKey;
            if(subKey.length() < 26){
                fprintf(stdout,"Error: Key is not long enough. Please rerun the program with a valid 26 character key\n");
                exit(1);
            }
            fprintf(stdout, "Plain text after attempting decipher with a key of '%s':\n\n",subKey.c_str());
            transform(subKey.begin(), subKey.end(), subKey.begin(), ::toupper);
            string plaintext = decryptSubstitutionCipher(message, subKey);
            
            string isValid;
            int validLock = 0;
            while(!validLock){
                fprintf(stdout, "%s\n\nIs this a valid deciphered text? Enter y or n for yes or no respectively.\n", plaintext.c_str());
                cin >> isValid;
                if(isValid.compare("y") == 0 || isValid.compare("Y") == 0){
                    fprintf(stdout, "The decryption has succeeded. Program will now exit.\n");
                    validLock = 1;
                } else if(isValid.compare("n") == 0 || isValid.compare("N") == 0){
                    fprintf(stdout, "The decryption has failed. Program will now exit.\n\n");
                    validLock = 1;
                }
            }
        }


    } else if(indexOfCoincidence >0.04){
        fprintf(stdout,"Possible polyalphabetic cipher detected due to a low index of coincidence.\n");
        fprintf(stdout,"The following cipher may be possible: Vigenere.\n");
        fprintf(stdout, "Checking for possible vigenere cipher.\nCalculating a sample frequency analaysis.\nFrequency Analysis:\n\n");
        displayFrequencyAnalysis(message);
        fprintf(stdout,"Automatic Cracking is not finished yet. Please enter a possible key:\n");
        string subKey;
        cin >> subKey;
        fprintf(stdout, "Plain text after attempting decipher with a key of '%s':\n\n",subKey.c_str());
        transform(subKey.begin(), subKey.end(), subKey.begin(), ::toupper);
        string plaintext = decryptVigenereCipher(message, subKey);
            
        string isValid;
        int validLock = 0;
        while(!validLock){
            fprintf(stdout, "%s\n\nIs this a valid deciphered text? Enter y or n for yes or no respectively.\n", plaintext.c_str());
            cin >> isValid;
            if(isValid.compare("y") == 0 || isValid.compare("Y") == 0){
                fprintf(stdout, "The decryption has succeeded. Program will now exit.\n");
                validLock = 1;
            } else if(isValid.compare("n") == 0 || isValid.compare("N") == 0){
                fprintf(stdout, "The decryption has failed. Program will now exit.\n\n");
                validLock = 1;
                }
            }


    } else {
        fprintf(stdout,"Possible one time pad cipher detected due to an extremely low index of coincidence\n");
        fprintf(stdout,"One time pad is not decryptable without knowing the exact key.\nThe program will now exit.\n");
        exit(1);
    }

}

