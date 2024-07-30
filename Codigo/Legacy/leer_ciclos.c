#include <stdint.h>
#include <stdio.h>

static inline uint64_t read_pmccntr(void);

static inline uint64_t read_pmccntr(void)
{
	uint64_t val;
	asm volatile("mrs %0, pmccntr_el0" : "=r"(val));
	return val;
}

int main()
{
	uint64_t val2 = read_pmccntr();
	printf("%llu\n", val2);
	return 0;
}
