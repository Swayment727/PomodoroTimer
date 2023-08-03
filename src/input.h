// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#pragma once
#include "Arguments.h"

/**
 * Parses and validates argv input.
 * @return validated output is placed into an instance of Arguments struct
 * @see Arguments
 */
Arguments input_check(int argc, char *argv[]);

/**
 * Turns off ECHO, ICANON flags and sets VMIN and VTIME to 0.
 */
void input_setupPoolingInput(void);

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// input.h is a part of PomodoroTimer is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// input.h is a part of PomodoroTimer is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
