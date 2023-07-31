#pragma once

#include <time.h>

#include "Arguments.h"
#include "TimeKeeper.h"
#include "Menu.h"

enum PomodoroState {inactive, paused,quit, workTime,breakTime,longBreakTime};

typedef struct Pomodoro{
    char formatedStartTime[128];
    time_t lastBreakPointTime;
    size_t totalWorkTime;

    TimeKeeper keeper;

    Menu menu;

    enum PomodoroState lastState;
    enum PomodoroState state;
    
    int workCycles;
    int breakCycles;
    const unsigned int WORK_LENGTH;
const int BREAK_LENGTH;
    const unsigned int LONG_BREAK_LENGTH;
    int valid;
}Pomodoro;


int pomodoro_start( Arguments args );

