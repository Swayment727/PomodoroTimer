#pragma once
#include "time.h"



typedef struct TimeKeeper{
    struct timespec startTime;
    struct timespec endTime;
    time_t lastSecondUpdate;
    int valid;
}TimeKeeper;

void TimeKeeper_startTime(TimeKeeper * keeper);

void TimeKeeper_endTimeAndSleep(TimeKeeper * keeper);

int TimeKeeper_hasSecondPassed(TimeKeeper * keeper);

TimeKeeper TimeKeeper_createKeeper(void);


