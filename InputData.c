
//
// written by xxxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
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



void InputData_parseLine(char line[],
      char values[][MAX_CHAR_PER_COLUMN], int *vindex) {

   char str[MAX_CHAR_PER_COLUMN];
   int j;
   char *data = line;
      
   // store the input in values
   *vindex = 1;
   j = 0;
   while ((*data != '\0') && (*data != '\n')) {

      if ((*data != '\t') ) { //&& (*data != ' ')) {
         str[j] = *data;
         j++;
      } else {
         str[j] = '\0';
         strcpy(values[*vindex], str);
         j = 0;
         (*vindex)++;
      }

      data++;
   }
   // get the last element
   str[j] = '\0';
   strcpy(values[*vindex], str);
}

void InputData_printParsedLine(char values[MAX_NUMBER_OF_COLUMNS][MAX_CHAR_PER_COLUMN], int vindex ) {

   int i;
   for (i = 1; i <= vindex; i++) {
		if (i < vindex)
			printf("%s\t", values[i]);
		else
			printf("%s", values[i]);
   }
	printf ("\n");
}


