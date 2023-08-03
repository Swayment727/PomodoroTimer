// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>

#include "input.h"

#define WORK_FLAG "-w"
#define BREAK_FLAG "-b"
#define LONG_FLAG "-l"
#define NAME_FLAG "-n"

Arguments input_check(int argc, char *argv[]) {
    const char *flags[] = {WORK_FLAG, BREAK_FLAG, LONG_FLAG, NAME_FLAG};
    Arguments output = {-1, -1, -1, NULL, 0};
    int tooManyArguments = argc > 5;
    int noArguments = argc == 1;
    if (noArguments) {
        output.valid = 1;
        return output;
    } else if (tooManyArguments) {
        return output;
    }
    ++argv;
    for (int inputFlag = 1; inputFlag < argc; inputFlag++) {
        const char **p_flag = flags;
        int parsedSomething = 0;
        for (size_t availableFlag = 0; availableFlag < sizeof(flags);
             availableFlag++) {
            int matchingPrefix = strncmp(*argv, *p_flag, 2) == 0;
            if (matchingPrefix && strncmp(*p_flag, NAME_FLAG, 2) == 0) {
                output.name =
                    (char *)malloc(sizeof(*output.name) * strlen((*argv) + 2));
                strcpy(output.name, *(argv) + 2);
                output.valid = 1;
                parsedSomething = 1;
                break;
            }
            int parsedNumber = atoi((*argv) + 2);
            int validNumber = parsedNumber > 0;
            if (matchingPrefix && validNumber) {
                *(((int *)(&output)) + availableFlag) = parsedNumber;
                output.valid = 1;
                parsedSomething = 1;
                break;
            }
            p_flag += 1;
        }
        output.valid = parsedSomething ? output.valid : 0;
        if (!output.valid) {
            return output;
        }
        ++argv;
    }
    return output;
}

void input_setupPoolingInput(void) {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    term.c_lflag &= ~(ECHO | ICANON);
    term.c_cc[VMIN] = 0;
    term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// input.c is a part of PomodoroTimer is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// input.c is a part of PomodoroTimer is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
