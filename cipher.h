#ifndef CIPHER_H
#define CIPHER_H

#include <string>

using namespace std;

string decryptShiftCipher(string message, int shift);
string decryptSubstitutionCipher(string message, string key);
string decryptVigenereCipher(string message);
string decryptPermutationCipher(string message);


#endif