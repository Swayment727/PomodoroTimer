// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#include "Arguments.h"
#include <stdlib.h>

int Arguments_equal(Arguments a, Arguments b) {
    return a.longTime == b.longTime && a.valid == b.valid &&
           a.workTime == b.workTime && a.breakTime == b.breakTime;
}

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// Arguments.c is a part of PomodoroTimer is free software: you can redistribute
// it and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// Arguments.c is a part of PomodoroTimer is distributed in the hope that it
// will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
