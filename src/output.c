#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "output.h"

void output_hideCursour(void){
    printf("\033[?25l");
}

void output_showCursour(void){
    printf("\033[?25h");
}


void output_clearAndSetCursour(void){
    printf("\033[2J");
    printf("\033[0;0H");
}


