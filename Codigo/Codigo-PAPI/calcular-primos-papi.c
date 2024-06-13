
/* BENCHMARKS TEST REQUIRED */
#include "benchmarks_test.h"
extern char *arm_cortex_pmu_events[];
extern int benchmark_num_trials;
extern int n_events;
int do_miller_rabin_primes_benchmark();

// Función para calcular a^b mod m
uint64_t power(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t result = 1;
    a = a % m;
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % m;
        }
        b = b >> 1;
        a = (a * a) % m;
    }
    return result;
}

// Test de primalidad de Miller-Rabin
bool isPrimeMillerRabin(uint64_t n, int k) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    // Encontrar r y d tal que n - 1 = 2^r * d
    uint64_t d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    // Realizar el test de Miller-Rabin k veces
    for (int i = 0; i < k; i++) {
        uint64_t a = 2 + rand() % (n - 4);
        uint64_t x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool prime = false;
        while (d != n - 1) {
            x = (x * x) % n;
            d *= 2;
            if (x == 1) return false;
            if (x == n - 1) {
                prime = true;
                break;
            }
        }
        if (!prime) return false;
    }
    return true;
}

int do_miller_rabin_primes_benchmark() {
    
    int i,count = 0;
    int LOOP = benchmark_num_trials;

    for(i=0; arm_cortex_pmu_events[i]!=NULL; i++)
		n_events++;

	/* Create the Event Set */
	int retval, EventSet = PAPI_NULL;
	long long values[20];

	retval = PAPI_library_init(PAPI_VER_CURRENT);
	if (retval != PAPI_VER_CURRENT) 
	{
		fprintf(stderr, "PAPI library init error!\n");
		exit(1);
	}

	if (PAPI_create_eventset(&EventSet) != PAPI_OK)
	{
   		fprintf(stderr,"Error creating eventset! %s\n", PAPI_strerror(retval));
		exit(1);
	}

	/* Adding the concrete set of events desired */
	for(i=0; i<n_events; i++)
	{
		if (PAPI_add_named_event(EventSet, arm_cortex_pmu_events[i]) != PAPI_OK) {
			fprintf(stderr,"Error adding event! %s\n", arm_cortex_pmu_events[i]);
			exit(1);
		}
	}

	/* Resetting values */
	retval = PAPI_reset(EventSet);
	if (retval != PAPI_OK)
	{
		printf("FAILURE:  PAPI_reset failed, retval=%d...\n", retval);
		exit(1);
	}

	/* Start counting events in the Event Set */
	if (PAPI_start(EventSet) != PAPI_OK) {
		fprintf(stderr,"Cound not start! %s\n", PAPI_strerror(retval));
		exit(1);
	}

    /* BENCHMARK START */

    for (uint64_t num = 2; count < LOOP; num++) {
        if (isPrimeMillerRabin(num, 10)) {
            count++;
        }
    }

    /* BENCHMARK END */

	/* Read the counting events in the Event Set */
	retval = PAPI_read(EventSet, values);
	if (retval != PAPI_OK)
		printf("FAILURE:  PAPI_read failed, retval=%d...\n", retval);

	/* Add the counters in the Event Set */
	if (PAPI_accum(EventSet, values) != PAPI_OK)
		exit(1);

	save_counters(arm_cortex_pmu_events, values, benchmark_num_trials);

	/* Stop the counting of events in the Event Set */
	if (PAPI_stop(EventSet, values) != PAPI_OK)
		exit(1);

	n_events = 0;
    return 0;
}