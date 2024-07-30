#include "benchmark_menu.h"

extern char *arm_cortex_pmu_events[];
extern int n_events;
int div_alu();

div_alu() {
    
    int i;

	// Variables para las operaciones
    double result = 1.0;

	/* BENCHMARK START */
	#ifdef GEM5
        m5op_addr = 0x10010000;
        map_m5_mem();
		m5_reset_stats(0,0);
    #endif
	
	for (i = 0; i < N_REPETITIONS; i++) result /= i;
	
	/* BENCHMARK END */
	#ifdef GEM5
		m5_dump_stats_addr(0,0); //m5_work_end_addr(0,0);
		unmap_m5_mem();
	#endif

    return 0;
}