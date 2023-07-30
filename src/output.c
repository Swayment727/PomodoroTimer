#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "output.h"

void output_setupPoolingInput(void){
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag &= ~(ECHO | ICANON);
    term.c_cc[VMIN]  = 0; 
    term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

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


