// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "output.h"

void output_hideCursour(void) { printf("\033[?25l"); }

void output_showCursour(void) { printf("\033[?25h"); }

void output_clearAndSetCursour(void) {
    printf("\033[2J");
    printf("\033[0;0H");
}

void output_writeToAFile(Pomodoro *p) {
    FILE *file = fopen("timeLog.txt", "a");

    if (!file) {
        perror("Something went wrong while openning the file!");
        return;
    }
    fprintf(file, "Work cycles: %d\nBreakCycles: %d\n", p->workCycles,
            p->breakCycles);
    fprintf(file, "Work time total: %zuh:%zum:%zus\n", p->totalWorkTime / 3600,
            (p->totalWorkTime % 3600) / 60, p->totalWorkTime % 60);

    fclose(file);
}

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// output.c is a part of PomodoroTimer is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// output.c is a part of PomodoroTimer is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
