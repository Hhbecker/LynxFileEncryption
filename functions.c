#include "header.h"  
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include <assert.h>

void encrypt(char* txtFile){

    // use string functions to create encrypted binary filename from user input filename
    char* binFile = strdup(txtFile);
    binFile = strtok(binFile, ".");
    strcat(binFile, ".lynx");

    FILE *fp;
    FILE *fpBin;

    fp = fopen (txtFile, "r") ; // opening an existing file in r mode
   
    if ( fp == NULL ){
        printf ("Could not open plaintext file\n");
        return;
    }

    fpBin = fopen(binFile, "wb");  // w for write, b for binary

    if ( fpBin == NULL ){
        printf ("Could not open binary file\n");
        return;
    }

    char asChar; // unsigned 8 bit integer typedef

    // pass in seed it returns next seed 
    // first seed you pass in is file creation time
    int seed = getSeed(binFile);

    if(seed < 0 || seed > 60){
        printf("Seed retrieval error\n");
        return;    
    }

    // set first key as seed
    int key = seed;

    printf("\n\n...ENCRYPTION IN PROGRESS...\n") ;

    // iterate through each char in the text file
    while(1){
        asChar = fgetc(fp) ; // because the EOF constant is negative 1 a comparison to an unsigned uint8_t will always be false so we need to pass the character into a signed data type first for comparison to the EOF constant 
        if(asChar == EOF){
            break;
        }
        else {

            key = getKey(key);
    
            asChar = key ^ asChar;
            
            //&intByte gets address of int in memory and passes that address to fwrite
            fwrite(&asChar, sizeof(asChar), 1, fpBin);      
        }
    }

    fclose(fp);
    fclose(fpBin);
    
    printf("An encrypted binary version of your file has been created.\n\nEncrypted file contents:\n");
    
    char str[100];
    strcpy(str, "xxd -b ");
    strcat(str, binFile);
    strcat(str, " | cut -d: -f 2 | sed 's/  .*//'");    
    system(str);

    //system("xxd -b testDir/test.bin | cut -d: -f 2 | sed 's/  .*//'");
    printf("\n");

}

void decrypt(char* binFile){

    // this is where you would take in user input of filename to be encrypted
    //char* txtFile = "testDir/gibberishDecrypt.txt";
    //char* binFile = "testDir/test.bin";

    // use string functions to create encrypted binary filename from user input filename
    char* txtFile = strdup(binFile);
    txtFile = strtok(txtFile, ".");
    strcat(txtFile, ".txt");

    FILE *fp;
    FILE *fpBin;

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

    int key = seed;
    
    char asChar;

    int putcResult;
    
    printf("\n\n...DECRYPTION IN PROGRESS...\n");

    printf("Your file has been converted back to plaintext format. \n\nDecrypted file contents:\n\"");

    while(1){
        asChar = fgetc(fpBin) ; 
        if(asChar == EOF){   // EOF constant is -1
            break;
        }
        else {

            key = getKey(key);

            asChar = key ^ asChar;
            
            //&intByte gets address of int in memory and passes that address to fwrite
            putcResult = fputc(asChar, fp);   
            printf("%c", asChar);   
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


int getKey(int currentKey){
    int newKey = (currentKey*currentKey)/2;
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

