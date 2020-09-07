#ifndef CIPHER_H
#define CIPHER_H

char* decryptShiftCipher(char* message);
char* decryptSubstitutionCipher(char* message);
char* decryptVigenereCipher(char* message);
char* decryptPermutationCipher(char* message);
char* decryptOneTimePadCipher(char* message);

#endif