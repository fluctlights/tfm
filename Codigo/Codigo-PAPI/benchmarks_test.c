#include "dhrystone-papi.c"
#include "whetstone-papi.c"
#include "calcular-pi-papi.c"
#include "calcular-primos-papi.c"

#ifndef REPETITIONS
#define REPETITIONS 5 /* if no macro set we put 5 benchmark repetitions */
#endif

int i,j = 0;

extern int benchmark_num_trials;
extern char *benchmark_name;
int n_events;

char *arm_cortex_pmu_events[] = 
{
#ifdef PMU_SET_0
    "L1I_CACHE_REFILL",
    "L1I_CACHE_ACCESS",
    "L1D_CACHE_REFILL",
    "L1D_CACHE_ACCESS",
    "L2D_CACHE_ACCESS",
    "L2D_CACHE_REFILL",
#elif PMU_SET_1
    "L1D_READ_ACCESS",
    "L1D_WRITE_ACCESS",
    "L1D_READ_REFILL",
    "L1D_WRITE_REFILL",
    "L2D_READ_ACCESS",
    "L2D_WRITE_ACCESS",
#elif PMU_SET_2
    "L2D_READ_REFILL",
    "L2D_WRITE_REFILL",
#elif PMU_SET_3
    "INST_RETIRED", // completed instructions
    "INST_SPEC_EXEC", // speculative executed instructions
    "INST_SPEC_EXEC_VFP", // floating point instructions
    "INST_SPEC_EXEC_INTEGER_INST", // integer instructions
    "CPU_CYCLES",
#endif
};

/**************
 * FUNCTIONS *
***************/

void show_usage()
{
	printf("USAGE: ./benchmarks_test -b(enchmark) <D,W,p,P> -s(ize) <integer value>");
	exit(1);
}

int do_dhrystone() 
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = do_dhrystone_benchmark();
	}
	return j;
}

int do_whetstone()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = do_whetstone_benchmark();	
	}
	return j;
}

int do_calc_pi()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = do_gauss_legendre_pi_benchmark();	
	}
	return j;
}

int do_calc_prime()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = do_miller_rabin_primes_benchmark();	
	}
	return j;
}

void save_counters(const char *arm_pmu_events[], long long values[], int size)
{
	bool new_file = true;
	FILE *f;
	int n=0;
	char filename[200];
	sprintf(filename, "/home/pi/benchmarks/Codigo-PAPI/CSV/");
    strcat(filename, benchmark_name);

    // Make the filename title with the events taken
    for (n=0; n<n_events; n++) {
        strcat(filename, "-");
        strcat(filename, arm_pmu_events[n]); // Agrega el nombre del evento al nombre del archivo
        strcat(filename, "-");
    }
    strcat(filename, ".csv");

	f = fopen(filename, "r+");
	if (f != NULL) {
        new_file = false;
		fseek(f, 0, SEEK_END); // Move to the end of file
	}
	
	if(new_file) 
	{
		f = fopen(filename, "w");
		if (f == NULL) {
			perror("Error opening file!");
			exit(1);
		}

		// Creating the index of the new CSV file
		fprintf(f, "%s,", benchmark_name); //benchmark name
		for(n=0; n<n_events; n++)
		{
			if(n==(n_events-1)) //endline
				fprintf(f, "%s\n",arm_pmu_events[n]);
			else
				fprintf(f, "%s,",arm_pmu_events[n]);
		}
	}

	// Filling with values
	fprintf(f, "%d,", size); // benchmark size
	for(n=0; n<n_events; n++)
	{
		if(n==(n_events-1)) //endline
			fprintf(f, "%lld\n", (long long int) values[n]);
		else
			fprintf(f, "%lld,", (long long int) values[n]);
	}

	fclose(f);
}


int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		show_usage();
	}

	switch(argv[2][0])
	{
		case 'D':
			benchmark_name = "DHRYSTONE";
			benchmark_num_trials = atoi(argv[4]);
			do_dhrystone(); //dhrystone benchmark
			break;
		
		case 'W':
			benchmark_name = "WHETSTONE";
			benchmark_num_trials = atoi(argv[4]);
			do_whetstone(); //whetstone benchmark
			break;

		case 'p':
			benchmark_name = "CALC-PI";
			benchmark_num_trials = atoi(argv[4]);
			do_calc_pi(); //pi decimals calculus benchmark
			break;

		case 'P':
			benchmark_name = "CALC-PRIME";
			benchmark_num_trials = atoi(argv[4]);
			do_calc_prime(); //primes calculus benchmark
			break;
		
		default:
			show_usage();
	}
}