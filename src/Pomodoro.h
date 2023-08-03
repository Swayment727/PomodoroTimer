// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#pragma once

#include <time.h>

#include "Arguments.h"
#include "Menu.h"
#include "TimeKeeper.h"

enum PomodoroState {
    inactive,
    paused,
    quit,
    workTime,
    breakTime,
    longBreakTime
};

/**
 * Stores all related information to Pomodoro timer
 */
typedef struct Pomodoro {
    char formatedStartTime[128];
    time_t lastBreakPointTime;
    struct tm pausedLastTime;
    size_t totalWorkTime;

    char *name;

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
} Pomodoro;

int Pomodoro_start(Arguments *args);

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// Pomodoro.h is a part of PomodoroTimer is free software: you can redistribute
// it and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// Pomodoro.h is a part of PomodoroTimer is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
