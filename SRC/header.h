#ifndef LYNX_H
#define LYNX_H

#include <stdlib.h>

void encrypt(char* txtFile);
void decrypt(char* binFile);
void promptUser(void);
int getSeed(char* fileName);
uint8_t getKey(uint8_t currentKey);
char* readFileName(void);

#endif 
