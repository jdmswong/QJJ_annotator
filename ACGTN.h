
#include <stdio.h>
#include "main.h"

struct ACGTN * ACGTN_Init() ;

#define NUMBER_OF_BASES 6
struct ACGTN {

	// A - 1
	// C - 2
	// G - 3
	// T - 4
	// N - 5
	// . = 6
	double count[NUMBER_OF_BASES+1];
	double AvgQualityPerCycle[MAX_READ_LENGTH+1];

};

char ACGTN_getBase(int index);
char ACGTN_getIndex(char base);
void ACGTN_printACGNTCount(struct ACGTN *acgtn);
