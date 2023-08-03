// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#pragma once
#include "time.h"

/**
 * Contains time information for Pomodoro.
 */
typedef struct TimeKeeper {
    struct timespec startTime;
    struct timespec endTime;
    time_t lastSecondUpdate;
    int valid;
} TimeKeeper;

/**
 * Records starting time.
 */
void TimeKeeper_startTime(TimeKeeper *keeper);

/**
 * Records endTime and sleeps to make the program run in 50fps.
 */
void TimeKeeper_endTimeAndSleep(TimeKeeper *keeper);

int TimeKeeper_hasSecondPassed(TimeKeeper *keeper);

TimeKeeper TimeKeeper_createKeeper(void);

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// TimeKeeper.h is a part of PomodoroTimer is free software: you can
// redistribute it and/or modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// TimeKeeper.h is a part of PomodoroTimer is distributed in the hope that it
// will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
