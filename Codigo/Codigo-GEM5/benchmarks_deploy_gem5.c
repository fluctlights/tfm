#include "benchmarks_deploy_gem5.h"

/**************
 * VARIABLES *
***************/

int i,j = 0;
int reps = 0;

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
	reps++;
	return j;
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
			
			if(reps == 5) system(exitm5); // exit condition
			
			break;
		
		default:
			show_usage();
	}
}