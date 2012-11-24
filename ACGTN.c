//
// written by 
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ACGTN.h"
#include "OutputData.h"


struct ACGTN * ACGTN_Init() {

	int i,j;

	struct ACGTN *acgtn = (struct ACGTN *) malloc (1 * sizeof (struct ACGTN));

	for (i = 0; i <= NUMBER_OF_BASES; i++)  {
		acgtn->count[i] = 0;
	}
	for (j = 0; j<= MAX_READ_LENGTH; j++)  {
		acgtn->AvgQualityPerCycle[j] = 0;
	}

	return acgtn;	
}


char ACGTN_getBase(int index) {
	if (index == 1)
		return 'A';
	else if (index == 2)
		return 'C';
	else if (index == 3)
		return 'G';
	else if (index == 4)
		return 'T';
	else if (index == 5)
		return 'N';
	else 
		return '*';
}
char ACGTN_getIndex(char base) {

	if ((base == 'A') || (base == 'a'))
		return 1;
	else if ((base == 'C') || (base == 'c'))
		return 2;
	else if ((base == 'G') || (base == 'g'))
		return 3;
	else if ((base == 'T') || (base == 't'))
		return 4;
	else if ((base == 'N') || (base == 'n'))
		return 5;
	else 
		return 6;
}
void ACGTN_printACGNTCount(struct ACGTN *acgtn) {

	int i;
	for (i = 1; i < NUMBER_OF_BASES; i++) {
		printf ("%.0f%c", acgtn->count[i], ACGTN_getBase(i));
		if (i < (NUMBER_OF_BASES-1))
				printf ("\t");
	}
}

