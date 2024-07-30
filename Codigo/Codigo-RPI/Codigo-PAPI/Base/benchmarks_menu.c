#include "solo_main.c"
#include "1000sumas_alu.c"
#include "1000sumas_fpu.c"
#include "1000mult_alu.c"
#include "1000mult_fpu.c"
#include "1000div_alu.c"
#include "1000div_fpu.c"
#include "acceso_vector.c"
#include "copia_vector.c"


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
	printf("USAGE: ./benchmarks -b(enchmark) <1..9>");
	exit(1);
}

int do_solo() 
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = solomain();
	}
	return j;
}

int do_sumas_alu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = sumas_alu();	
	}
	return j;
}

int do_sumas_fpu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = sumas_fpu();	
	}
	return j;
}

int do_mult_alu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = mult_alu();	
	}
	return j;
}

int do_mult_fpu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = mult_fpu();	
	}
	return j;
}

int do_div_alu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = div_alu();	
	}
	return j;
}

int do_div_fpu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = div_fpu();	
	}
	return j;
}

int do_mem_access()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = mem_access();	
	}
	return j;
}

int do_mem_copy()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = mem_copy();	
	}
	return j;
}

void save_counters(const char *arm_pmu_events[], long long values[], int size)
{
	bool new_file = true;
	FILE *f;
	int n=0;
	char filename[200];
	sprintf(filename, "/home/pi/benchmarks/Codigo-PAPI/Base/CSV/");
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
	if(argc != 3)
	{
		show_usage();
	}

	switch(argv[2][0])
	{
		case '1':
			benchmark_name = "SOLOMAIN";
			do_solo();
			break;
		
		case '2':
			benchmark_name = "SUMAS-ALU";
			do_sumas_alu();
			break;

		case '3':
			benchmark_name = "SUMAS-FPU";
			do_sumas_fpu();
			break;

		case '4':
			benchmark_name = "MULT-ALU";
			do_mult_alu();
			break;

		case '5':
			benchmark_name = "MULT-FPU";
			do_mult_fpu();
			break;

		case '6':
			benchmark_name = "DIV-ALU";
			do_div_alu();
			break;

		case '7':
			benchmark_name = "DIV-FPU";
			do_div_fpu();
			break;

		case '8':
			benchmark_name = "MEM-ACCESS";
			do_mem_access();
			break;

		case '9':
			benchmark_name = "MEM-COPY";
			do_mem_copy();
			break;
		
		default:
			show_usage();
	}
}