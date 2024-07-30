#include "benchmark_menu.h"

/**************
 * VARIABLES *
***************/

int i,j, reps = 0;
bool end = false;

char *resetstats ={
    "/sbin/m5 resetstats"
};

char *dumpstats ={
    "/sbin/m5 dumpstats"
};

char *exitm5 ={
    "/sbin/m5 exit"  
};

int benchmark_num_trials = 0;
char *benchmark_name = "a";

/**************
 * FUNCTIONS *
***************/

void show_usage()
{
	printf("USAGE: ./benchmarks_test -b(enchmark) <D,W,p,P> -s(ize) <integer value>");
	exit(1);
}
void do_solo() 
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = solomain();
	}
	return j;
}

void do_sumas_alu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = sumas_alu();	
	}
}

void do_sumas_fpu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = sumas_fpu();	
	}
}

void do_mult_alu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = mult_alu();	
	}
}

void do_mult_fpu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = mult_fpu();	
	}
}

void do_div_alu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = div_alu();	
	}
}

void do_div_fpu()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = div_fpu();	
	}
}

void do_mem_access()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = mem_access();	
	}
}

void do_mem_copy()
{
	for (i=0; i<REPETITIONS; i++)
	{
		j = mem_copy();	
	}
	
	reps++;

	if (reps == 5) { //cuando llegue a 5 habra que terminar
		end = true;
	}

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

			if(end) system(exitm5); // exit condition

			break;
		
		default:
			show_usage();
	}
}
