#include <stdio.h>
#include <time.h>

struct timespec tstart = {0, 0};
struct timespec tend = {0, 0};

void start_timing() { clock_gettime(CLOCK_MONOTONIC, &tstart); }

void end_timing() {
    clock_gettime(CLOCK_MONOTONIC, &tend);
    double elapsed = ((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) -
                     ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec);
    printf("Time elapsed: %.9f\n", elapsed);
}
