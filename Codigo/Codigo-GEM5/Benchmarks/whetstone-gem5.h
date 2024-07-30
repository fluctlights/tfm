
#include "benchmarks_deploy_gem5.h"

/* function prototypes */
void POUT(long N, long J, long K, double X1, double X2, double X3, double X4);
void PA(double E[]);
void P0(void);
void P3(double X, double Y, double *Z);
int do_whetstone_benchmark();


#ifdef PRINTOUT
void
POUT(long N, long J, long K, double X1, double X2, double X3, double X4)
{
	printf("%7ld %7ld %7ld %12.4e %12.4e %12.4e %12.4e\n",
						N, J, K, X1, X2, X3, X4);
}
#endif
