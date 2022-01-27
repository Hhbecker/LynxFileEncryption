#ifndef LYNX_H
#define LYNX_H
#include <stdio.h>

void encrypt(void);
void decrypt(void);
int function(int num);
int functionInverse(int num);
void readTxt(FILE* fp);
void readBin(FILE* fp);
void promptUser(void);
int getSeed(char* fileName);
int getKey(int currentKey);

#endif 
