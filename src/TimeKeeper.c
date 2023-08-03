// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#include <threads.h>
#include <time.h>

#include "TimeKeeper.h"

void TimeKeeper_startTime(TimeKeeper *keeper) {
    timespec_get(&keeper->startTime, TIME_UTC);
    if (keeper->valid == 0) {
        keeper->lastSecondUpdate = keeper->startTime.tv_sec;
        keeper->valid = 1;
    }
}

void TimeKeeper_endTimeAndSleep(TimeKeeper *keeper) {
    timespec_get(&keeper->endTime, TIME_UTC);
    long timeToBeSlept =
        keeper->startTime.tv_nsec + 20000000 - keeper->endTime.tv_nsec;

    thrd_sleep(
        &(struct timespec){.tv_sec = 0,
                           .tv_nsec = timeToBeSlept < 0 ? 0 : timeToBeSlept},
        NULL);
}

int TimeKeeper_hasSecondPassed(TimeKeeper *keeper) {
    struct timespec currentTime;
    timespec_get(&currentTime, TIME_UTC);
    if (currentTime.tv_sec > keeper->lastSecondUpdate) {
        keeper->lastSecondUpdate = currentTime.tv_sec;
        return 1;
    }
    return 0;
}

TimeKeeper TimeKeeper_createKeeper(void) {
    TimeKeeper output = {.valid = 0};
    return output;
}

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// TimeKeeper.c is a part of PomodoroTimer is free software: you can
// redistribute it and/or modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// TimeKeeper.c is a part of PomodoroTimer is distributed in the hope that it
// will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
