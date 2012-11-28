//
// written by xxxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"


struct InputData {

	// input mode 
	int mode;
	// input file 
	char inputFileName[1024];
	FILE *inputFile;

	char inputFilePrefix[1024];

	// output file 
	char outputFileName[1024];

	// 
	int verbose ;


};

struct InputData * InputData_Init();
void InputData_printUserInputs(struct InputData *id);
void InputData_parseLine(char line[], char values[][MAX_CHAR_PER_COLUMN], int *vindex) ;
void InputData_printParsedLine(char values[MAX_NUMBER_OF_COLUMNS][MAX_CHAR_PER_COLUMN], int vindex );

