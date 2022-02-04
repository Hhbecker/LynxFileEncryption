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
        fclose(fp);
        return;
    }

    // open binary file in write binary mode
    fpBin = fopen(binFile, "wb"); 

    // make sure binary file was succesfully opened
    if ( fpBin == NULL ){
        printf ("Could not open binary file\n");
        fclose(fp);
        fclose(fpBin);
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
        fclose(fp);
        fclose(fpBin);
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
            //currentChar = key ^ currentChar; // (non assembly implementation)

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

    char str2[40];
    strcpy(str2, " | cut -d: -f 2 | sed 's/  .*//'");
    strcat(str, str2);
    //printf("System command is: %s\n", str); 
   
    //system(str);
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

    // make sure binary file was succesfully opened 
    if ( fp == NULL ){
        printf ("Could not open plaintext file\n");
        fclose(fp);
        return;
    }

    // open binary file in write 
    fpBin = fopen(binFile, "rb");  // r for read, b for binary

    // make sure binary file was succesfully opened 
    if ( fpBin == NULL ){
        printf ("Could not open binary file\n");
        fclose(fp);
        fclose(fpBin);
        return;
    }

    // set initial key to seed
    int8_t key = (int8_t) getSeed(binFile);

    // if key is not within 0-60 seconds something went wrong
    if(key < 0 || key > 60){
        printf("Seed retrieval error\n");
        fclose(fp);
        fclose(fpBin);
        return;    
    }
    
    // create variable to hold current character from the text file 
    char currentChar;

    // create return value variable for putc function
    int putcResult;
    
    printf("\n\n...DECRYPTION IN PROGRESS...\n");

    printf("Your file has been converted back to plaintext format. \n\nDecrypted file contents:\n\"");

    // iterate through each char in the text file
    while(1){
        // assign next byte in getchar buffer to currentChar variable
        currentChar = fgetc(fpBin) ; 
        // EOF constant is -1
        if(currentChar == EOF){   
            break;
        }
        else {
            // perform computation on key to get next pseudorandom key
            key = getKey(key);

            // currentChar = key ^ currentChar; (non assembly implementation)

            // assembly implementation of bitwise XOR on char and key (see encrypt function for more info)
            __asm__ ( "xorb %%bl, %%al;"
            : "=a" (currentChar)
            : "a" (currentChar), "b" (key) );
            
            //&intByte gets address of int in memory and passes that address to fwrite
            putcResult = fputc(currentChar, fp);   
            printf("%c", currentChar);   
        }
    }

    // close both text and binary files
    fclose(fp);
    fclose(fpBin);

    printf("\"\n\n");

}

// getKey: perform computation on current key to generate next pseudorandom key
// input: current key
// returns: new current key
int8_t getKey(int8_t currentKey){
    // square current key and divide it by two then subtract 5 to get the new key
    int8_t newKey = (currentKey*currentKey)/2;
    return (newKey - 5);
}

// getSeed: runs a bash command to retrieve the creation date of the file specified in the input, 
// temporarily writes the second of the creation time to a file and saves the contents of this file into 
// the C variable number which is the seed of the encrpytion key and is returned by this function
// input: fileName of binary file to encrypt or decrypt
// returns: seed integer
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

    // create variable to store
    int number;

    in_file = fopen(tempFile, "r");

    // make sure file opened properly
    if (in_file == NULL){
        printf("Can't open seed temp file for reading.\n");
        return -1;
    }

    else{
        // read in number from temp file as a line
        fscanf(in_file, "%d", &number);
        fclose(in_file);
    }

    // delete temp file
    remove(tempFile);

    return number;
}

