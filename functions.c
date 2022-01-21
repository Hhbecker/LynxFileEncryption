#include "header.h"  
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <stdbool.h>
#include <assert.h>

void encrypt(void){
    // must ask for file and check file
    
    // read in file name

    char* directory;
    printf("Please specify the directory and document type you would like to search:\n");
    printf("Example: 'p5docs/*.txt'\n");
    
    // create inputs for getline function
    char* line = NULL;
    size_t len = 0;
    size_t lineSize = 0;

    lineSize = getline(&line, &len, stdin); 
    if(lineSize){
        // to avoid error: variable ‘lineSize’ set but not used
    }

    directory = strtok(line, "\n");
    
    // hardcode directory during debugging
    if(debug){
        directory = "p5docs/*.txt";
    }

    glob_t result;
    int retval = glob(directory, 0, NULL, &result);
    if(retval !=0){
        printf("Directory invalid, glob unsuccessful: exiting main\n");
        return -1;
    }

        // 4. confirm searchable files are present in the requested directory
    int numFiles = (int) result.gl_pathc;
    if(result.gl_pathc<1){
        printf("No files in this directory: exiting main\n");
        return -1;
    }

    //printf("num files is: %d\n", numFiles);

    glob_t* globPtr = &result;







}

void decrypt(void){
    // must ask for file and check file

}