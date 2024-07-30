#include "benchmark_menu.h"

extern char *arm_cortex_pmu_events[];
extern int n_events;
int mult_fpu();

mult_fpu() {
    
    int i;

	// Variables para las operaciones
    float a_float = 1.5f;
	float b_float = 2.5f;
    float result_float;

	/* BENCHMARK START */
	#ifdef GEM5
        m5op_addr = 0x10010000;
        map_m5_mem();
		m5_reset_stats(0,0);
    #endif
	
    for (i = 0; i < N_REPETITIONS; i++) result_float = result_float + a_float + b_float;
	
	/* BENCHMARK END */
	#ifdef GEM5
		m5_dump_stats_addr(0,0); //m5_work_end_addr(0,0);
		unmap_m5_mem();
	#endif

    return 0;
}