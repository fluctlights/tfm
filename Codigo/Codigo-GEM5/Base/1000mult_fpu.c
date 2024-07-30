#include "benchmark_menu.h"

extern char *arm_cortex_pmu_events[];
extern int n_events;
int mult_fpu();

mult_fpu() {
    
    int i;

	// Variables para las operaciones
    float num_float = 20.5f; //ejemplo
    float factorial_approx;

	/* BENCHMARK START */
	#ifdef GEM5
        m5op_addr = 0x10010000;
        map_m5_mem();
		m5_reset_stats(0,0);
    #endif
	
    factorial_approx = tgammaf(num_float + 1.0f); // Calcula factorial
	
	/* BENCHMARK END */
	#ifdef GEM5
		m5_dump_stats_addr(0,0); //m5_work_end_addr(0,0);
		unmap_m5_mem();
	#endif

    return 0;
}