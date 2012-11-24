#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#include "InputData.h"
#include "OutputData.h"

#include "main.h"
#include "dbSNP.h"

#define DBSNP_COLUMN_CHR 1
#define DBSNP_COLUMN_START 2
#define DBSNP_COLUMN_END 3
#define DBSNP_COLUMN_REFERENCE 4
#define DBSNP_COLUMN_VARIANT 5


void dbSNP_misc_Usage(int argc, char *argv[], struct InputData *id) {
	
	printf("%s", AUTHORS);
	printf("\nUtils for annotating UCSC dbSNP format files.");
	printf( "\n\n\t%s dbSNP misc [ -m mode ]  ",
			argv[0]);
	printf("\n");
	
	if ((id->mode == MODE_ANNOTATE_DBSNP_SNP) || (id->mode == 0))  {
		printf("\n\t-m %d\tannotate known SNPs in UCSC dbSNP",MODE_ANNOTATE_DBSNP_SNP);
		if ((id->mode == MODE_ANNOTATE_DBSNP_SNP) )  {
			printf("\n\t\t-i TABIX_FILE\tUCSC dbSNP file indexed by tabix.");

			printf("\n\t\t-T TARGET_FILE\ttab-delimited target file");
			printf("\n\t\t-c INT\tchromosome column number in TARGET_FILE.  Default is %d", DBSNP_COLUMN_CHR);
			printf("\n\t\t-s INT\tstart column number in TARGET_FILE.  Default is %d",DBSNP_COLUMN_START);
			printf("\n\t\t-e INT\tend column number in TARGET_FILE.  Default is %d", DBSNP_COLUMN_END);
			printf("\n\t\t-R INT\treference base column number in TARGET_FILE.  Default is %d", DBSNP_COLUMN_REFERENCE);
			printf("\n\t\t-S INT\tvariant base column number in TARGET_FILE.  Default is %d", DBSNP_COLUMN_VARIANT);
		}
	}

	if (id->mode > 0) {
		printf("\n\t\t-v\tverbose mode ( for debugging )");
	}

	printf("\n\n");
	exit (0);
}




void dbSNP_misc (int argc, char *argv[]) {

	char c;
	struct InputData *id = InputData_Init();
	//struct OutputData *od = OutputData_Init();

	while ((c = getopt(argc, argv, "m:i:v")) != -1) {
		switch (c) {
		case 'm':
			id->mode = atoi(optarg);
			break;
		case 'i':
			strcpy(id->inputFileName, optarg);
			break;
		case 'v':
			id->verbose = 1;
			break;
		default:
			//abort();
			printf("\n\nunknown arguments %s ", optarg);
			dbSNP_misc_Usage(argc, argv, id);
		}
	}
	if (id->mode == 0)
		dbSNP_misc_Usage(argc,argv,id);

	if (id->verbose)
		InputData_printUserInputs(id);


	if ((id->mode == MODE_ANNOTATE_DBSNP_SNP)) {
		if (strlen(id->inputFileName)==0) 
			dbSNP_misc_Usage(argc,argv,id);
		//dbSNP_UCSC_annotate_SNPs (id, cc,ss,ee,rr,vv,flag);
	}
}



