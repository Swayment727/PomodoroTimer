#include <string.h> 
#include <stdlib.h>
#include <stdio.h>

#include "input.h"

#define WORK_FLAG "-w" 
#define BREAK_FLAG "-b" 
#define LONG_FLAG "-l"

Arguments input_check(int argc, char *argv[]){
    const char *flags[] = {WORK_FLAG,BREAK_FLAG, LONG_FLAG};
    Arguments output = {-1,-1,-1,0};
    int tooManyArguments = argc > 5;
    int noArguments = argc == 1;
    if( noArguments ){
        output.valid = 1;
        return output;
    }
    else if( tooManyArguments ){
        return output;
    }
    ++argv;
    for( int inputFlag = 1; inputFlag < argc; inputFlag++ ){
        const char **p_flag = flags;
        int parsedSomething = 0;
        for( size_t availableFlag = 0; availableFlag < 3; availableFlag++ ){
            int matchingPrefix = strncmp(*argv,*p_flag,2 ) == 0;
            int parsedNumber = atoi((*argv)+2) ;
            int validNumber =  parsedNumber > 0;
            if( matchingPrefix && validNumber ){
                *(((int*)(&output))+availableFlag) = parsedNumber;
                output.valid = 1;
                parsedSomething = 1;
                break;
            }
            p_flag += 1;
        }
        output.valid = parsedSomething ? output.valid : 0;
        if( !output.valid ){
            return output;
        }
        ++argv;
    }
    return output;
}


