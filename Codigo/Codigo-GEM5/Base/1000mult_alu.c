#include "benchmark_menu.h"

extern char *arm_cortex_pmu_events[];
extern int n_events;
int mult_alu();

mult_alu() {
    
    int i;

	// Variables para las operaciones
	int fact = 20;
    unsigned long long factor = 1; //CAMBIAR A FLOAT
    
	/* BENCHMARK START */
	#ifdef GEM5
        m5op_addr = 0x10010000;
        map_m5_mem();
		m5_reset_stats(0,0);
    #endif

    // Calculando el factorial de manera iterativa
    for (i = 1; i <= fact; ++i) {
        factor *= i;
    }
	
	/* BENCHMARK END */
	#ifdef GEM5
		m5_dump_stats_addr(0,0); //m5_work_end_addr(0,0);
		unmap_m5_mem();
	#endif

    return 0;
}