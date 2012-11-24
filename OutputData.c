
//
// written by xxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "OutputData.h"


/**
  initialize an output structure
 **/
struct OutputData * OutputData_Init() {
	struct OutputData *od =  (struct OutputData *) malloc (1 * sizeof (struct OutputData));

	od->outputOrientation = OUTPUT_ORIENTATION_VERTICAL;


	return od;
}


void OutputData_print(struct OutputData *od) {
	if (od->outputOrientation == OUTPUT_ORIENTATION_VERTICAL) {
		OutputData_printVertical(od);
	} else 
		OutputData_printHorizontal(od);
}
void OutputData_printHorizontal(struct OutputData *od) {

	int j;

   printf ("\n");
   for (j = 1; j <= od->n; j++) {
		if (strstr(od->header[j],"."))
      	printf ("\t");
		else 
      	printf ("%s\t",od->header[j]);
   }
   printf ("\n");
   for (j = 1; j <= od->n; j++) {
		if (strstr(od->header[j],"."))
      	printf ("\t");
		else 
      	printf ("%s\t",od->data[j]);
   }
   printf ("\n\n");
}

void OutputData_printVertical(struct OutputData *od) {
	int j;
   printf ("\n");
   for (j = 2; j <= od->n; j++) {
		if (strstr(od->header[j],".") && strstr(od->data[j],"."))
      	printf ("\n");
		else 
      	printf ("%s\t%s\n",od->header[j], od->data[j]);
   }
   printf ("\n");
}

void OutputData_addData(struct OutputData *od, int index, char header[], char data[]) {

	sprintf(od->header[index], header);
	sprintf(od->data[index], data);

}
