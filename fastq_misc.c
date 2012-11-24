#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "InputData.h"
#include "OutputData.h"

#include "fastq.h"
#include "main.h"

#define MODE_FASTQ_COUNT_ENTRY 1
#define MODE_FASTQ_ACGTN_DISTRIBUTION 2
#define MODE_FASTQ_SHOW_READS 5

/**
  fastq usage 
  **/
void fastq_misc_Usage(int argc, char *argv[], struct InputData *id) {
	
	printf("%s", AUTHORS);
	printf("\nUtils for processing FASTQ files .");
	printf( "\n\n\t%s fastq misc [ -m mode ]  ",
			argv[0]);
	printf("\n");
	
	if ((id->mode == MODE_FASTQ_COUNT_ENTRY) || (id->mode == 0))  {
		printf("\n\t-m %d\tcount number of entries",MODE_FASTQ_COUNT_ENTRY);
		if ((id->mode == MODE_FASTQ_COUNT_ENTRY) )  {
			printf("\n\t\t-i FILE\tinput FASTQ file.");
		}
	}
	if ((id->mode == MODE_FASTQ_ACGTN_DISTRIBUTION) || (id->mode == 0))  {
		printf("\n\t-m %d\tA,C,G,and T distributions of reads", MODE_FASTQ_ACGTN_DISTRIBUTION);
		if ((id->mode == MODE_FASTQ_ACGTN_DISTRIBUTION) )  {
			printf("\n\t\t-i FILE\tinput FASTQ file.");
		}
	}
	if ((id->mode == MODE_FASTQ_SHOW_READS) || (id->mode == 0))  {
		printf("\n\t-m %d\tshow reads",MODE_FASTQ_SHOW_READS);
		if ((id->mode == MODE_FASTQ_SHOW_READS) )  {
			printf("\n\t\t-i FILE\tinput FASTQ file.");
		}
	}

	if (id->mode > 0) {
		printf("\n\t\t-H\tprints outputs in horizontal format.  Default, outputs are printed in vertical format.");
		printf("\n\t\t-v\tverbose mode ( for debugging )");
	}

	printf("\n\n");
}


/**
  fastq main 
  **/

void fastq_misc(int argc, char *argv[]) {

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
			fastq_misc_Usage(argc, argv, id);
		}
	}
	if (id->mode == 0) {
		fastq_misc_Usage(argc,argv,id);
		exit(1);
	}

	if (id->verbose)
		InputData_printUserInputs(id);


	if ((id->mode == MODE_FASTQ_COUNT_ENTRY)
		 || (id->mode == MODE_FASTQ_SHOW_READS)
		 || (id->mode == MODE_FASTQ_ACGTN_DISTRIBUTION)
			) {
		if (strlen(id->inputFileName)==0)  {
			fastq_misc_Usage(argc,argv,id);
			printf ("\tMissing input file.  Please see usage above!\n\n");
			exit(1);
		} else if (strstr(id->inputFileName,"/dev/stdin") && (strlen(id->inputFilePrefix)==0))  {
			fastq_misc_Usage(argc,argv,id);
			printf ("\tMissing input file prefix.  Please see usage above!\n\n");
			exit(1);
		}
		if ((id->mode == MODE_FASTQ_COUNT_ENTRY)) {
			fastq_count(id, od);
			OutputData_print(od);
		} else if ((id->mode == MODE_FASTQ_ACGTN_DISTRIBUTION)) {
			fastq_acgtnDistributions(id,od);
			OutputData_print(od);
		} else if ((id->mode == MODE_FASTQ_SHOW_READS)) {
			fastq_showReads(id);
		}
	}
}



