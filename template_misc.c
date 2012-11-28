#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "InputData.h"
#include "OutputData.h"

#include "vcf.h"
#include "main.h"

#define MODE_XXX 1

/**
  XXX usage 
  **/
void XXX_misc_Usage(int argc, char *argv[], struct InputData *id) {
	
	printf("%s", AUTHORS);
	printf("\nUtils for processing XXX files .");
	printf( "\n\n\t%s XXX misc [ -m mode ]  ",
			argv[0]);
	printf("\n");
	
	if ((id->mode == MODE_XXX) || (id->mode == 0))  {
		printf("\n\t-m %d\tXXX",MODE_XXX);
		if ((id->mode == MODE_XXX) )  {
			printf("\n\t\t-i FILE\tinput file.");
		}
	}

	if (id->mode > 0) {
		printf("\n\t\t-H\tprints outputs in horizontal format.  Default, outputs are printed in vertical format.");
		printf("\n\t\t-v\tverbose mode ( for debugging )");
	}

	printf("\n\n");
}


/**
	XXX main
**/
void XXX_misc(int argc, char *argv[]) {
	char c;
	struct InputData *id = InputData_Init();
	struct OutputData *od = OutputData_Init();

	while ((c = getopt(argc, argv, "m:i:p:vH")) != -1) {
		switch (c) {
		case 'm':
			id->mode = atoi(optarg);
			break;
		case 'p':
			strcpy(id->inputFilePrefix, optarg);
			break;
		case 'i':
			strcpy(id->inputFileName, optarg);
			break;
		case 'H':
			od->outputOrientation = OUTPUT_ORIENTATION_HORIZONTAL;
			break;
		case 'v':
			id->verbose = 1;
			break;
		default:
			//abort();
			printf("\n\nunknown arguments %s ", optarg);
			XXX_misc_Usage(argc, argv, id);
		}
	}
	if (id->mode == 0) {
		XXX_misc_Usage(argc,argv,id);
		exit(1);
	}

	if (id->verbose)
		InputData_printUserInputs(id);


	if (id->mode == MODE_FASTQ_COUNT_ENTRY) {
		if (strlen(id->inputFileName)==0)  {
			xxx_misc_Usage(argc,argv,id);
			printf ("\tMissing input file.  Please see usage above!\n\n");
			exit(1);
		}
		if ((id->mode == MODE_FASTQ_COUNT_ENTRY)) {
			xxx_count(id, od);
			OutputData_print(od);
		}
	}
}


