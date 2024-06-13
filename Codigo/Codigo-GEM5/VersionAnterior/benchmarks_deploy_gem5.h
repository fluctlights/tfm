
/************
 * HEADERS *
 ************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

/**************
 * VARIABLES *
 **************/

/* Type of benchmark to perform
    EXAMPLES ALREADY TRIED:

    |-----------|-----------|
    | DHRYSTONE |  10000000 |
    |-----------|-----------|
    | WHETSTONE |    200000 |
    |-----------|-----------|
    | CALC_PI   | 100000000 |
    |-----------|-----------|
    | CALC_PRIM |   1000000 |
    |-----------|-----------|

*/

char *benchmark_name;
int benchmark_num_trials;

#ifndef HEADER_H
#define HEADER_H
extern char *resetstats[]; //defined in benchmarks_test_gem5.c
extern char *dumpstats[]; //defined in benchmarks_test_gem5.c
extern char *exitm5[]; //defined in benchmarks_test_gem5.c
#endif

/**************
 * FUNCTIONS *
***************/

void show_usage();
int do_dhrystone();
int do_whetstone();
int do_calc_pi();
int do_calc_prime();