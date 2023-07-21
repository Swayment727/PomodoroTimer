#include <string.h> 
#include <stdlib.h>

#include "input.h"

#define CYCLE_FLAG "-c" 
#define WORK_FLAG "-w" 
#define BREAK_FLAG "-b" 
#define LONG_FLAG "-l"

Arguments input_check(int argc, char *argv[]){
    const char *flags[] = {CYCLE_FLAG,WORK_FLAG,BREAK_FLAG, LONG_FLAG};
    Arguments output = {-1,-1,-1,-1,0};
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
    for( size_t inputFlag = 1; inputFlag < argc; inputFlag++ ){
        const char **p_flag = flags;
        for( size_t availableFlag = 0; availableFlag < 4; availableFlag++ ){
            int matchingPrefix = strncmp(*argv,*p_flag,2 ) == 0;
            int parsedNumber = atoi((*p_flag)+2) ;
            int validNumber =  parsedNumber > 0;
            if( matchingPrefix && validNumber ){
                *(((int*)(&output))+availableFlag) = parsedNumber;
                output.valid = 1;
            }
            p_flag += 1;
        }
        if( !output.valid ){
            return output;
        }
        ++argv;
    }
    return output;
}
