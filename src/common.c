#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

const long BILLION=1000000000l;

/**Runs timer
        @param now - array to store the times when timer triggered
        @param waittill - array to store the times when timer should have triggered
        @param wait - nanosecond between each trigger, i.e wait time
        @param nr - number of triggers
        */
void runtimer(unsigned long *now, unsigned long *waittill, 
    unsigned long wait, unsigned long nr);


static void inline addNanoSecs(struct timespec* curTime, int64_t nanosec)
{
    if ((nanosec+curTime->tv_nsec) >= BILLION)
    {
        curTime->tv_sec += (nanosec/BILLION)+1;
        curTime->tv_nsec += nanosec-BILLION;
    }
    else
    {
        curTime->tv_sec += nanosec/BILLION;
        curTime->tv_nsec += nanosec;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        printf("Usage: %s [freq] [dur] [output]\n", argv[0]);
        return 1;
    }

    const unsigned long FREQ = atol(argv[1]);          // frequency
    const unsigned long WAIT = BILLION / FREQ;         // wait time between ticks
    printf("Wait time is set to\t %lu nanosec\n", WAIT);
    const unsigned int DUR = atoi(argv[2]);            // duration is second

    const unsigned long MAXRUN = DUR * FREQ;
    printf("Nr of expected ticks\t %lu\n", MAXRUN);    
    unsigned long *now = malloc(MAXRUN * sizeof(unsigned long));
    unsigned long *waittill = malloc(MAXRUN * sizeof(unsigned long));

    printf("Starting the timer\n");  
    
    runtimer(now, waittill, WAIT, MAXRUN);    

    const float realdur = ((float) waittill[MAXRUN-1] - now[1]) / BILLION;    

    printf("Real duration was\t %f sec\n", realdur);
    printf("Real frequency was\t %ld\n", (long) (MAXRUN / realdur));    

    printf("Writing results to file %s\n", argv[3]);  
    FILE *fp = fopen(argv[3], "w");
    fprintf(fp, "planned,real,latency\n");
    unsigned long sumwait=0;
    for (unsigned long i=0; i<MAXRUN; ++i) {
      fprintf(fp, "%lu,%lu,%lu\n", waittill[i], now[i], now[i] - waittill[i]);
      sumwait += now[i] - waittill[i];
    }
    fclose(fp);

    printf("Wait time offset\t %ld nanosec\n", (long) (sumwait / MAXRUN));

    return 0;
}
