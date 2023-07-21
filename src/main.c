#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "Pomodoro.h"


int main(int argc, char *argv[]){
    Arguments parsedArguments = input_check(argc,argv);
    if( !parsedArguments.valid ){
       return EXIT_FAILURE; 
    }
    pomodoro_start(parsedArguments);
    return EXIT_SUCCESS;
}
