/*******************************
 *    DHRYSTONE 1.1 VERSION   *
 * Downloaded from netlib.org *
 * 	 Modificated to use PAPI  *
********************************/

#include "benchmarks_test.h"

/* Compiler dependent options */
#undef	NOENUM			/* Define if compiler has no enum's */
#undef	NOSTRUCTASSIGN		/* Define if compiler can't assign structures */

/* for compatibility with goofed up version */
/*#define GOOF			/* Define if you want the goofed up version */

#ifdef GOOF
char	Version[] = "1.0";
#else
char	Version[] = "1.1";
#endif

#ifdef	NOSTRUCTASSIGN
#define	structassign(d, s)	memcpy(&(d), &(s), sizeof(d))
#else
#define	structassign(d, s)	d = s
#endif

#ifdef	NOENUM
#define	Ident1	1
#define	Ident2	2
#define	Ident3	3
#define	Ident4	4
#define	Ident5	5
typedef int	Enumeration;
#else
typedef enum	{Ident1, Ident2, Ident3, Ident4, Ident5} Enumeration;
#endif

typedef int	OneToThirty;
typedef int	OneToFifty;
typedef char	CapitalLetter;
typedef char	String30[31];
typedef int	Array1Dim[51];
typedef int	Array2Dim[51][51];

struct	Record
{
	struct Record		*PtrComp;
	Enumeration		Discr;
	Enumeration		EnumComp;
	OneToFifty		IntComp;
	String30		StringComp;
};

typedef struct Record 	RecordType;
typedef RecordType *	RecordPtr;
typedef int		boolean;

#define	NULL		0
#define	TRUE		1
#define	FALSE		0

#ifndef REG
#define	REG
#endif

extern Enumeration	Func1();
extern boolean		Func2();

extern char *arm_cortex_pmu_events[];
extern int benchmark_num_trials;
extern int n_events;
int do_dhrystone_benchmark();

/*
 * Package 1
 */
int		IntGlob;
boolean		BoolGlob;
char		Char1Glob;
char		Char2Glob;
Array1Dim	Array1Glob;
Array2Dim	Array2Glob;
RecordPtr	PtrGlb;
RecordPtr	PtrGlbNext;

do_dhrystone_benchmark()
{
	OneToFifty		IntLoc1;
	REG OneToFifty		IntLoc2;
	OneToFifty		IntLoc3;
	REG char		CharLoc;
	REG char		CharIndex;
	Enumeration	 	EnumLoc;
	String30		String1Loc;
	String30		String2Loc;

	register unsigned int	i;

	PtrGlbNext = (RecordPtr) malloc(sizeof(RecordType));
	PtrGlb = (RecordPtr) malloc(sizeof(RecordType));
	PtrGlb->PtrComp = PtrGlbNext;
	PtrGlb->Discr = Ident1;
	PtrGlb->EnumComp = Ident3;
	PtrGlb->IntComp = 40;
	strcpy(PtrGlb->StringComp, "DHRYSTONE PROGRAM, SOME STRING");
#ifndef	GOOF
	strcpy(String1Loc, "DHRYSTONE PROGRAM, 1'ST STRING");	/*GOOF*/
#endif
	Array2Glob[8][7] = 10;	/* Was missing in published program */

	/*****************
	* PAPI CODE ZONE *
	******************/
	
	long LOOPS = benchmark_num_trials;

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

	for (long l = 0; l < LOOPS; ++l)
	{
		Proc5();
		Proc4();
		IntLoc1 = 2;
		IntLoc2 = 3;
		strcpy(String2Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
		EnumLoc = Ident2;
		BoolGlob = ! Func2(String1Loc, String2Loc);
		while (IntLoc1 < IntLoc2)
		{
			IntLoc3 = 5 * IntLoc1 - IntLoc2;
			Proc7(IntLoc1, IntLoc2, &IntLoc3);
			++IntLoc1;
		}
		Proc8(Array1Glob, Array2Glob, IntLoc1, IntLoc3);
		Proc1(PtrGlb);
		for (CharIndex = 'A'; CharIndex <= Char2Glob; ++CharIndex)
			if (EnumLoc == Func1(CharIndex, 'C'))
				Proc6(Ident1, &EnumLoc);
		IntLoc3 = IntLoc2 * IntLoc1;
		IntLoc2 = IntLoc3 / IntLoc1;
		IntLoc2 = 7 * (IntLoc3 - IntLoc2) - IntLoc1;
		Proc2(&IntLoc1);
	}

	/* BENCHMARK END */

	/* Read the counting events in the Event Set */
	retval = PAPI_read(EventSet, values);
	if (retval != PAPI_OK)
		printf("FAILURE:  PAPI_read failed, retval=%d...\n", retval);

	/* Add the counters in the Event Set */
	if (PAPI_accum(EventSet, values) != PAPI_OK)
		exit(1);

	save_counters(arm_cortex_pmu_events, values, LOOPS);

	/* Stop the counting of events in the Event Set */
	if (PAPI_stop(EventSet, values) != PAPI_OK)
		exit(1);

	n_events = 0;
	return 0;
}


Proc1(PtrParIn)
REG RecordPtr	PtrParIn;
{
#define	NextRecord	(*(PtrParIn->PtrComp))

	structassign(NextRecord, *PtrGlb);
	PtrParIn->IntComp = 5;
	NextRecord.IntComp = PtrParIn->IntComp;
	NextRecord.PtrComp = PtrParIn->PtrComp;
	Proc3(NextRecord.PtrComp);
	if (NextRecord.Discr == Ident1)
	{
		NextRecord.IntComp = 6;
		Proc6(PtrParIn->EnumComp, &NextRecord.EnumComp);
		NextRecord.PtrComp = PtrGlb->PtrComp;
		Proc7(NextRecord.IntComp, 10, &NextRecord.IntComp);
	}
	else
		structassign(*PtrParIn, NextRecord);

#undef	NextRecord
}

Proc2(IntParIO)
OneToFifty	*IntParIO;
{
	REG OneToFifty		IntLoc;
	REG Enumeration		EnumLoc;

	IntLoc = *IntParIO + 10;
	for(;;)
	{
		if (Char1Glob == 'A')
		{
			--IntLoc;
			*IntParIO = IntLoc - IntGlob;
			EnumLoc = Ident1;
		}
		if (EnumLoc == Ident1)
			break;
	}
}

Proc3(PtrParOut)
RecordPtr	*PtrParOut;
{
	if (PtrGlb != NULL)
		*PtrParOut = PtrGlb->PtrComp;
	else
		IntGlob = 100;
	Proc7(10, IntGlob, &PtrGlb->IntComp);
}

Proc4()
{
	REG boolean	BoolLoc;

	BoolLoc = Char1Glob == 'A';
	BoolLoc |= BoolGlob;
	Char2Glob = 'B';
}

Proc5()
{
	Char1Glob = 'A';
	BoolGlob = FALSE;
}

extern boolean Func3();

Proc6(EnumParIn, EnumParOut)
REG Enumeration	EnumParIn;
REG Enumeration	*EnumParOut;
{
	*EnumParOut = EnumParIn;
	if (! Func3(EnumParIn) )
		*EnumParOut = Ident4;
	switch (EnumParIn)
	{
	case Ident1:	*EnumParOut = Ident1; break;
	case Ident2:	if (IntGlob > 100) *EnumParOut = Ident1;
			else *EnumParOut = Ident4;
			break;
	case Ident3:	*EnumParOut = Ident2; break;
	case Ident4:	break;
	case Ident5:	*EnumParOut = Ident3;
	}
}

Proc7(IntParI1, IntParI2, IntParOut)
OneToFifty	IntParI1;
OneToFifty	IntParI2;
OneToFifty	*IntParOut;
{
	REG OneToFifty	IntLoc;

	IntLoc = IntParI1 + 2;
	*IntParOut = IntParI2 + IntLoc;
}

Proc8(Array1Par, Array2Par, IntParI1, IntParI2)
Array1Dim	Array1Par;
Array2Dim	Array2Par;
OneToFifty	IntParI1;
OneToFifty	IntParI2;
{
	REG OneToFifty	IntLoc;
	REG OneToFifty	IntIndex;

	IntLoc = IntParI1 + 5;
	Array1Par[IntLoc] = IntParI2;
	Array1Par[IntLoc+1] = Array1Par[IntLoc];
	Array1Par[IntLoc+30] = IntLoc;
	for (IntIndex = IntLoc; IntIndex <= (IntLoc+1); ++IntIndex)
		Array2Par[IntLoc][IntIndex] = IntLoc;
	++Array2Par[IntLoc][IntLoc-1];
	Array2Par[IntLoc+20][IntLoc] = Array1Par[IntLoc];
	IntGlob = 5;
}

Enumeration Func1(CharPar1, CharPar2)
CapitalLetter	CharPar1;
CapitalLetter	CharPar2;
{
	REG CapitalLetter	CharLoc1;
	REG CapitalLetter	CharLoc2;

	CharLoc1 = CharPar1;
	CharLoc2 = CharLoc1;
	if (CharLoc2 != CharPar2)
		return (Ident1);
	else
		return (Ident2);
}

boolean Func2(StrParI1, StrParI2)
String30	StrParI1;
String30	StrParI2;
{
	REG OneToThirty		IntLoc;
	REG CapitalLetter	CharLoc;

	IntLoc = 1;
	while (IntLoc <= 1)
		if (Func1(StrParI1[IntLoc], StrParI2[IntLoc+1]) == Ident1)
		{
			CharLoc = 'A';
			++IntLoc;
		}
	if (CharLoc >= 'W' && CharLoc <= 'Z')
		IntLoc = 7;
	if (CharLoc == 'X')
		return(TRUE);
	else
	{
		if (strcmp(StrParI1, StrParI2) > 0)
		{
			IntLoc += 7;
			return (TRUE);
		}
		else
			return (FALSE);
	}
}

boolean Func3(EnumParIn)
REG Enumeration	EnumParIn;
{
	REG Enumeration	EnumLoc;

	EnumLoc = EnumParIn;
	if (EnumLoc == Ident3) return (TRUE);
	return (FALSE);
}


#ifdef	NOSTRUCTASSIGN
memcpy(d, s, l)
register char	*d;
register char	*s;
register int	l;
{
	while (l--) *d++ = *s++;
}
#endif
/* ---------- */
