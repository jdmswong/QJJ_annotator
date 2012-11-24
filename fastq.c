//
// written by xxxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "InputData.h"
#include "OutputData.h"
#include "ACGTN.h"
#include "main.h"

/**
  count the number of entries in input file 
  **/
void fastq_count(struct InputData *id, struct OutputData *od) {

   char line[MAX_CHAR_PER_LINE];
	unsigned long n = 0;

   id->inputFile = fopen(id->inputFileName, "r");
	if (id->inputFile == NULL) {
		printf ("\n[%s:%d] - error open file '%s'", __FILE__, __LINE__, id->inputFileName);
		printf ("\n\n");
		exit (1);
	}

	// read input file 
   while ((fgets(line, MAX_CHAR_PER_LINE, id->inputFile) != NULL)) {
		if (id->verbose) 
      	printf ("[%s:%d] - \t%s", __FILE__, __LINE__, line);
		n++;
   }   
   fclose(id->inputFile);

	// FASTQ file is 4 lines per entry
	n = n/4;
	  
	od->n = 1;
	sprintf(od->header[od->n], "#HEADER");
	sprintf(od->data[od->n], "DATA");

	od->n++;
	sprintf(od->header[od->n], "input_file_name");
	// take the prefix if input file is '/dev/stdin
	if (strstr(id->inputFileName,"/dev/stdin")) {
		strcpy(id->inputFileName,id->inputFilePrefix);
		sprintf(od->data[od->n], "%s",id->inputFileName);
	} else {
		sprintf(od->data[od->n], "%s",id->inputFileName);
	}
	
	od->n++;
	sprintf(od->header[od->n], "number_of_reads");
	sprintf(od->data[od->n], "%ld",n);

}



/**
  distribution of A,C,G,and T
  **/
void fastq_acgtnDistributions(struct InputData *id, struct OutputData *od) {

   char line[MAX_CHAR_PER_LINE];
	unsigned long n = 0, N = 0;
	struct ACGTN *acgtn = ACGTN_Init();
	char *ptr;
	int i;
	double ACGTN[NUMBER_OF_BASES+1];

   id->inputFile = fopen(id->inputFileName, "r");
	if (id->inputFile == NULL) {
		printf ("\n[%s:%d] - error open file '%s'", __FILE__, __LINE__, id->inputFileName);
		printf ("\n\n");
		exit (1);
	}

	for (i=0;i <= NUMBER_OF_BASES; i++)
		ACGTN[i] = 0;
			
	// read input file 
   while ((fgets(line, MAX_CHAR_PER_LINE, id->inputFile) != NULL)) {
		n++;
		if ((n==2) || (((n-2)%4)==0))  {

			for (i=0;i <= NUMBER_OF_BASES; i++)
				acgtn->count[i]=0;

			// total number of bases 
			N += (strlen(line)-1);

			ptr = line;
			while (*ptr ) {
				i = ACGTN_getIndex(*ptr);
				acgtn->count[i]++;
				ptr++;
			}
			
			for (i=1;i < NUMBER_OF_BASES; i++) {
				ACGTN[i] += acgtn->count[i]; 
			}

			if (id->verbose){
				// remove new line from line
				line[strlen(line)-1] = '\0';
      		printf ("[%s:%d] -\t%s\tlength\t%ld\ttotal_bases\t%ld\t", __FILE__, __LINE__, line, strlen(line),N);
				ACGTN_printACGNTCount(acgtn);
				printf ("\n");
			}
		}
   }   
   fclose(id->inputFile);
	
	od->n = 1;
	sprintf(od->header[od->n], "#HEADER");
	sprintf(od->data[od->n], "DATA");
	
	od->n++;
	sprintf(od->header[od->n], "input_file_name");
	// take the prefix if input file is '/dev/stdin
	if (strstr(id->inputFileName,"/dev/stdin")) {
		strcpy(id->inputFileName,id->inputFilePrefix);
		sprintf(od->data[od->n], "%s",id->inputFileName);
	} else {
		sprintf(od->data[od->n], "%s",id->inputFileName);
	}


	
	od->n++;
	sprintf(od->header[od->n], "base");
	sprintf(od->data[od->n], "count");

	for (i=1;i < NUMBER_OF_BASES; i++) {
		od->n++;
		sprintf(od->header[od->n], "%c", ACGTN_getBase(i));
		sprintf(od->data[od->n], "%.0f", ACGTN[i]);
	}
	od->n++;
	sprintf(od->header[od->n], ".");
	sprintf(od->data[od->n], ".");
	
	od->n++;
	sprintf(od->header[od->n], "base");
	sprintf(od->data[od->n], "percentage");

	for (i=1;i < NUMBER_OF_BASES; i++) {
		od->n++;
		sprintf(od->header[od->n], "%c", ACGTN_getBase(i));
		sprintf(od->data[od->n], "%.2f", (100.0*ACGTN[i])/(N));
	}
}




/**
  show only reads from the input FASTQ file 
  **/
void fastq_showReads(struct InputData *id, struct OutputData *od) {

   char line[MAX_CHAR_PER_LINE];
	unsigned long n = 0;

   id->inputFile = fopen(id->inputFileName, "r");
	if (id->inputFile == NULL) {
		printf ("\n[%s:%d] - error open file '%s'", __FILE__, __LINE__, id->inputFileName);
		printf ("\n\n");
		exit (1);
	}

	// read input file 
   while ((fgets(line, MAX_CHAR_PER_LINE, id->inputFile) != NULL)) {
		n++;
		if ((n==2) || (((n-2)%4)==0)) 
      	printf ("[%s:%d] - %s", __FILE__, __LINE__, line);
   }   
   fclose(id->inputFile);
}


