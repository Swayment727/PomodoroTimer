// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

// #define DEBUG 1
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Pomodoro.h"
#include "input.h"

int main(int argc, char *argv[]) {
#ifdef DEBUG
    printf("ifdef running\n");
    char *argvLookalike[] = {"SomeFileName", "-w5", "-l15", "-b10"};
    Arguments args = {-1, -1, -1, 1};
    input_check(1, argvLookalike);
    assert(Arguments_equal(input_check(1, argvLookalike), args));
    args = (Arguments){5, 10, 15, 1};
    assert(Arguments_equal(input_check(4, argvLookalike), args));
    argvLookalike[3] = "-w";
    assert(input_check(4, argvLookalike).valid == 0);
    argvLookalike[3] = "-p10";
    assert(input_check(4, argvLookalike).valid == 0);
    argvLookalike[3] = "w10";
    assert(input_check(4, argvLookalike).valid == 0);
    argvLookalike[3] = "w-10";
    assert(input_check(4, argvLookalike).valid == 0);
    argvLookalike[3] = "w0";
    assert(input_check(4, argvLookalike).valid == 0);
    argvLookalike[3] = "b100000000000000000000000000";
    assert(input_check(4, argvLookalike).valid == 0);
#endif /* ifdef DEBUG */

    Arguments parsedArguments = input_check(argc, argv);
    if (!parsedArguments.valid) {
        return EXIT_FAILURE;
    }
    Pomodoro_start(&parsedArguments);
    return EXIT_SUCCESS;
}

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// main.c is a part of PomodoroTimer is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// main.c is a part of PomodoroTimer is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
