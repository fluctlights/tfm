
#include "benchmarks_deploy_gem5.h"

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
typedef char CapitalLetter;
typedef char String30[31];
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

// extern Enumeration	Func1();
// extern boolean		Func2();
// extern boolean Func3();

int do_dhrystone_benchmark();
int Proc1(REG RecordPtr PtrParIn);
int Proc2(OneToFifty *IntParIO);
int Proc3(RecordPtr	*PtrParOut);
int Proc4();
int Proc5();
int Proc6(REG Enumeration EnumParIn, REG Enumeration *EnumParOut);
int Proc7(OneToFifty IntParI1, OneToFifty ntParI2, OneToFifty *IntParOut);
int Proc8(Array1Dim Array1Par, Array2Dim Array2Par, OneToFifty IntParI1, OneToFifty IntParI2);

Enumeration Func1(CapitalLetter CharPar1, CapitalLetter CharPar2);
boolean Func2(String30 StrParI1, String30 StrParI2);
boolean Func3(REG Enumeration EnumParIn);

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
