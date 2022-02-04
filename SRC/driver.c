/*
Main and driver methods for the Lynx Encryption Module.
Author: Henry Becker
Date: 2/2/22
This application is MIT licensed.
*/

#include <stdio.h>    
#include <stdlib.h>
#include <string.h>

// link to Header file "hashmap.h" which contains functions headers
#include "header.h" 

// promptUser: requests user for action and interprets user input to call correct function
// input: void
// returns: void
int main(void){

    // message on start up
    printf("\n -- WELCOME TO LYNX ENCRYPTION -- \n\n");
  
    printf("This application is MIT licensed. Author: Henry Becker. Date: Jan 2022\n\n");

    promptUser();

}

// promptUser: requests user for action and interprets user input to call correct function
// input: void
// returns: void
void promptUser(void){

    printf("Please enter e to encrypt, d to decrypt, or x to exit:\n\n");

    // flush stdin buffer from previous getchar calls
    fflush(stdin);

    // read input char from user (only allow single char input)
    int input = getchar();

    // if input is e for encrypt
    if(input == 101){
        // flush buffer for getchar calls within encrypt function
        fflush(stdin);
        // retrieve fileName for input into encrypt function
        char* fileName = readFileName();
        encrypt(fileName);

        // return to user prompt after encryption completes
        promptUser(); 
    }
    // if input is d for decrypt
    else if(input == 100){
        // flush buffer for getchar calls within decrypt function
        fflush(stdin);
        // retrieve fileName for input into decrypt function
        char* fileName = readFileName();
        decrypt(fileName);

        // return to user prompt after encryption completes
        promptUser();
    }

    // if input is x quit program
    else if(input == 120){
        exit(0);
    }

    // if input is not edx return to user prompt
    else{
        printf("\nInput invalid. ");
        promptUser();
    }
}

// readFileName: uses the getline c function to save a user input file name into a char array
// input: void
// returns: pointer to char array containing filename for encryption or decryption
char* readFileName(void){
    char* directory;
    printf("Please specify the filepath and document name:\n");
    
    // create inputs for getline function
    char* line = NULL;
    size_t len = 0;
    size_t lineSize = 0;

    // set line variable equal to char array of contents of standard in
    lineSize = getline(&line, &len, stdin); 
    if(lineSize){
        // to avoid error: 'variable ‘lineSize’ set but not used'
    }

    // remove newline from char array by tokenizing string 
    directory = strtok(line, "\n");

    // return filename requested by user without newline
    return directory;
}
