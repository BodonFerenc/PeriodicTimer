/**
 * @file byspleep.h
 * @author Ferenc Bodon
 * @date 3 Marc 2020
 * @brief File containing timer based on sleep functionality.
 *
 * This timer calls function clock_nanosleep to sleep till the next trigger time
 */

#include "common.c"

void runtimer(bool (*eventExecutor)(const struct timespec*), 
    unsigned long *now, unsigned long *waittill, 
    unsigned long wait, unsigned long nr) {

    unsigned long runs=0;   
    bool ok = true;
    struct timespec nextSendTime;
    clock_gettime(CLOCK_MONOTONIC,&nextSendTime);

    while (ok && runs < nr) {        
        addNanoSecs(&nextSendTime,wait);
        waittill[runs] = BILLION * nextSendTime.tv_sec + nextSendTime.tv_nsec;
        clock_nanosleep(CLOCK_MONOTONIC, 1, &nextSendTime, NULL);
        clock_gettime(CLOCK_MONOTONIC, &nextSendTime);
        ok = eventExecutor(&nextSendTime);
        now[runs++] = BILLION * nextSendTime.tv_sec + nextSendTime.tv_nsec;        
    } 
}

