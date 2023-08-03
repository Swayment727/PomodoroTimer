// Copyright (C) Swayment727
// See end of file for the complete copyright information

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>
#include <unistd.h>

#include "Menu.h"
#include "Pomodoro.h"
#include "TimeKeeper.h"
#include "input.h"
#include "output.h"

int _Pomodoro_pause(void *pomodoro) {
    Pomodoro *p = (Pomodoro *)pomodoro;
    if (p->state != paused) {
        p->lastState = p->state;
        p->state = paused;
        p->pausedLastTime = *localtime(&p->lastBreakPointTime);
    }
    return 1;
}

int _Pomodoro_unpause(void *pomodoro) {
    Pomodoro *p = (Pomodoro *)pomodoro;
    if (p->state == paused) {
        p->state = p->lastState;
        p->lastBreakPointTime = mktime(&p->pausedLastTime);
    }
    return 1;
}

int _Pomodoro_quit(void *pomodoro) {
    Pomodoro *p = (Pomodoro *)pomodoro;
    p->state = quit;
    return 1;
}

Pomodoro _Pomodoro_create(Arguments *args) {
    time_t currentTime = time(NULL);
    Pomodoro output = {
        .formatedStartTime = "",
        .keeper = TimeKeeper_createKeeper(),
        .name = args->name == NULL ? NULL : args->name,
        .menu = Menu_createMenu("Main menu"),
        .lastBreakPointTime = currentTime,
        .totalWorkTime = 0,
        .state = inactive,
        .WORK_LENGTH = args->workTime == -1 ? 25 : args->workTime,
        .BREAK_LENGTH = args->breakTime == -1 ? 5 : args->breakTime,
        .LONG_BREAK_LENGTH = args->longTime == -1 ? 15 : args->longTime,
        .workCycles = 0,
        .breakCycles = 0};
    args->name = NULL;
    Menu_addMenu(&output.menu, "Pause", _Pomodoro_pause);
    Menu_addMenu(&output.menu, "Unpause", _Pomodoro_unpause);
    Menu_addMenu(&output.menu, "Quit", _Pomodoro_quit);
    strftime(output.formatedStartTime, sizeof(output.formatedStartTime), "%c",
             localtime(&currentTime));
    if (currentTime == (time_t)(-1)) {
        output.valid = 0;
    }
    return output;
}

void _Pomodoro_display(Pomodoro *p) {
    output_clearAndSetCursour();

    if (p->name != NULL)
        printf("Activity name: %s\n", p->name);
    printf("Started at: %s\n", p->formatedStartTime);
    size_t passedSeconds = difftime(time(NULL), p->lastBreakPointTime);
    switch (p->state) {
    case (workTime):
        printf("Work time: %zu:%zu/%d:00\n", passedSeconds / 60,
               passedSeconds % 60, p->WORK_LENGTH);
        break;
    case (breakTime):
        printf("Break time: %zu:%zu/%d:00\n", passedSeconds / 60,
               passedSeconds % 60, p->BREAK_LENGTH);
        break;
    case (longBreakTime):
        printf("Long break time: %zu:%zu/%d:00\n", passedSeconds / 60,
               passedSeconds % 60, p->LONG_BREAK_LENGTH);
        break;
    case (paused):
        printf("Paused\n");
        break;
    default:
        break;
    }
    printf("Work cycles: %d\nBreakCycles: %d\n", p->workCycles, p->breakCycles);
    printf("Work time total: %zuh:%zum:%zus\n", p->totalWorkTime / 3600,
           (p->totalWorkTime % 3600) / 60, p->totalWorkTime % 60);
}

void _Pomodoro_work(Pomodoro *p, size_t passedMinutes) {
    if (passedMinutes >= p->WORK_LENGTH) {
        p->workCycles += 1;
        if (p->workCycles == 4) {
            system("kdialog --msgbox \"Long break Time!\" &");
            p->state = longBreakTime;
        } else {
            system("kdialog --msgbox \"Break Time!\" &");
            p->state = breakTime;
        }
        p->lastBreakPointTime = time(NULL);
    } else {
        p->totalWorkTime += 1;
    }
}

void _Pomodoro_break(Pomodoro *p, size_t passedMinutes, size_t breakLength) {
    if (passedMinutes >= breakLength) {
        system("kdialog --msgbox \"Time to work, Zug Zug!\" &");
        p->state = workTime;
        p->lastBreakPointTime = time(NULL);
        p->breakCycles += 1;
    }
}

void _Pomodoro_update(Pomodoro *p) {
    size_t passedMinutes = (time(NULL) - p->lastBreakPointTime) / 60;
    switch (p->state) {
    case (workTime):
        _Pomodoro_work(p, passedMinutes);
        break;
    case (breakTime):
        _Pomodoro_break(p, passedMinutes, p->BREAK_LENGTH);
        break;
    case (longBreakTime):
        _Pomodoro_break(p, passedMinutes, p->LONG_BREAK_LENGTH);
        break;
    case (paused):
        p->pausedLastTime.tm_sec += 1;
        break;
    default:
        break;
    }
}

int Pomodoro_start(Arguments *args) {
    Pomodoro p = _Pomodoro_create(args);
    input_setupPoolingInput();
    p.state = workTime;
    if (!args->valid)
        return 1;
    while (p.state != quit) {
        TimeKeeper_startTime(&p.keeper);
        _Pomodoro_display(&p);
        Menu_cycle(&p.menu, &p);
        TimeKeeper_endTimeAndSleep(&p.keeper);
        if (TimeKeeper_hasSecondPassed(&p.keeper)) {
            _Pomodoro_update(&p);
            _Pomodoro_display(&p);
        }
    }
    Menu_destroy(&p.menu);
    free(p.name);
    output_writeToAFile(&p);
    return 0;
}

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
// Copyright (C) 2023 Swayment727
//
// Pomodoro.c is a part of PomodoroTimer is free software: you can redistribute
// it and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// Pomodoro.c is a part of PomodoroTimer is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
