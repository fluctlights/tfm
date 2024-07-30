
/************
 * HEADERS *
 *************/

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
#endif

#ifndef REPETITIONS
#define REPETITIONS 5 /* if no macro set we put 5 benchmark repetitions */
#endif

#ifndef N_REPETITIONS
#define N_REPETITIONS 1000 /* if no macro set we put 1000 loops */
#endif

#ifndef VECTOR_SIZE
#define VECTOR_SIZE 1000 /* if no macro set we put 100 position for the vector */
#endif

/**************
 * VARIABLES *
 **************/

extern char *resetstats; //defined in benchmarks_menu.c
extern char *dumpstats; //defined in benchmarks_menu.c
extern char *exitm5; //defined in benchmarks_menu.c
extern int benchmark_num_trials;
extern char *benchmark_name;

/**************
 * FUNCTIONS *
***************/

void show_usage();
void do_solo();
void do_sumas_alu();
void do_sumas_fpu();
void do_mult_alu();
void do_mult_fpu();
void do_div_alu();
void do_div_fpu();
void do_mem_access();
void do_mem_copy();