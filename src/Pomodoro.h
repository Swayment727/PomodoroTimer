#pragma once

#include <time.h>

#include "Arguments.h"

enum PomodoroState {inactive, workTime,breakTime,longBreakTime};

typedef struct Pomodoro{
    time_t startTime;
    char formatedStartTime[128];
    struct tm* endTime;
    time_t lastBreakPointTime;
    size_t totalWorkTime;

    enum PomodoroState state;
    
    int workCycles;
    int breakCycles;
    const unsigned int WORK_LENGTH;
const int BREAK_LENGTH;
    const unsigned int LONG_BREAK_LENGTH;
    int valid;
}Pomodoro;


int pomodoro_start( Arguments args );

