//
// written by xxxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
