//
// written by xxxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// max number of samples in a VCF file
#define MAX_NUMBER_OF_SAMPLES 10

// 
#define VCF_COLUMN_CHR 1
#define VCF_COLUMN_POS 2
#define VCF_COLUMN_ID 3
#define VCF_COLUMN_REF 4
#define VCF_COLUMN_ALT 5
#define VCF_COLUMN_QUAL 6
#define VCF_COLUMN_FILTER 7
#define VCF_COLUMN_INFO 8
#define VCF_COLUMN_FORMAT 9


// a structure for holding VCF information 
struct VCF {

	// genotype format column number 
	int genotypeFormatColumn ;

	// n is the number of samples 
	int n;
	char sampleNames[MAX_NUMBER_OF_SAMPLES+1][1024];
	// column number in the VCF file 
	int sampleColumns[MAX_NUMBER_OF_SAMPLES+1];
	char sampleData[MAX_NUMBER_OF_SAMPLES+1][1024];

	// number of variants according to the genotype 
	unsigned long counts[MAX_NUMBER_OF_SAMPLES+1];


};


void vcf_misc_Usage(int argc, char *argv[], struct InputData *id);
void vcf_misc(int argc, char *argv[]);

void vcf_counts(struct InputData *id, struct OutputData *od);
void vcf_annotates(struct InputData *id, struct OutputData *od);
void vcf_splitGenotypeFormat(char header[], char genotype[], char outputStr[]) ;

