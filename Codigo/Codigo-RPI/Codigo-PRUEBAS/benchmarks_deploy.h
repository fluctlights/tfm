
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
#include <linux/time.h>

/**************
 * VARIABLES *
 **************/

char *benchmark_name;
int benchmark_num_trials;


/**************
 * FUNCTIONS *
***************/

void show_usage();
int do_dhrystone();
int do_whetstone();
int do_calc_pi();
int do_calc_prime();