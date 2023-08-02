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


void output_writeToAFile(Pomodoro *p){
    FILE* file = fopen("timeLog.txt", "a");

    if( !file ){
        perror("Something went wrong while openning the file!");
        return;
    }
    fprintf(file,"Work cycles: %d\nBreakCycles: %d\n",p->workCycles, p->breakCycles);
    fprintf(file,"Work time total: %zuh:%zum:%zus\n", p->totalWorkTime / 3600 ,(p->totalWorkTime % 3600) / 60,p->totalWorkTime % 60);

    fclose(file);
}

