#include <stdio.h>
#include <time.h>

const long BILLION=1000000000l;

int main(int argc, char* argv[])
{
    struct timespec start;    
    struct timespec stop;    
    struct timespec timenow;    
    printf("Executing clock_gettime billion times.\n");
    printf("This can last for a minute... relax ;)\n");

    clock_gettime(CLOCK_MONOTONIC,&start);
    for (unsigned int i=0; i < BILLION; ++i) {
            clock_gettime(CLOCK_MONOTONIC,&timenow);
    }
    clock_gettime(CLOCK_MONOTONIC,&stop);

    printf("The time to execute clock_gettime is less than %f nanoseconds\n", 
        (stop.tv_sec - start.tv_sec) + (double) (stop.tv_nsec - start.tv_nsec) / BILLION);

    return 0;
}