#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "InputData.h"
#include "OutputData.h"

#include "vcf.h"
#include "main.h"

#define MODE_VCF_COUNT_ENTRY 1
#define MODE_VCF_ANNOTATE_SAMPLES 10

/**
  VCF usage 
  **/
void vcf_misc_Usage(int argc, char *argv[], struct InputData *id) {
	
	printf("%s", AUTHORS);
	printf("\nUtils for processing VCF files .");
	printf( "\n\n\t%s vcf misc [ -m mode ]  ",
			argv[0]);
	printf("\n");
	
	if ((id->mode == MODE_VCF_COUNT_ENTRY) || (id->mode == 0))  {
		printf("\n\t-m %d\tcount number of variants",MODE_VCF_COUNT_ENTRY);
		if ((id->mode == MODE_VCF_COUNT_ENTRY) )  {
			printf("\n\t\t-i FILE\tinput VCF file.");
		}
	}
	if ((id->mode == MODE_VCF_ANNOTATE_SAMPLES) || (id->mode == 0))  {
		printf("\n\t-m %d\tannotate samples",MODE_VCF_ANNOTATE_SAMPLES);
		if ((id->mode == MODE_VCF_ANNOTATE_SAMPLES) )  {
			printf("\n\t\t-i FILE\tinput VCF file.");
			printf("\n\t\t-S STR\tsample names separated by commas ( e.g., Sample1,Sample2,Sample3 ).");
			printf("\n\t\t-C STR\tsamples genotype column numbers ( e.g., 10,11,12 )");
			printf("\n\t\t-G INT\tgenotype format column number.");
		}
	}

	if (id->mode > 0) {
		printf("\n\t\t-H\tprints outputs in horizontal format.  Default, outputs are printed in vertical format.");
		printf("\n\t\t-v\tverbose mode ( for debugging )");
	}

	printf("\n\n");
}


/**
	vcf main
**/
void vcf_misc(int argc, char *argv[]) {
	char c;
	struct InputData *id = InputData_Init();
	struct OutputData *od = OutputData_Init();
	char samples[1024] = "", columns[1024] = "";
	int genotypeFormatColumn = -1;

	while ((c = getopt(argc, argv, "m:i:p:C:S:G:vH")) != -1) {
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
		case 'S':
			strcpy(samples, optarg);
			break;
		case 'C':
			strcpy(columns, optarg);
			break;
		case 'H':
			od->outputOrientation = OUTPUT_ORIENTATION_HORIZONTAL;
			break;
		case 'G':
			genotypeFormatColumn = atoi(optarg);
			break;
		case 'v':
			id->verbose = 1;
			break;
		default:
			//abort();
			printf("\n\nunknown arguments %s ", optarg);
			vcf_misc_Usage(argc, argv, id);
		}
	}
	if (id->mode == 0) {
		vcf_misc_Usage(argc,argv,id);
		exit(1);
	}

	if (id->verbose)
		InputData_printUserInputs(id);


	if ((id->mode == MODE_VCF_COUNT_ENTRY) ||
		 (id->mode == MODE_VCF_ANNOTATE_SAMPLES)
			) {
		if (strlen(id->inputFileName)==0)  {
			vcf_misc_Usage(argc,argv,id);
			printf ("\tMissing input file.  Please see usage above!\n\n");
			exit(1);
		} else if (strstr(id->inputFileName,"/dev/stdin") && (strlen(id->inputFilePrefix)==0))  {
			vcf_misc_Usage(argc,argv,id);
			printf ("\tMissing input file prefix.  Please see usage above!\n\n");
			exit(1);
		}


		if ((id->mode == MODE_VCF_COUNT_ENTRY)) {
			vcf_counts(id, od);
			OutputData_print(od);
		} else if ((id->mode == MODE_VCF_ANNOTATE_SAMPLES)) {
			vcf_annotates(id, od);
		}
	}
}



