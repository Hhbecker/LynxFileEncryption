#include "header.h"  
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include <assert.h>

void encrypt(void){

    printf("\n\nENCRYPTION IN PROGRESS...\n") ;

    printf("\n\nOpening the file\n") ;

    // this is where you would take in user input of filename to be encrypted
    char* txtFile = "testDir/gibberish.txt";
    char* binFile = "testDir/test.bin";

    //first check for EOF then cast to char 

    int asInt;

    FILE *fp;

    fp = fopen (txtFile, "r") ; // opening an existing file in r+ mode
   
    if ( fp == NULL ){
        printf ("Could not open file\n");
        return;
    }

    FILE *fpBin;

    fpBin = fopen(binFile, "wb");  // w for write, b for binary

    if ( fpBin == NULL ){
        printf ("Could not open binary file\n");
        return;
    }

    //int newInt;
    char newChar;

    // pass in seed it returns next seed 
    // first seed you pass in is file creation time

    // iterate through each char in the text file
    while(1){
        asInt = fgetc (fp) ; // reading the file
        if(asInt==EOF){
            break;
        }
        else {
            //newInt = function(asInt);
            newChar = (char) asInt;

            //&newInt gets address of int in memory and passes that address to fwrite
            fwrite(&newChar, sizeof newChar, 1, fpBin);      
        }
    }



    printf("\nClosing the file\n\n") ;
    fclose(fp);
    fclose(fpBin);

    int seed = getSeed(binFile);
    if(seed >= 0 && seed <=60){
        printf("Encryption key seed retrieved succesfully. Seed = %d\n", seed);
    }
    else{
        printf("Seed retrieval error\n");
    }



}

void decrypt(void){

    // this is the encrypt code
    // diferences include - reading from binary and writing to text instead of other way around 
    // 

    printf("\n\nENCRYPTION IN PROGRESS...\n") ;

    printf("\n\nOpening the file\n") ;

    // this is where you would take in user input of filename to be encrypted
    char* txtFile = "testDir/gibberish.txt";
    char* binFile = "testDir/test.bin";

    //first check for EOF then cast to char 

    int asInt;

    FILE *fp;

    fp = fopen (txtFile, "w") ; // opening an existing file in r+ mode
   
    if ( fp == NULL ){
        printf ("Could not open file\n");
        return;
    }

    FILE *fpBin;

    fpBin = fopen(binFile, "rb");  // r for read, b for binary

    if ( fpBin == NULL ){
        printf ("Could not open binary file\n");
        return;
    }

    //int newInt;
    char newChar;

    // pass in seed it returns next seed 
    // first seed you pass in is file creation time

    // iterate through each char in the text file
    // while(1){
    //     asInt = fgetc (fp) ; // reading the file
    //     if(asInt==EOF){
    //         break;
    //     }
    //     else {
    //         //newInt = function(asInt);
    //         newChar = (char) asInt;

    //         //&newInt gets address of int in memory and passes that address to fwrite
    //         fwrite(&newChar, sizeof newChar, 1, fpBin);      
    //     }
    // }



    printf("\nClosing the file\n\n") ;
    fclose(fp);
    fclose(fpBin);

    int seed = getSeed(binFile);
    if(seed >= 0 && seed <=60){
        printf("Encryption key seed retrieved succesfully. Seed = %d\n", seed);
    }
    else{
        printf("Seed retrieval error\n");
    }




}

// // must return an int between 0-127
int function(int num){

    // An early computer-based PRNG, suggested by John von Neumann in 1946, 
    // is known as the middle-square method. The algorithm is as follows: 
    // take any number, square it, remove the middle digits of the resulting 
    // number as the "random number", then use that number as the seed for the 
    // next iteration.




    return num-100;
}

// This function runs a bash command to retrieve the creation date of the file specified in the input, 
// temporarily writes the second of the creation time to a file and saves the contents of this file into 
// the C variable number which is the seed of the encrpytion key and is returned by this function
int getSeed(char* fileName){

    //concatenate filename string with rest of command
    const char* tempFile = "testDir/seedTemp.txt";

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
        printf("Can't open file for reading.\n");
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



int functionInverse(int num){
    return num+100;
}


// I'm converting to binary because if I kept everything in ascii I would have to restrain the results of the ciphertext to integers between 0 and 127 which greatly decreases the strength of the encryption


void readTxt(FILE* fp){

    if(fp){

    }

    // // bool debug = true;

    // // read in file name
    // printf("\nPlease specify the document you would like to encrypt:\n");
    // //printf("Example: 'p5docs/*.txt'\n");
    
    // char* fileName = "testDir/gibberish.txt";

    // // first check for EOF then cast to char 

    // int asInt;
    // char asChar;

    // FILE *fp;
    
    // printf( "Opening the file\n" ) ;
    // fp = fopen ( fileName, "r" ) ; // opening an existing file
    // if ( fp == NULL )
    // {
    //     printf ("Could not open file\n");
    //     return;
    // }
    // printf( "File contents:\n" ) ;
    // while(1){
    //     asInt = fgetc (fp) ; // reading the file
    //     if(asInt==EOF){
    //         break;
    //     }
    //     if(asInt>127){
    //         //printf("Non ascii characters present in file, these characters will be replaced with ?\n");
    //     }
    //     asChar = (char) asInt;
    //     printf("%c", asChar);
    // }
   
    // fclose(fp);

}

void readBin(FILE *fp){
    
    if(fp){
        
    }
}





