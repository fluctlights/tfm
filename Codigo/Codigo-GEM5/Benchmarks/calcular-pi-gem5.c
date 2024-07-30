#include "calcular-pi-gem5.h"

int do_gauss_legendre_pi_benchmark()
{
    
    double a = 1.0;
    double b = 1.0 / sqrt(2);
    double t = 0.25;
    double p = 1.0;
    double pi;
    int i;
    int LOOP = benchmark_num_trials;
    
    /* BENCHMARK START */
    #ifdef GEM5
        m5op_addr = 0x10010000;
        map_m5_mem();
		m5_reset_stats(0,0);
    #endif

    for (int i = 0; i < benchmark_num_trials; i++) {
        double a_next = (a + b) / 2;
        double b_next = sqrt(a * b);
        double t_next = t - p * pow((a - a_next), 2);
        double p_next = 2 * p;

        a = a_next;
        b = b_next;
        t = t_next;
        p = p_next;
    }

    pi = pow((a + b), 2) / (4 * t);

    /* BENCHMARK END */
	#ifdef GEM5
		m5_dump_stats_addr(0,0); //m5_work_end_addr(0,0);
		unmap_m5_mem();
	#endif

    return 0;
}