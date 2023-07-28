#define DEBUG 1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "input.h"
#include "Pomodoro.h"


int main(int argc, char *argv[]){
    #ifdef DEBUG
        printf("ifdef running\n");
        char *argvLookalike[] = {"SomeFileName","-w5","-l15","-b10"};
        Arguments args = {-1,-1,-1,1};
        input_check(1,argvLookalike);
        assert( Arguments_equal(input_check(1,argvLookalike),args));
        args = (Arguments){5,10,15,1};
        assert( Arguments_equal(input_check(4,argvLookalike),args));
        argvLookalike[3] = "-w" ;
        assert( input_check(4,argvLookalike).valid == 0 );
        argvLookalike[3] = "-p10";
        assert( input_check(4,argvLookalike).valid == 0 );
        argvLookalike[3] = "w10";
        assert( input_check(4,argvLookalike).valid == 0 );
        argvLookalike[3] = "w-10";
        assert( input_check(4,argvLookalike).valid == 0 );
        argvLookalike[3] = "w0";
        assert( input_check(4,argvLookalike).valid == 0 );
        argvLookalike[3] = "b100000000000000000000000000";
        assert( input_check(4,argvLookalike).valid == 0 );
    #endif /* ifdef DEBUG */


    Arguments parsedArguments = input_check(argc,argv);
    if( !parsedArguments.valid ){
       return EXIT_FAILURE; 
    }
    pomodoro_start(parsedArguments);
    return EXIT_SUCCESS;
}
