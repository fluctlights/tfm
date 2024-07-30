#include "benchmark_menu.h"

extern char *arm_cortex_pmu_events[];
extern int n_events;
int mem_copy();


mem_copy() {
    
    int i;

	/* Variables */
	int vector_original[VECTOR_SIZE];
	int vector_copia[VECTOR_SIZE];
	srand(time(NULL));
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        vector_original[i] = (rand() % 10);
    }

	/* BENCHMARK START */
	#ifdef GEM5
        m5op_addr = 0x10010000;
        map_m5_mem();
		m5_reset_stats(0,0);
    #endif
	
	for (int i = 0; i < VECTOR_SIZE; ++i) vector_copia[i] = vector_original[i];

	/* BENCHMARK END */
	#ifdef GEM5
		m5_dump_stats_addr(0,0); //m5_work_end_addr(0,0);
		unmap_m5_mem();
	#endif

    return 0;
}