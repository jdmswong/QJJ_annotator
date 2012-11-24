
//
// written by xxxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "InputData.h"


/**
  initialize an input structure
 **/
struct InputData * InputData_Init() {
	struct InputData *id =  (struct InputData *) malloc (1 * sizeof (struct InputData));

	id->mode = 0;
	strcpy(id->inputFileName, "");
	strcpy(id->outputFileName, "");

	id->verbose = 0;

	return id;
}

/**
  prints what the user input 
  **/
void InputData_printUserInputs(struct InputData *id) {

	printf ("\n\n");
	printf ("\n==================================");
	printf ("\n[%s:%d] DEBUG", __FILE__, __LINE__ );
	printf ("\nmode: '%d' ", id->mode);
	printf ("\ninput file name: '%s' ", id->inputFileName );
	printf ("\n\n");

}
