// Copyright (C) 2023 Swayment727
// See end of file for the complete copyright information

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Menu.h"

Menu Menu_createMenu(const char *menuTitle) {
    Menu menu = {.lines = NULL, .cnt = 0, .current = 0, .menuTitle = menuTitle};
    return menu;
}

void Menu_addMenu(Menu *menu, const char *description,
                  int (*operation)(void *)) {
    if (menu->current >= menu->cnt) {
        menu->cnt += 5;
        menu->lines = realloc(menu->lines, sizeof(*menu->lines) * menu->cnt);
    }
    MenuItem item = {.description = description, .operation = operation};
    menu->lines[menu->current++] = item;
}

void Menu_display(Menu *menu) {
    printf("%s\n", menu->menuTitle);
    for (size_t i = 0; i < menu->current; i++) {
        printf("%zu. %s\n", i + 1, menu->lines[i].description);
    }
}

void Menu_input(Menu *menu, void *pomodoro) {
    char c;
    read(fileno(stdin), &c, 1);
    if (c > '0' && c < '1' + menu->current) {
        menu->lines[c - '1'].operation(pomodoro);
    }
}

void Menu_cycle(Menu *menu, void *pomodoro) {
    Menu_display(menu);
    Menu_input(menu, pomodoro);
}

void Menu_destroy(Menu *menu) {
    free(menu->lines);
    menu->lines = NULL;
    menu->current = 0;
    menu->cnt = 0;
}

// PomodoroTimer is a TUI pomodoro timer that also tracks worked time.
//
// Menu.c is a part of PomodoroTimer is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// Menu.c is a part of PomodoroTimer is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://www.gnu.org/licenses/.
