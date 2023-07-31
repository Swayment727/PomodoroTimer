#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Menu.h"

Menu Menu_createMenu(const char * menuTitle){
    Menu menu = {.lines=NULL,.cnt=0,.current=0,.menuTitle=menuTitle};
    return menu;
}

void Menu_addMenu(Menu* menu, const char * description, int(*operation)(void*)){
    if(  menu->current >= menu->cnt ){
        menu->cnt += 5;
        menu->lines = realloc(menu->lines, sizeof(*menu->lines) * menu->cnt);
    }
    MenuItem item = {.description=description, operation=operation};
    menu->lines[menu->current++] = item;
}

void Menu_display(Menu * menu){
    printf("%s\n",menu->menuTitle);
    for( size_t i = 0; i < menu->current; i++ ){
        printf("%zu. %s\n",i+1,menu->lines[i].description);
    }
}


void Menu_input(Menu * menu, void * pomodoro) {
    char c;
    read(fileno(stdin), &c, 1);
    if( c > '0' && c < '1' + menu->current){
        menu->lines[c - '1'].operation(pomodoro);
    }
}



void Menu_cycle(Menu * menu, void * pomodoro){
    Menu_display(menu);
    Menu_input(menu,pomodoro);
}

void Menu_destroy(Menu * menu){
    free(menu->lines);
    menu->lines = NULL;
    menu->current = 0;
    menu->cnt = 0;
}
