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

    // printf("Input is = %d\n", input);

    // if input is e for encrypt
    if(input == 101){
        // 0 triggers readFile encrypt mode
        encrypt();

        printf("your file has been converted to an encrypted binary format. To view encrypted binary press v\n");
        
        // return to user prompt after encryption completes
        promptUser(); 
    }
    // if input is d for decrypt
    else if(input == 100){
        // 1 triggers readFile decrypt mode
        //decrypt();

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
