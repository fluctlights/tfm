
/************
 * HEADERS *
 ************/

//standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// m5ops required
#include <gem5/m5ops.h>
#include <m5_mmap.h>
#define GEM5


#ifndef HEADER_H
#define HEADER_H
extern char *resetstats; //defined in benchmarks_test_gem5.c
extern char *dumpstats; //defined in benchmarks_test_gem5.c
extern char *exitm5; //defined in benchmarks_test_gem5.c
extern int benchmark_num_trials;
extern char *benchmark_name;
#endif

#ifndef REPETITIONS
#define REPETITIONS 5 /* if no macro set we put 5 benchmark repetitions */
#endif

/**************
 * FUNCTIONS *
***************/

void show_usage();
void do_dhrystone();
void do_whetstone();
void do_calc_pi();
void do_calc_prime();