#include <time.h>
#include <threads.h>

#include "TimeKeeper.h"



void TimeKeeper_startTime(TimeKeeper * keeper){
    timespec_get(&keeper->startTime,TIME_UTC);
    if( keeper->valid == 0 ){
        keeper->lastSecondUpdate = keeper->startTime.tv_sec;
        keeper->valid = 1;
    }
}

void TimeKeeper_endTimeAndSleep(TimeKeeper * keeper){
    timespec_get(&keeper->endTime,TIME_UTC);
    long timeToBeSlept = keeper->startTime.tv_nsec + 20000000 - keeper->endTime.tv_nsec;

    thrd_sleep(&(struct timespec){  .tv_sec=0,
                                    .tv_nsec= timeToBeSlept < 0 ? 0 : timeToBeSlept  }, NULL); 
}

int TimeKeeper_hasSecondPassed(TimeKeeper * keeper){
    struct timespec currentTime;
    timespec_get(&currentTime, TIME_UTC);
    if(currentTime.tv_sec > keeper->lastSecondUpdate){
        keeper->lastSecondUpdate = currentTime.tv_sec;
        return 1;
    }
    return 0;
}

TimeKeeper TimeKeeper_createKeeper(void){
    TimeKeeper output = {.valid=0};
    return output;
}
