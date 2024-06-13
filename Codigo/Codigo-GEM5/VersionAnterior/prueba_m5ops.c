#include <gem5/m5ops.h>
#include <m5_mmap.h>
#include <stdio.h>

int main()
{
#ifdef GEM5
    m5op_addr = 0xFFFF0000;
    map_m5_mem();
    m5_work_begin_addr(0,0);
#endif

	print("AAAAAAAAAAAAAAAAAAAAAA\n");

#ifdef GEM5
    m5_work_end_addr(0,0);
    unmap_m5_mem();
#endif

}
