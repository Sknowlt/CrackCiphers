# CrackCiphers

## Description

Crack Ciphers currently only supports a small handful of encryptions due to it being used purely for a academic cryptography course.
The supported ciphers are as follows:

- Shift Cipher
- Substitution Cipher
- Vigenere Cipher
- Permutation Cipher (Columnar Transposition)
- One-Time Pad

Currently, decryption is supported but not automated for any cipher except for shift ciphers and any one-time pad ciphers. One-Time pad is based on a XOR problem, proving itself to be an unbreakable encryption given current methods.

---

## How to Run

If on Windows, you will need to have some form of GNU Make. This will allow the following commands to run in order to both build the project and clean the directory the project is in. These commands will need to be run within the project directory.

To Build:

```console
make crackcipher
```

To Clean Direcory on Windows:

```console
make dirclean
```

To Run on Windows:
Note: Replace \<path> with path to cipher text. In this project, four sample texts are provided as CipherTexts/cipher*.txt where \* can be 1 - 4.

```console
CrackCipher <path>
```

If on Linux, the build instrucitons will be the same. However, the directory cleaning command will not work due to using a Windows 'del' command. Thus, for Linux, you will need to clean the directory with the following command.

```console
make linuxdirclean
```

To Run on Linux:
Note: It is similar to the Windows run command. However, it will follow linux conventions.

```console
./CrackCiphers <path>
```
