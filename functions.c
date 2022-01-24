#include "header.h"  
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include <assert.h>

void encrypt(void){
    // bool debug = true;

    // read in file name
    printf("\nPlease specify the document you would like to encrypt:\n");
    //printf("Example: 'p5docs/*.txt'\n");
    
    char* fileName = "testDir/gibberish.txt";

    //int asInt;

    FILE *fp ;
    char c ;
    printf( "Opening the file\n" ) ;
    fp = fopen ( fileName, "r" ) ; // opening an existing file
    if ( fp == NULL )
    {
        printf ( "Could not open file\n" ) ;
    }
    printf( "Reading the file\n" ) ;
    while ( 1 )
    {
        c = fgetc ( fp ) ; // reading the file
        if(c == EOF){
            break;
        }
        else{
            printf ( "%c", c ) ;
            //asInt = (int) c;
            //printf ( "%d ", asInt);
        }
    }
    printf("\nClosing the file\n") ;



}

void decrypt(void){
    // must ask for file and check file

}

