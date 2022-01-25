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

    int newInt;
    char newChar;

    while(1){
        asInt = fgetc (fp) ; // reading the file
        if(asInt==EOF){
            break;
        }
        else {
            newInt = function(asInt);
            newChar = (char) newInt; 
        
            // // set the position of the stream one character back, this is done by getting the current 
            // // position using ftell, subtracting one from it and using fseek to set a new position
            // fseek(fp, ftell(fp) - 1, SEEK_SET);

            // ////////////////// STAGING AREA 1 ////////////////////////
            // //fprintf(fp, "%c", newChar);    // print using fprintf as a char
            // //fprintf(fp, "%d", newInt);     // print using fprintf as an int
            // putw(newInt, fp);

            // // print to console
            // printf("%u", newInt);

            // create new binary file and write this int to the binary file 

            fwrite(&newInt, sizeof newInt, 1, fpBin); //&newInt gets address of int in memory and passes that address to fwrite

        }
        else{
            newInt = decrypt(asInt);
            newChar = (char) newInt;
            // set the position of the stream one character back, this is done by getting the current 
            // position using ftell, subtracting one from it and using fseek to set a new position
            fseek(fp, ftell(fp) - 1, SEEK_SET);

            /////////////////// STAGING AREA 2 ///////////////////////
            //fprintf(fp, "%c", newChar);
            //fprintf(fp, "%d", newInt);
            putw(newInt, fp);

            // print to console
            printf("%c", newChar);
        }
    }

    printf("\nClosing the file\n\n") ;
    fclose(fp);
    fclose(fpBin);

}

// // must return an int between 0-127
int function(int num){
    return num-100;
}


int functionInverse(int num){
    return num+100;
}


// I'm converting to binary because if I kept everything in ascii I would have to restrain the results of the ciphertext to integers between 0 and 127 which greatly decreases the strength of the encryption


void readTxt(FILE* fp){
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
    
}





