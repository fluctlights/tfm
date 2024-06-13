/* BENCHMARKS TEST REQUIRED */
#include "benchmarks_test.h"
extern char *arm_cortex_pmu_events[];
extern int benchmark_num_trials;
extern int n_events;
int do_gauss_legendre_pi_benchmark();

do_gauss_legendre_pi_benchmark()
{
    
    double a = 1.0;
    double b = 1.0 / sqrt(2);
    double t = 0.25;
    double p = 1.0;
    double pi;
    int i;
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

    /* Read the counting events in the Event Set */
	retval = PAPI_read(EventSet, values);
	if (retval != PAPI_OK)
		printf("FAILURE:  PAPI_read failed, retval=%d...\n", retval);

	/* Add the counters in the Event Set */
	if (PAPI_accum(EventSet, values) != PAPI_OK)
		exit(1);

	save_counters(arm_cortex_pmu_events, values, LOOP);

	/* Stop the counting of events in the Event Set */
	if (PAPI_stop(EventSet, values) != PAPI_OK)
		exit(1);

	n_events = 0;
    return 0;
}