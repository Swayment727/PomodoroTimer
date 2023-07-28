#include "Arguments.h"


int Arguments_equal(Arguments a, Arguments b){
    return      a.longTime == b.longTime &&
                a.valid == b.valid &&
                a.workTime == b.workTime &&
                a.breakTime == b.breakTime;
}
