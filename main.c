/******************************************************/
/*  Author: Nicholas Finch                             /
/*  Author: Mikayla Armstrong                          /
/*  Date: 2/18/2016                                    /
/*                                                     /
/* Summary: This is a program that takes in            /
/* a string argument from the terminal.                /
/* This program applies an arbitrary number of         /
/* string processing functions (aka "processors")      /
/* to a string (i.e. an array of characters). Both,    /
/* the array of function pointers and the string are   /
/* passed in as arguments. The function returns an     /
/* array of strings representing the results of the    /
/* application of each of the processors on the        /
/* input string.                                       /
/*                                                     /
/******************************************************/

#define BUF 100
#define ASCIIZ 0
#include <stdio.h>

char* char_double(char* str){                                          // start of our function
    char* dest = (char*)malloc(sizeof(char)*BUF);                      // we malloc out the appropriate size of our destination
    char* temp = dest;                                                 // we then set a temporary pointer such that we don't dereference
    *dest++ = '_';                                                     // we add our underscores
    *dest++ = '_';                                                     // we add our underscores
    while (*str){                                                      // while we haven't hit null in str
        *dest++ = *str;                                                // increment dest, but don't increment str.
        *dest++ = *str++;                                              // this allows us to copy twice the content
    }                                                                  // end while
    *dest++ = '_';                                                     // we add our underscores
    *dest++ = '_';                                                     // we add our underscores
    *dest++ = '\n';                                                    // we add our new line
    *dest++ = ASCIIZ;                                                  // ASCIIZ the last memory space
    return temp;                                                       // return our pointer
}

char* char_flip(char* str){
    char* dest = (char*)malloc(sizeof(char)*BUF);                       // allocates the appropriate space needed
    char* temp = dest;                                                  // set our pointer so we don't dereference
    *dest++ = '_';                                                      // we add our underscores
    *dest++ = '_';                                                      // we add our underscores
    while (*str){                                                       // while loop that says if string exis then continue
        if(*str > 90)                                                   // if it is a captial,
            *dest++ = (*str++)-32;                                      // make it lowercase
        else                                                            // otherwise
            *dest++ = (*str++)+32;                                      // make it a capital instead
    }                                                                   // end while
    *dest++ = '_';                                                      // we add our underscores
    *dest++ = '_';                                                      // we add our underscores
    *dest++ = '\n';                                                     // we add our new line
    *dest++ = ASCIIZ;                                                   // ASCIIZ the last memory space
    return temp;                                                        // return the value that is flipped

}

char* char_shift(char* str){
    char* dest = (char*)malloc(sizeof(char)*BUF);                        // allocates the appropriate space needed
    char* temp = dest;                                                   // set our pointer so we don't dereference
    *dest++ = '_';                                                       // we add our underscores
    *dest++ = '_';                                                       // we add our underscores
    while(*str){                                                         // while the string exists loop
        *dest++ = *str;                                                  // adds a letter
        *dest++ = (*str++)+1;                                            // adds incremented letter and moves str to next pointer
    }                                                                    // end while
    *dest++ = '_';                                                       // we add our underscores
    *dest++ = '_';                                                       // we add our underscores
    *dest++ = '\n';                                                      // we add our new line
    *dest = ASCIIZ;                                                      // ASCIIZ the last memory space
    return temp;                                                         //returns the value that is shifted over
}

char *concat(char *dest, const char *src) {
    while (*dest != ASCIIZ) dest++;                                      // increment the length of dest's pointer to get to the end of the memory
    while (*src != ASCIIZ)                                               // a while loop that checks we haven't reached a null in src
        *dest++ = *src++;                                                // offset by the size of dest we will now copy content from src to dest
    *(dest++) = ASCIIZ;                                                  // increment up one more in memory and add a termination
    return dest;                                                         // return the final result
}


char** string_central(char*(*array_func_ptr[])(char*),char* strings){
    char* dest = (char*)malloc(sizeof(char)*BUF);                        // allocates the appropriate space needed
    while (*dest != ASCIIZ) *dest++ = ASCIIZ;                            // loop through dest and null out all the memory locations throughout
    char* rtnVal = dest;                                                 // set rtnVal to hold pointer position
//    char* val1 = (*(array_func_ptr++))(strings);                       // setting up values to test to see what
//    char* val2 = (*(array_func_ptr++))(strings);                       // type was being returned
//    char* val3 = (*(array_func_ptr++))(strings);                       // the type is char.
    while(*array_func_ptr != NULL){                                      // while the array of functions isn't null loops
        concat(dest, (*(array_func_ptr++))(strings));                    // because the type is a char* i could loop through
//        *(dest++) = (*(array_func_ptr++))(strings);                    // each function in the array and concatenate the entire string
                                                                         // The functions also take care of ASCIIZ and New Line
    }                                                                    // end while
    return rtnVal;                                                       // return the final value
}

int main(int argc, char **argv){
    char* (*foo[])(char*) = {char_double, char_shift, char_flip, NULL};  // make the array of pointers, NULL terminating at the end
    printf(string_central(foo, *(++argv)));                              // call on string_central. string central takes in the function array and the string from argv
    return (0);                                                          // return 0 if we succeed.
}

