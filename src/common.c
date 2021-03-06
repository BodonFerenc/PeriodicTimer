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
void runtimer(bool (*eventExecutor)(const struct timespec*), unsigned long *now, unsigned long *waittill, 
    unsigned long wait, unsigned long nr);


bool doNothing(const struct timespec* t) {
    // do nothing
    return true;    
}

void writeOutDetail(const char* filename, unsigned long nr, 
    unsigned long *now,unsigned long *waittill) {
    printf("Writing results to file %s\n", filename);  
    FILE *fp = fopen(filename, "w");

    fprintf(fp, "planned,real,latency\n");
    unsigned long sumwait=0;
    for (unsigned long i=0; i<nr; ++i) {
      fprintf(fp, "%lu,%lu,%lu\n", waittill[i], now[i], now[i] - waittill[i]);
      sumwait += now[i] - waittill[i];
    }
    fclose(fp);

    printf("Average wait time latency\t %ld nanosec\n", (long) (sumwait / nr));
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
    printf("Wait time is set to\t\t %lu nanosec\n", WAIT);
    const unsigned int DUR = atoi(argv[2]);            // duration is second

    const unsigned long MAXRUN = DUR * FREQ;
    printf("Nr of expected ticks\t\t %lu\n", MAXRUN); 

    // arrays to store planned and real trigger times   
    unsigned long *now = (unsigned long *) malloc(MAXRUN * sizeof(long));
    unsigned long *waittill = (unsigned long *) malloc(MAXRUN * sizeof(long));

    printf("Starting the timer\n");      
    runtimer(doNothing, now, waittill, WAIT, MAXRUN);    

    const float realdur = (float) (now[MAXRUN-1] - waittill[0]) / BILLION;    
    printf("Real duration was\t\t %f sec\n", realdur);
    printf("Real frequency was\t\t %ld\n", (long) (MAXRUN / realdur));    

    writeOutDetail(argv[3], MAXRUN, now, waittill);

    free(now);
    free(waittill);

    return 0;
}
