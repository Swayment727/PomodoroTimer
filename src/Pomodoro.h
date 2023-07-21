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
    const int WORK_LENGTH;
const int BREAK_LENGTH;
    const int LONG_BREAK_LENGTH;
    const int CYCLES;
    int valid;
}Pomodoro;


int pomodoro_start( Arguments args );

