//
// written by xxxx
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "InputData.h"
#include "OutputData.h"
#include "dbSNP.h"
#include "fastq.h"

/** 
  main usage 

 **/
void usage(int argc, char *argv[]) {
	printf("%s", AUTHORS );
	printf("\nAn annotation pipeline for Next Gen Sequencing data. ");
	printf("\n\nUsage:");
	printf("\n\t%s dbSNP misc\t", argv[0]);
	printf("\n\n");
	exit(0);
}

/**
  main line 

 **/

int main(int argc, char *argv[]) {
		
	if (argc == 1) {
		usage(argc, argv);
	}
		
	if (strstr(argv[1], "dbSNP") || strstr(argv[1], "dbsnp")) {
		if (argc == 2) {
			printf("\n\t%s dbSNP misc\t\n\n", argv[0]);
		} else if (strstr(argv[2], "misc")) {
			dbSNP_misc(argc, argv);
		} else
			usage(argc, argv);
	} else if (strstr(argv[1], "fastq") ) {
		if (argc == 2) {
			printf("\n\t%s fastq misc\t\n\n", argv[0]);
		} else if (strstr(argv[2], "misc")) {
			fastq_misc(argc, argv);
		} else
			usage(argc, argv);
	} else
		usage(argc, argv);

	return 0;
}



