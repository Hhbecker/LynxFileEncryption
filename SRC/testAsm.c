/*
A sandbox to test inline x86 assembly within gcc compiled C code.
*/
#include <stdlib.h>
#include <stdio.h>

int main(void){

    printf("\n -- ASM test -- \n\n");

    //asChar = key ^ asChar;

    // int arg1 = 5;
    // int arg2 = 5;
    // int XOR;

    char arg1 = '=';
    char arg2 = 'T';
    char XOR;

    // So called "extended assembly" allows us to specify the input registers, 
    // output registers and a list of clobbered registers.

    // There are two %’s prefixed to the register name, 
    // which helps GCC to distinguish between the operands and registers. operands have a single % as prefix.

    // The order of operands is source(s) first, and destination last. 
    // For example, Intel syntax "mov eax, edx" will look like "mov %edx 
    __asm__ __volatile__ ( "xorb %%bl, %%al;"
        : "=a" (XOR)
        : "a" (arg1), "b" (arg2) );

        printf("%d\n",XOR);

    // If our assembly statement must execute where we put it, 
    // (i.e. must not be moved out of a loop as an optimization), 
    // put the keyword "volatile" or "__volatile__" after "asm" or "__asm__" and before the ()s.

}

