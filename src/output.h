// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#pragma once

#include "Pomodoro.h"

void output_hideCursour(void);

void output_showCursour(void);

/**
 * clears the screen and sets cursour to the left top corner.
 */
void output_clearAndSetCursour(void);

/**
 * Appends a summary of the given time spend working to a file called
 * "timeLog.txt", currently uses the folder in which the exectuable is stored
 * in.
 */
// TODO: Add a way to modify the output folder.
void output_writeToAFile(Pomodoro *p);

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// output.h is a part of PomodoroTimer is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// output.h is a part of PomodoroTimer is distributed in the hope that it will
// be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
