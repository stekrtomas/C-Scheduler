// Based on https://c9x.me/articles/gthreads/code0.html
#include "gthr.h"

// Dummy function to simulate some thread work
void f(void) {
    static int x;
    int i, id;

    id = ++x;
    while (true) {

        printf("F Thread id = %d, val = %d BEGINNING\n", id, ++i);
        uninterruptibleNanoSleep(0, 50000000);
        printf("F Thread id = %d, val = %d END\n", id, ++i);
        uninterruptibleNanoSleep(0, 50000000);
    }
}

// Dummy function to simulate some thread work
void g(void) {
    static int x;
    int i, id;

    id = ++x;
    while (true) {

        printf("G Thread id = %d, val = %d BEGINNING\n", id, ++i);
        uninterruptibleNanoSleep(0, 50000000);
        printf("G Thread id = %d, val = %d END\n", id, ++i);
        uninterruptibleNanoSleep(0, 50000000);

    }
}

void showStats(int signum) {
    printf("\nStats:\n");
    printf("------------------------------\n");
    printf("    ID | Tickets | Priority | State || Runtime | MinRuntime | MaxRuntime || WaitTime | MinWaitTime | MaxWaitTime | WaitCount \n");
    //get parent's pid
    for (int i = 0; i < MaxGThreads; i++)
    {
        printf("%5d |",i);
        printf("%5d |",gttbl[i].prior.tickets);
        printf("%5d |",gttbl[i].prior.priority);
        if(gttbl[i].st == Running){
            printf("Running || ");
        }
        if(gttbl[i].st == Ready){
            printf("Ready   || ");
        }
        if(gttbl[i].st == Unused){
            printf("Unused  || ");
        }
        printf("%10d |",gttbl[i].stats.runTime);
        printf("%10d |",gttbl[i].stats.minRunTime);
        printf("%10d |",gttbl[i].stats.maxRunTime);
        printf("%10d ||",gttbl[i].stats.waitTime);
        printf("%10d |",gttbl[i].stats.maxWaitTime);
        printf("%10d |",gttbl[i].stats.minWaitTime);
        printf("%10d |",gttbl[i].stats.waitCount);
        printf("\n");
    }
    int ppid = getppid();
    //send SIGUSR1 signal to parrent
    kill(ppid, SIGINT);
    exit(0);
}

int main(void) {
    int type = 1; // 1 = Lottery scheduler , 0 = Priority scheduler
    signal(SIGINT, showStats);

    if(type == 1){
        gtinit(LotteryScheduler);// initialize threads, see gthr.c
    }
    else{
        gtinit(PriotiryScheduler);  // initialize threads, see gthr.c
    }

    gtgo(f, 10);        // set f() as first thread
    gtgo(f, 1);        // set f() as first thread
    gtgo(f, 8);        // set f() as first thread
    gtgo(f, 0);        // set f() as first thread
    gtgo(f, 2);        // set f() as second thread
    gtgo(g, 8);        // set g() as third thread
    gtgo(g, 1);        // set g() as third thread
    gtgo(g, 8);        // set g() as third thread
    gtgo(g, 0);        // set g() as third thread
    gtgo(g, 2);        // set g() as third thread
    gtret(1);        // wait until all threads terminate
}
