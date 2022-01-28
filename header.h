#ifndef LYNX_H
#define LYNX_H
#include <stdio.h>

void encrypt(char* txtFile);
void decrypt(char* binFile);
void promptUser(void);
int getSeed(char* fileName);
int getKey(int currentKey);
char* readFileName(void);

#endif 
