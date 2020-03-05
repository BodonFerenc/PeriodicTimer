/**
 * @file bytimecheck.h
 * @author Ferenc Bodon
 * @date 3 Marc 2020
 * @brief File containing timer based on time sampling.
 *
 * This timer constantly asks for the current time and checks if it passed the next trigger time
 */

#include "common.c"

/** returns true if the first time is at or after the second time
*/
static bool inline isafter(const struct timespec* t1, const struct timespec* t2) {
    return t1->tv_sec > t2->tv_sec || 
        (t1->tv_sec == t2->tv_sec && t1->tv_nsec >= t2->tv_nsec);
}


void runtimer(bool (*eventExecutor)(const struct timespec*), unsigned long *now, unsigned long *waittill, 
    unsigned long wait, unsigned long nr) {

    unsigned long runs=0;        
    bool ok = true;
    struct timespec timenow;    

    struct timespec nextSendTime;
    clock_gettime(CLOCK_MONOTONIC,&nextSendTime);

    while (ok && runs < nr) {  
        clock_gettime(CLOCK_MONOTONIC, &timenow);
        if (isafter(&timenow, &nextSendTime)) {
          ok = eventExecutor(&timenow);
          now[runs] = BILLION * timenow.tv_sec + timenow.tv_nsec;
          waittill[runs++] = BILLION * nextSendTime.tv_sec + nextSendTime.tv_nsec;
          addNanoSecs(&nextSendTime, wait);
          }
    } 
}

