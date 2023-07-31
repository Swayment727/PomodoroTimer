#pragma once

#include <stdio.h>



typedef struct MenuItem{
    const char * description;
    int(*operation)(void *);
}MenuItem;

typedef struct Menu{
    const char * menuTitle;
    size_t cnt;
    size_t current;
    MenuItem * lines;
}Menu;

void Menu_cycle(Menu * menu, void * pomodoro);

void Menu_display(Menu * menu);

void Menu_addMenu(Menu* menu, const char * description, int(*operation)(void*));

Menu Menu_createMenu(const char * menuTitle);

void Menu_input(Menu * menu, void * pomodoro);

void Menu_destroy(Menu * menu);
