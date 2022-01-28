#include "header.h"  
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include <assert.h>

// link to Header file "hashmap.h" which contains:
// linked list node struct "llnode"
// hashmap struct "hashmap"

int main(void){

    printf("\n -- WELCOME TO LYNX ENCRYPTION -- \n\n");

    // call the prompt user function
    promptUser();

}

void promptUser(void){

    printf("Please enter e to encrypt, d to decrypt, or x to exit:\n\n");

    // flush stdin buffer from previous getchar calls
    fflush(stdin);

    // read input char from user (only allow single char input, error check if it is not e,d, or x)
    int input = getchar();

    // if input is e for encrypt
    if(input == 101){
        fflush(stdin);
        char* fileName = readFileName();
        encrypt(fileName);

        // return to user prompt after encryption completes
        promptUser(); 
    }
    // if input is d for decrypt
    else if(input == 100){
        fflush(stdin);
        char* fileName = readFileName();
        decrypt(fileName);

        // return to user prompt after encryption completes
        promptUser();
    }

    else if(input == 120){
        exit(0);
    }

    else{
        printf("\nInput invalid. ");
        promptUser();
    }
}

char* readFileName(void){
    char* directory;
    printf("Please specify the filepath and document name:\n");
    
    // create inputs for getline function
    char* line = NULL;
    size_t len = 0;
    size_t lineSize = 0;

    lineSize = getline(&line, &len, stdin); 
    if(lineSize){
        // to avoid error: variable ‘lineSize’ set but not used
    }

    directory = strtok(line, "\n");

    return directory;
}
