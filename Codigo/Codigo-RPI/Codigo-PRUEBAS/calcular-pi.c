/* BENCHMARKS TEST REQUIRED */
#include "benchmarks_deploy.h"

extern char *arm_cortex_pmu_events[];
extern int benchmark_num_trials;
extern int n_events;
int do_gauss_legendre_pi_benchmark();

/*
* Declared time variables
*/
struct timespec start;
struct timespec end;
long seconds, nanoseconds;
double elapsed;

do_gauss_legendre_pi_benchmark()
{
    
    double a = 1.0;
    double b = 1.0 / sqrt(2);
    double t = 0.25;
    double p = 1.0;
    double pi;
    int i;
    int LOOP = benchmark_num_trials;
    
    /* BENCHMARK START */

    // Tiempo inicial
    clock_gettime(CLOCK_MONOTONIC, &start);
    
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
    
    // Obtener el tiempo final
    clock_gettime(CLOCK_MONOTONIC, &end);

	// Calcular el tiempo transcurrido
    seconds = end.tv_sec - start.tv_sec;
    nanoseconds = end.tv_nsec - start.tv_nsec;

    // Ajustar si los nanosegundos del final son menores que los del inicio
    if (nanoseconds < 0) {
        seconds--;
        nanoseconds += 1000000000;
    }

    elapsed = seconds + nanoseconds * 1e-9;

    printf("Tiempo transcurrido: %.9f segundos.\n", elapsed);


    return 0;
}