#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>

#include "Menu.h"
#include "Pomodoro.h"
#include "TimeKeeper.h"
#include "output.h"
#include "input.h"

int _pomodoro_pause(void * pomodoro){
    Pomodoro * p = (Pomodoro *)pomodoro;
    if( p->state != paused ){
        p->lastState = p->state;
        p->state = paused;
        p->pausedLastTime = *localtime(&p->lastBreakPointTime);
    }
    return 1;
}


int _pomodoro_unpause(void * pomodoro){
    Pomodoro * p = (Pomodoro *)pomodoro;
    if( p->state == paused ){
        p->state = p->lastState;
        p->lastBreakPointTime = mktime(&p->pausedLastTime);
    }
    return 1;
}

Pomodoro _pomodoro_create( Arguments args ){
    time_t currentTime = time(NULL);
    Pomodoro output = { .formatedStartTime = "", 
                        .keeper = TimeKeeper_createKeeper(),
                        .menu = Menu_createMenu("Main menu"),
                        .lastBreakPointTime = currentTime,
                        .totalWorkTime = 0,
                        .state = inactive,
                        .WORK_LENGTH = args.workTime == -1 ? 25 : args.workTime, 
                        .BREAK_LENGTH = args.breakTime == -1 ? 5 : args.breakTime, 
                        .LONG_BREAK_LENGTH = args.longTime == -1 ? 15 : args.longTime,
                        .workCycles = 0,
                        .breakCycles = 0};
    //TODO: this will leak, since I'm not calling free, add a function to call it from pomodoro
    Menu_addMenu(&output.menu,"Pause",_pomodoro_pause);
    Menu_addMenu(&output.menu,"Unpause",_pomodoro_unpause);
    strftime(output.formatedStartTime, sizeof(output.formatedStartTime), "%c",localtime(&currentTime));
    if( currentTime == (time_t)(-1) ){
        output.valid = 0;
    }
    return output;
}


void _pomodoro_display( Pomodoro *p ){
    output_clearAndSetCursour();
    printf("Started at: %s\n",p->formatedStartTime); 
    size_t passedSeconds = difftime(time(NULL), p->lastBreakPointTime);
    switch(p->state){
        case( workTime ):
            printf("Work time: %zu:%zu/%d:00\n",passedSeconds / 60, passedSeconds % 60, p->WORK_LENGTH );
            break;
        case( breakTime ):
            printf("Break time: %zu:%zu/%d:00\n",passedSeconds / 60, passedSeconds % 60, p->BREAK_LENGTH);
            break;
        case( longBreakTime ):
            printf("Long break time: %zu:%zu/%d:00\n",passedSeconds / 60, passedSeconds % 60, p->LONG_BREAK_LENGTH);
            break;
        case( paused ):
            printf("Paused\n");
            break;
        default:
            break;
    }
    printf("Work cycles: %d\nBreakCycles: %d\n",p->workCycles, p->breakCycles);
    printf("Work time total: %zu:%zu:%zu\n", p->totalWorkTime / 3600 ,(p->totalWorkTime % 3600) / 60,p->totalWorkTime % 60);
}

void _pomodoro_work( Pomodoro *p, size_t passedMinutes ){
    if( passedMinutes >= p->WORK_LENGTH  ){
        p->workCycles += 1;
        if( p->workCycles == 4 ){
            system("kdialog --msgbox \"Long break Time!\" &");
            p->state = longBreakTime;
        }
        else{
            system("kdialog --msgbox \"Break Time!\" &");
            p->state = breakTime;
        }
        p->lastBreakPointTime = time(NULL);
    }
    else{
        p->totalWorkTime += 1;
    }
}

void _pomodoro_break( Pomodoro *p, size_t passedMinutes, size_t breakLength ){
    if( passedMinutes >= breakLength){
        system("kdialog --msgbox \"Time to work, Zug Zug!\" &");
        p->state = workTime;
        p->lastBreakPointTime = time(NULL);
        p->breakCycles += 1;
    }
}

void _pomodoro_update( Pomodoro *p ){ 
    size_t passedMinutes = (time(NULL) - p->lastBreakPointTime) / 60;
    switch(p->state){
        case(workTime):
            _pomodoro_work(p,passedMinutes);
            break;
        case(breakTime):
            _pomodoro_break(p,passedMinutes,p->BREAK_LENGTH);
            break;
        case(longBreakTime):
           _pomodoro_break(p,passedMinutes,p->LONG_BREAK_LENGTH);
            break;
        case(paused):
            p->pausedLastTime.tm_sec += 1;
            break;
        default:
            break;
    }
}

int pomodoro_start(Arguments args){
    Pomodoro p = _pomodoro_create(args);
    input_setupPoolingInput(); 
    p.state = workTime;
    if( !args.valid )
        return 1;
    while( 1 ){
        TimeKeeper_startTime(&p.keeper);
        _pomodoro_display(&p);
        Menu_cycle(&p.menu,&p);
        TimeKeeper_endTimeAndSleep(&p.keeper);
        if( TimeKeeper_hasSecondPassed(&p.keeper) ){
            _pomodoro_update(&p);
            _pomodoro_display(&p);
        }
    }  

    return 0;
}


