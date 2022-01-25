#include "header.h"  
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include <assert.h>

void readFile(int mode){
    // bool debug = true;

    // read in file name
    printf("\nPlease specify the document you would like to encrypt:\n");
    //printf("Example: 'p5docs/*.txt'\n");
    
    char* fileName = "testDir/gibberish.txt";

    // first check for EOF then cast to char 

    int asInt;
    char asChar;

    FILE *fp ;
    
    printf( "Opening the file\n" ) ;
    fp = fopen ( fileName, "r" ) ; // opening an existing file
    if ( fp == NULL )
    {
        printf ("Could not open file\n");
        return;
    }
    printf( "File contents:\n" ) ;
    while(1){
        asInt = fgetc (fp) ; // reading the file
        if(asInt==EOF){
            break;
        }
        if(asInt>127){
            //printf("Non ascii characters present in file, these characters will be replaced with ?\n");
        }
        asChar = (char) asInt;
        printf("%c", asChar);
    }
   
    fclose(fp);

    printf("\n\nOpening the file\n") ;
    fp = fopen (fileName, "r+") ; // opening an existing file in r+ mode
   
    if ( fp == NULL ){
        printf ("Could not open file\n");
        return;
    }

    if(mode == 0){
        printf("Encrypted file contents:\n");
    }
    else{
        printf("Decrypted file contents:\n");
    }
    
    int newInt;
    char newChar;

    while(1){
        asInt = fgetc (fp) ; // reading the file
        if(asInt==EOF){
            break;
        }
        else if(mode == 0){
            newInt = encrypt(asInt);
            newChar = (char) newInt; 
        
            // set the position of the stream one character back, this is done by getting the current 
            // position using ftell, subtracting one from it and using fseek to set a new position
            fseek(fp, ftell(fp) - 1, SEEK_SET);

            //fprintf(fp, "%c", newChar);
            fprintf(fp, "%d", newInt);
            printf("%d", newInt);
        }
        else{
            newInt = decrypt(asInt);
            newChar = (char) newInt;
            // set the position of the stream one character back, this is done by getting the current 
            // position using ftell, subtracting one from it and using fseek to set a new position
            fseek(fp, ftell(fp) - 1, SEEK_SET);

            fprintf(fp, "%c", newChar);
            //fprintf(fp, "%d", newInt);
            printf("%d", newInt);
        }
    }

    printf("\nClosing the file\n\n") ;
    fclose(fp);

    // We use the getw() and putw() I/O functions to read an integer from a file 
    // and write an integer to a file respectively. 
    // Syntax of getw: int num = getw(fptr); Where, fptr is a file pointer.



}

// must return an int between 0-127
int encrypt(int num){
    // must ask for file and check file
    return num-100;
}


int decrypt(int num){
    // must ask for file and check file
    return num+100;
}


// I'm converting to binary because if I kept everything in ascii I would have to restrain the results of the ciphertext to integers between 0 and 127 which greatly decreases the strength of the encryption



