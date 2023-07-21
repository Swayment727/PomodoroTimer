#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>

#include "Pomodoro.h"


Pomodoro _pomodoro_create( Arguments args ){
    time_t currentTime = time(NULL);
    //TODO: extract time based logic outside into another struct with it's own "methods"
    Pomodoro output = { .startTime = currentTime,
                        .formatedStartTime = "",  
                        .endTime = localtime(&currentTime),
                        .lastBreakPointTime = currentTime,
                        .totalWorkTime = 0,
                        .state = inactive,
                        .WORK_LENGTH = args.workTime != -1 ? args.workTime : 25, 
                        .BREAK_LENGTH = args.breakTime != -1 ? args.breakTime : 5, 
                        .CYCLES = args.longTime != -1 ? args.longTime : 15, 
                        .LONG_BREAK_LENGTH = 15,
                        .workCycles = 0,
                        .breakCycles = 0};
    strftime(output.formatedStartTime, sizeof(output.formatedStartTime), "%c",localtime(&currentTime));
    if( currentTime == (time_t)(-1) ){
        output.valid = 0;
    }
    return output;
}

void _pomodoro_clear(){
    printf("\033[2J");
    printf("\033[0;0H");
}

void _pomodoro_display( Pomodoro *p ){
    _pomodoro_clear();
    printf("Started at: %s\n",p->formatedStartTime); 
    size_t passedSeconds = difftime(time(NULL), p->lastBreakPointTime);
    if( p->state == workTime ){
        printf("Work time: %zu:%zu/%d:00\n",passedSeconds / 60, passedSeconds % 60, p->WORK_LENGTH );
    }
    else{
        printf("Break time: %zu:%zu/%d:00\n",passedSeconds / 60, passedSeconds % 60, p->BREAK_LENGTH);
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
    if( p->state == workTime ){
        _pomodoro_work(p,passedMinutes);
    }
    else if( p->state == breakTime ){       
        _pomodoro_break(p,passedMinutes,p->BREAK_LENGTH);
    }
    else if ( p->state == longBreakTime ){
       _pomodoro_break(p,passedMinutes,p->LONG_BREAK_LENGTH);
    }
}

int pomodoro_start(Arguments args){
    Pomodoro p = _pomodoro_create(args);
    p.state = workTime;
    if( !args.valid )
        return 1;
    while( 1 ){
        struct timespec startTime;
        timespec_get(&startTime,TIME_UTC);
        
        struct timespec endTime;
        timespec_get(&endTime,TIME_UTC);
        int secondRolledOver = endTime.tv_sec > startTime.tv_sec;
        if( secondRolledOver ){
            _pomodoro_display(&p);
            _pomodoro_update(&p);
        }

        timespec_get(&endTime,TIME_UTC);
        long endNs = endTime.tv_nsec;
        thrd_sleep(&(struct timespec){.tv_sec=0,.tv_nsec=1000000000 - endNs }, NULL); 
        _pomodoro_display(&p);
        _pomodoro_update(&p);
    }  

    return 0;
}


