/*
Functional methods for the Lynx Encryption Module.
Author: Henry Becker
Date: 2/2/22
This application is MIT licensed.
*/

#include <stdio.h>    
#include <stdlib.h>
#include <string.h>

// link to Header file "hashmap.h" which contains functions headers
#include "header.h" 

// encrypt: open file requested by user, create binary file with .lynx extension, encrypt each char 
// of text file and write encrypted binary to binary file without altering text file, close both files
// input: char pointer to filename of user requested text file
// returns: void
void encrypt(char* txtFile){

    // use string functions to create encrypted binary filename from user input filename
    char* binFile = strdup(txtFile);
    // save all characters of filename before the first "." character into the binFile variable
    binFile = strtok(binFile, ".");
    // add the ".lynx" extension to the filename
    strcat(binFile, ".lynx");

    // create file pointers for both the text and binary file
    FILE *fp;
    FILE *fpBin;

    // open text file in read mode
    fp = fopen (txtFile, "r") ; 
   
    // make sure file is succesfully opened
    if ( fp == NULL ){
        printf ("Could not open plaintext file\n");
        return;
    }

    // open binary file in write binary mode
    fpBin = fopen(binFile, "wb"); 

    // make sure binary file was succesfully opened
    if ( fpBin == NULL ){
        printf ("Could not open binary file\n");
        return;
    }

    // create variable to hold current character from the text file 
    char currentChar; 

    // get number generator seed which is the creation time of the binary file held by the OS
    int key = (int8_t) getSeed(binFile);

    // the seed is currently supposed to be the seconds of the hours:minutes:seconds of the creation time
    // if the seconds is not between 0-60 something went wrong
    if(key < 0 || key > 60){
        printf("Seed retrieval error\n");
        return;    
    }

    printf("\n\n...ENCRYPTION IN PROGRESS...\n") ;

    // iterate through each char in the text file
    while(1){
        // set currentChar var to the next char in the input buffer using fgetc()
        currentChar = fgetc(fp); 
        // if the current char equals -1 (the end of file ) break loop
        if(currentChar == EOF){
            break;
        }
        else {

            // perform calculation to produce pseudorandom key 
            key = getKey(key);
    
            // XOR the key with the current char
            // currentChar = key ^ currentChar; (non assembly implementation)

            // assembly implementation of bitwise XOR on char and key
            // xorb = xor opcode on a single byte of data 
            // %%bl = lowest 8 bits of general purpose register EBX (source register)
            // %%al = lowest 8 bits of general purpose register EAX (source register/destination register)
            // first line following colon is output info
            // second line following colon is input info
            // =a is assigning the destination register of the computation to the "currentChar" variable
            // see the below site for more information
            // https://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C

            //////////////////////////////////
            __asm__ ( "xorb %%bl, %%al;"
            : "=a" (currentChar)
            : "a" (currentChar), "b" (key) );
            //////////////////////////////////

            //&intByte gets address of int in memory and passes that address to fwrite
            fwrite(&currentChar, sizeof(currentChar), 1, fpBin);      
        }
    }

    // close both file pointers
    fclose(fp);
    fclose(fpBin);
    
    printf("An encrypted binary version of your file has been created.\n\nEncrypted file contents:\n");
    
    // use string splitting to create the necessary terminal command to print binary in a sleek format using xxd function 
    //system("xxd -b fileName | cut -d: -f 2 | sed 's/  .*//'");
    char str[100];
    strcpy(str, "xxd -b ");
    strcat(str, binFile);
    strcat(str, " | cut -d: -f 2 | sed 's/  .*//'");    
    system(str);
    printf("\n");

}

// decrypt: open binary file requested by user, create text file, decrypt each byte 
// of binary file and write corresponding ascii to text file without altering binary file, close both files
// input: char pointer to filename of user requested binary file
// returns: void
void decrypt(char* binFile){

    // use string functions to create unencrypted text filename from user input binary filename
    char* txtFile = strdup(binFile);
    // save all characters of filename before the first "." character into the txtFile variable
    txtFile = strtok(txtFile, ".");
    // add the ".txt" extension to the filename 
    strcat(txtFile, ".txt");

    // create file pointers for both text and binary file
    FILE *fp;
    FILE *fpBin;

    // open text file in write mode
    fp = fopen (txtFile, "w") ; // opening a file in r mode
   
    if ( fp == NULL ){
        printf ("Could not open plaintext file\n");
        return;
    }

    fpBin = fopen(binFile, "r");  // r for read, b for binary

    if ( fpBin == NULL ){
        printf ("Could not open binary file\n");
        return;
    }

    // pass in seed it returns next seed 
    // first seed you pass in is file creation time
    int seed = getSeed(binFile);

    if(seed < 0 || seed > 60){
        printf("Seed retrieval error\n");
        return;    
    }

    int8_t key = (int8_t) seed;
    
    char currentChar;

    int putcResult;
    
    printf("\n\n...DECRYPTION IN PROGRESS...\n");

    printf("Your file has been converted back to plaintext format. \n\nDecrypted file contents:\n\"");

    while(1){
        currentChar = fgetc(fpBin) ; 
        if(currentChar == EOF){   // EOF constant is -1
            break;
        }
        else {

            key = getKey(key);

            // currentChar = key ^ currentChar; (non assembly implementation)

            // assembly implementation of bitwise XOR on char and key
            __asm__ ( "xorb %%bl, %%al;"
            : "=a" (currentChar)
            : "a" (currentChar), "b" (key) );
            
            //&intByte gets address of int in memory and passes that address to fwrite
            putcResult = fputc(currentChar, fp);   
            printf("%c", currentChar);   
        }
    }

    fclose(fp);
    fclose(fpBin);

    printf("\"\n\n");

}

    // An early computer-based PRNG, suggested by John von Neumann in 1946, 
    // is known as the middle-square method. The algorithm is as follows: 
    // take any number, square it, remove the middle digits of the resulting 
    // number as the "random number", then use that number as the seed for the 
    // next iteration.


int8_t getKey(int8_t currentKey){
    int8_t newKey = (currentKey*currentKey)/2;
    return (newKey - 5);
}

// This function runs a bash command to retrieve the creation date of the file specified in the input, 
// temporarily writes the second of the creation time to a file and saves the contents of this file into 
// the C variable number which is the seed of the encrpytion key and is returned by this function
int getSeed(char* fileName){

    //concatenate filename string with rest of command
    const char* tempFile = "seedTemp.txt";

    //send second of file creation into file seedTemp.txt
    char str[100];
    strcpy(str, "GetFileInfo ");
    strcat(str, fileName);
    strcat(str, " | sed -n 5p | cut -d ':' -f 4 > ");
    strcat(str, tempFile);
    // full string is "GetFileInfo fileName.txt | sed -n 5p | cut -d ':' -f 4 > seedTemp.txt"
    // pipe the output of the GetFileInfo command into sed which pipes the 5th line of the ouput 
    // to cut which sends the information after the 4th colon to the file seedTemp.txt
    system(str);

    // open seedTemp.txt and save value as integer
    FILE *in_file;
    int number;

    in_file = fopen(tempFile, "r");

    if (in_file == NULL)
    {
        printf("Can't open seed temp file for reading.\n");
        return -1;
    }
    else
    {
        fscanf(in_file, "%d", &number);
        fclose(in_file);
    }

    remove(tempFile);

    return number;
}

