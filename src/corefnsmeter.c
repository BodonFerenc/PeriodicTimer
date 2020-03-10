#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const long BILLION=1000000000l;
const int MAGICNR = 26 * 26 * 26 * 26;

int main(int argc, char* argv[])
{
    struct timespec start;    
    struct timespec stop;    
    struct timespec timenow;    
    printf("Executing clock_gettime billion times.\n");
    printf("This can last for a minute... relax ;)\n");

    unsigned int i;
    clock_gettime(CLOCK_MONOTONIC,&start);
    for (i=0; i < BILLION; ++i) {
            clock_gettime(CLOCK_MONOTONIC,&timenow);
    }
    clock_gettime(CLOCK_MONOTONIC,&stop);

    printf("The time to execute clock_gettime, counter increment (++) and a comparison (<) is less than %f nanoseconds\n", 
        (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec) / BILLION);

    int dontcare;
    clock_gettime(CLOCK_MONOTONIC,&start);
    for (i=0; i < BILLION; ++i) {
            dontcare = rand() % MAGICNR;
    }
    clock_gettime(CLOCK_MONOTONIC,&stop);

    printf("The time to execute a random number generation, calculating modulo, incrementing a counter and doing a comparison (<) is less than %f nanoseconds\n", 
        (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec) / BILLION);        

    return dontcare;
}