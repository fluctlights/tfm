
/************
 * HEADERS *
 *************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <papi.h>

/**************
 * VARIABLES *
 **************/

char *benchmark_name;

/************************************
 *    ARM CORTEX A72 PMU EVENTS     *
 * FROM TECHNICAL REFERENCE MANUAL  *
 * As that doc say we cannot gather *
 *  more than 6 PMU event counters  *
 *     concurrently so we select    *
 *     6 by 6 on each iteration     *
 ************************************/

#ifndef HEADER_H
#define HEADER_H

extern char *arm_cortex_pmu_events[]; //defined in benchmarks_test.c
extern int n_events;

#endif

#ifndef N_REPETITIONS
#define N_REPETITIONS 1000 /* if no macro set we put 1000 loops */
#endif

#ifndef VECTOR_SIZE
#define VECTOR_SIZE 1000 /* if no macro set we put 100 position for the vector */
#endif

/*

***************************************************************
*    Glossary of all events the ARM Cortex A72 PMU gathers    *
* Reference: table 11-24, page 430 Technical Reference Manual *
***************************************************************

char *arm_cortex_pmu_events[] = {

    //CACHE RELATED IMPORTANT EVENTS

    "L1I_CACHE_REFILL",
    "L1I_CACHE_ACCESS",
    "L1D_CACHE_REFILL",
    "L1D_CACHE_ACCESS",
    "L2D_CACHE_ACCESS",
    "L2D_CACHE_REFILL",

    //OTHER CACHE EVENTS
    
    "L1D_TLB_REFILL",
    "L1I_TLB_REFILL",
    "L1D_READ_ACCESS",
    "L1D_WRITE_ACCESS",
    "L1D_READ_REFILL",
    "L1D_WRITE_REFILL",
    "L1D_WB_VICTIM",
    "L1D_WB_CLEAN_COHERENCY",
    "L1D_INVALIDATE",
    "L1D_TLB_READ_REFILL",
    "L1D_TLB_WRITE_REFILL",
    "L1D_CACHE_WB",
    "L2D_CACHE_WB",
    "L2D_READ_ACCESS",
    "L2D_WRITE_ACCESS",
    "L2D_READ_REFILL",
    "L2D_WRITE_REFILL",
    "L2D_WB_VICTIM",
    "L2D_WB_CLEAN_COHERENCY",
    "L2D_INVALIDATE",

    //INSTRUCTION RELATED IMPORTANT EVENTS

    "INST_RETIRED", // completed instructions
    "INST_SPEC_EXEC", // speculative executed instructions
    "INST_SPEC_EXEC_VFP", // floating point instructions
    "INST_SPEC_EXEC_INTEGER_INST", // integer instructions
    "CPU_CYCLES",

    //OTHER INSTRUCTION EVENTS

    "INST_SPEC_EXEC_LOAD",
    "INST_SPEC_EXEC_STORE",
    "INST_SPEC_EXEC_LOAD_STORE",
    "INST_SPEC_EXEC_SIMD",
    "INST_SPEC_EXEC_SOFT_PC",    
    "INST_SPEC_EXEC_LDREX",
    "INST_SPEC_EXEC_STREX_PASS",
    "INST_SPEC_EXEC_STREX_FAIL",

    *****************************
    * CURRENTLY NOT USED EVENTS *
    *****************************

    //BRANCH EVENTS

    "BRANCH_MISPRED"
    "BRANCH_PRED"
    "BRANCH_SPEC_EXEC_IMM_BRANCH",
    "BRANCH_SPEC_EXEC_RET",
    "BRANCH_SPEC_EXEC_IND",

    //EXCEPTION EVENTS

    "EXCEPTION_TAKEN"
    "EXCEPTION_RETURN"
    "EXCEPTION_UNDEF"
    "EXCEPTION_SVC"
    "EXCEPTION_PABORT"
    "EXCEPTION_DABORT"
    "EXCEPTION_IRQ"
    "EXCEPTION_FIQ"
    "EXCEPTION_SMC"
    "EXCEPTION_HVC"
    "EXCEPTION_TRAP_PABORT"
    "EXCEPTION_TRAP_DABORT"
    "EXCEPTION_TRAP_OTHER"
    "EXCEPTION_TRAP_IRQ"
    "EXCEPTION_TRAP_FIQ"

    //BUS ACCESS EVENTS

    "BUS_ACCESS"
    "BUS_CYCLES"
    "BUS_READ_ACCESS"
    "BUS_WRITE_ACCESS"
    "BUS_NORMAL_ACCESS"
    "BUS_NOT_NORMAL_ACCESS"
    "BUS_NORMAL_ACCESS_2"
    "BUS_PERIPH_ACCESS"

    //MEMORY EVENTS

    "DATA_MEM_ACCESS"
    "DATA_MEM_READ_ACCESS"
    "DATA_MEM_WRITE_ACCESS"
    "UNALIGNED_READ_ACCESS"
    "UNALIGNED_WRITE_ACCESS"
    "UNALIGNED_ACCESS"

    //MEMORY COHERENCY EVENTS

    "CID_WRITE_RETIRED"
    "TTBR_WRITE_RETIRED"
    "RC_LD_SPEC"
    "RC_ST_SPEC"
    "BARRIER_SPEC_EXEC_ISB"
    "BARRIER_SPEC_EXEC_DSB"
    "BARRIER_SPEC_EXEC_DMB"
    "LOCAL_MEMORY_ERROR",

    //SOFTWARE EVENTS
    "SW_INCR",
};

*/

/**************
 * FUNCTIONS *
***************/

void show_usage();
void save_counters(const char *arm_pmu_events[], long long values[], int size);