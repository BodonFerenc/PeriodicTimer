/**
 * @file bytimecheck.h
 * @author Ferenc Bodon
 * @date 3 Marc 2020
 * @brief File containing timer based on time sampling.
 *
 * This timer constantly asks for the current time and checks if it passed the next trigger time
 */

#include "common.c"
#include <math.h>

/** returns true if the first time is at or after the second time
*/
static bool inline isafter(const struct timespec* t1, const struct timespec* t2) {
    return t1->tv_sec > t2->tv_sec || 
        (t1->tv_sec == t2->tv_sec && t1->tv_nsec >= t2->tv_nsec);
}

static void inline setNextTriggerTime(struct timespec* const input, struct timespec* nextTriggerTime, long nanosec);

static void inline setNextTriggerTimeJumpForward(struct timespec* const input, struct timespec* nextTriggerTime, long nanosec) {
    nextTriggerTime->tv_nsec = input->tv_nsec + nanosec - input->tv_nsec % nanosec;

    if (nextTriggerTime->tv_nsec >= BILLION)
    {
        nextTriggerTime->tv_sec = input->tv_sec + 1;
        nextTriggerTime->tv_nsec -= BILLION;        
    } else
    {
        nextTriggerTime->tv_sec = input->tv_sec;
    }
}

static void inline setNextTriggerTimeStrict(struct timespec* const input, struct timespec* nextTriggerTime, long nanosec) {
    // we ignore current time
    nextTriggerTime->tv_nsec += nanosec; 
    if (nextTriggerTime->tv_nsec >= BILLION)
    {
        ++(nextTriggerTime->tv_sec);
        nextTriggerTime->tv_nsec -= BILLION;
    } 
}

void runtimer(bool (*eventExecutor)(const struct timespec*), unsigned long *now, unsigned long *waittill, 
    unsigned long wait, unsigned long nr) {

    unsigned long runs=0;        
    bool ok = true;
    struct timespec nextSendTime;
    clock_gettime(CLOCK_MONOTONIC,&nextSendTime);

    struct timespec timenow;    
    clock_gettime(CLOCK_MONOTONIC,&timenow);

    setNextTriggerTime(&timenow, &nextSendTime, wait);

    while (ok && runs < nr) {  
        clock_gettime(CLOCK_MONOTONIC, &timenow);
        if (isafter(&timenow, &nextSendTime)) {
          ok = eventExecutor(&timenow);
          now[runs] = BILLION * timenow.tv_sec + timenow.tv_nsec;
          waittill[runs++] = BILLION * nextSendTime.tv_sec + nextSendTime.tv_nsec;
          setNextTriggerTime(&timenow, &nextSendTime, wait);
          }
    } 
}

