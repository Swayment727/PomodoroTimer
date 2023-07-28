#pragma once

typedef struct Arguments{
    int workTime;
    int breakTime;
    int longTime;
    int valid;
}Arguments;

int Arguments_equal ( Arguments a, Arguments b );


