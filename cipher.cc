#include <stdio.h>
#include <iostream> 
#include <vector> 
#include <string>
#include <iterator> 
#include <map> 
#include <math.h>
#include "cipher.h"

using namespace std;


string decryptShiftCipher(string message, int key){

    string plaintext = "";
    int charValue = 0;
    int newCharValue = 0;

    for(int i = 0; i < message.length(); i++){
        charValue = message.at(i) - 65;
        newCharValue = (charValue - key) % 26;
        if(newCharValue < 0){
            newCharValue += 26;
        }
        plaintext += (char)(newCharValue + 65);
    }

    return plaintext;

}





string decryptSubstitutionCipher(string message, string key){
 
    map<char, char>decryptMap;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string plaintext = "";

    for(int i = 0; i < 26; i++){
        decryptMap.insert({key.at(i),alphabet.at(i)});
    }

    for(int j = 0; j < message.length(); j++){
        plaintext += (char)(decryptMap.at(message.at(j)));
    }
    return plaintext;

}





string decryptVigenereCipher(string message, string key){

    string plaintext = "";

    int j = 0;
    for(int i = 0; i < message.length(); i++){
        plaintext += (char)(((message.at(i) - key.at(j) + 26) % 26)+65);
        if(j == (key.length()-1)){
            j = 0;
        } else{
            j++;
        }  
    }

    return plaintext;

}


string decryptPermutationCipher(string message, string key){
    
    string plaintext = "";
    int columnLength = ceil((double)message.length()/ (double)key.length());

    map<char,int>keyIndex;
    for(int i = 0; i < key.length(); i++){
        keyIndex.insert({key.at(i), i});
    }
    vector<vector<char>> cipherMatrix(columnLength, vector<char>(key.length()));
    vector<vector<char>> resultMatrix(columnLength, vector<char>(key.length()));
    
    int messageIndex = 0;
    for(int i = 0; i < key.length(); i++){
        for(int j = 0; j < columnLength; j++){
            if(messageIndex < message.length()){
                if(!isalpha(message.at(messageIndex))){
                    cipherMatrix[j][i] = '-';
                } else {
                    cipherMatrix[j][i] = message.at(messageIndex);
                }
                 
            } else {
                cipherMatrix[j][i] = '-';
            }
            
            messageIndex++;
        }
    }


    for(int i = 0; i < key.length(); i++){
        for(int j = 0; j < cipherMatrix.size(); j++){
            resultMatrix[j][keyIndex[key[i]]] = cipherMatrix[j][distance(keyIndex.begin(),keyIndex.find(key[i]))];
        }
    }


    for(int i = 0; i < resultMatrix.size(); i++){
        for(int j = 0; j < resultMatrix.at(i).size(); j++){
            if(resultMatrix[i][j] != '-'){
                plaintext += resultMatrix[i][j];
            }
        }
    }
    
    return plaintext;

}
