#include <stdio.h>
#include <string>
#include <iterator> 
#include <map> 
#include "cipher.h"

using namespace std;


string decryptShiftCipher(string message, int key){

    string plaintext = "";
    int charValue = 0;
    int newCharValue = 0;

    for(int i = 0; i < message.length(); i++){
        charValue = message.at(i) - 65;
        newCharValue = (charValue - key) % 26;
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

//TODO
string decryptVigenereCipher(string message){

    return NULL;

}

//TODO
string decryptPermutationCipher(string message){

    return NULL;

}
