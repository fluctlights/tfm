#include "benchmark_menu.h"

extern char *arm_cortex_pmu_events[];
extern int n_events;
int mem_access();

mem_access() {
    
    int i;
    
    for(i=0; arm_cortex_pmu_events[i]!=NULL; i++)
		n_events++;

	/* Create the Event Set */
	int retval, EventSet = PAPI_NULL;
	long long values[20];

	/* Variables */
	int vector[VECTOR_SIZE];
	int temp;
	srand(time(NULL));
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        vector[i] = (rand() % 10);
    }

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
	
	for (int i = 0; i < VECTOR_SIZE / 2; ++i) { //Swap de elementos
        temp = vector[i];
        vector[i] = vector[VECTOR_SIZE - 1 - i];
        vector[VECTOR_SIZE - 1 - i] = temp;
    }
	
	/* BENCHMARK END */


    /* Read the counting events in the Event Set */
	retval = PAPI_read(EventSet, values);
	if (retval != PAPI_OK)
		printf("FAILURE:  PAPI_read failed, retval=%d...\n", retval);

	/* Add the counters in the Event Set */
	if (PAPI_accum(EventSet, values) != PAPI_OK)
		exit(1);

	save_counters(arm_cortex_pmu_events, values, N_REPETITIONS);

	/* Stop the counting of events in the Event Set */
	if (PAPI_stop(EventSet, values) != PAPI_OK)
		exit(1);

	n_events = 0;
    return 0;
}