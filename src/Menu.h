// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#pragma once

#include <stdio.h>

/**
 * Contains a single menu entry.
 */
typedef struct MenuItem {
    const char *description;
    int (*operation)(void *);
} MenuItem;

/**
 * Whole menu comprising off MenuItem instances.
 * @see MenuItem
 */
typedef struct Menu {
    const char *menuTitle;
    size_t cnt;
    size_t current;
    MenuItem *lines;
} Menu;

/**
 * Checks input and display menu.
 * @param menu Menu to be displayed.
 * @param pomodoro the current pomodoro timer.
 */
void Menu_cycle(Menu *menu, void *pomodoro);

void Menu_display(Menu *menu);

void Menu_addMenu(Menu *menu, const char *description,
                  int (*operation)(void *));

Menu Menu_createMenu(const char *menuTitle);

/**
 * Checks for input and launches the accompanying command if the given input is
 * correct.
 * @param menu Current menu that is being used
 * @param pomodoro Pomodoro instance that is again currently used.
 */
void Menu_input(Menu *menu, void *pomodoro);

void Menu_destroy(Menu *menu);

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// Menu.h is a part of PomodoroTimer is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// Menu.h is a part of PomodoroTimer is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
