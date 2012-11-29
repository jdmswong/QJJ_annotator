//
// written by xxxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "InputData.h"
#include "OutputData.h"
#include "vcf.h"
#include "main.h"



struct VCF *vcf_Init() {

	int i;
	struct VCF *vcf = (struct VCF *) malloc (sizeof (struct VCF));

	vcf->n = 0;
	for (i=1;i<=MAX_NUMBER_OF_SAMPLES;i++) {
   	strcpy(vcf->sampleNames[i],"");
		vcf->sampleColumns[i] = 0;
   	strcpy(vcf->sampleData[i],"");
		vcf->counts[i] = 0;
	}
	return vcf;
}



/**
  count the number of variants in the input file 
  **/
void vcf_counts(struct InputData *id, struct OutputData *od) {

   char line[MAX_CHAR_PER_LINE];
	char values[MAX_NUMBER_OF_COLUMNS][MAX_CHAR_PER_COLUMN];
	int vindex, i, j;
	struct VCF *vcf = vcf_Init();

   id->inputFile = fopen(id->inputFileName, "r");
	if (id->inputFile == NULL) {
		printf ("\n[%s:%d] - error open file '%s'", __FILE__, __LINE__, id->inputFileName);
		printf ("\n\n");
		exit (1);
	}

	// read input file 
   while ((fgets(line, MAX_CHAR_PER_LINE, id->inputFile) != NULL)) {

		// skip lines with comments 
		if ((line[0] == '#') && (line[1] == '#'))
			continue;

		if (id->verbose) {
			printf ("\n\n=====================================");
      	printf ("\n[%s:%d] - %s", __FILE__, __LINE__, line);
		}

		InputData_parseLine(line, values, &vindex);
		//InputData_printParsedLine(values,vindex);

		// get sample information 
		if (strstr(line,"#CHROM")) {
			vcf->n = 0;
			vcf->genotypeFormatColumn = VCF_COLUMN_FORMAT;
			for (i = VCF_COLUMN_FORMAT+1; i <= vindex; i++) {
				vcf->n++;
				strcpy(vcf->sampleNames[vcf->n], values[i]);
				vcf->sampleColumns[vcf->n] = i;
				if (id->verbose) {
					printf ("\n[%s:%d] - sample ID: %s column number %d", __FILE__, __LINE__, vcf->sampleNames[vcf->n], vcf->sampleColumns[vcf->n]);
				}
			}
			if (id->verbose) {
				printf ("\n\n");
			}
		} else {
			
			if (vcf->n == 0) {
				printf ("\n[%s:%d] - Please use -S, -C and -G to indicate your sample names, genotypes and genotype column format numbers.\n\n", __FILE__, __LINE__);
				exit (1);
			}
			
			j = 0;
			for (i = VCF_COLUMN_FORMAT+1; i <= vindex; i++) {
				j++;
				if (id->verbose) {
					printf ("\n[%s:%d] - sample ID: %s ; column number %d ; \tgenotype %s", __FILE__, __LINE__, vcf->sampleNames[j], vcf->sampleColumns[j], values[vcf->sampleColumns[j]]);
				}
				// count if genotype is not './.' and '0/0'
				if (!strstr(values[vcf->sampleColumns[j]],"./.") && 
					(!strstr(values[vcf->sampleColumns[j]],"0/0"))) {
					if (id->verbose) {
						printf ("; counting ");
					}
					vcf->counts[j]++;
				}
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
	
	strcpy(od->outputComments, "## number of variants in each of the samples");
	for (i = 1; i <= vcf->n; i++) {
		od->n++;
		sprintf(od->header[od->n], "%s", vcf->sampleNames[i]);
		sprintf(od->data[od->n], "%ld",vcf->counts[i]);
	}

}





/**
  annotate VCF file 
  **/
void vcf_annotates(struct InputData *id, struct OutputData *od) {

   char line[MAX_CHAR_PER_LINE];
	char values[MAX_NUMBER_OF_COLUMNS][MAX_CHAR_PER_COLUMN];
	int vindex, i,j,k,l,p;
	char str[1024];
	struct VCF *vcf = vcf_Init();

	int length;
	char **pptr;
	char **vptr;

	char tmpStr[1024];
	char outputStr[1024];


   id->inputFile = fopen(id->inputFileName, "r");
	if (id->inputFile == NULL) {
		printf ("\n[%s:%d] - error open file '%s'", __FILE__, __LINE__, id->inputFileName);
		printf ("\n\n");
		exit (1);
	}

	// read input file 
   while ((fgets(line, MAX_CHAR_PER_LINE, id->inputFile) != NULL)) {

		// skip lines with comments 
		if ((line[0] == '#') && (line[1] == '#'))
			continue;

		if (id->verbose) {
			printf ("\n\n=====================================");
      	printf ("\n[%s:%d] - %s", __FILE__, __LINE__, line);
		}

		InputData_parseLine(line, values, &vindex);
		//InputData_printParsedLine(values,vindex);

		// get sample information 
		if (strstr(line,"#CHROM")) {
			vcf->n = 0;
			vcf->genotypeFormatColumn = VCF_COLUMN_FORMAT;
			for (i = VCF_COLUMN_FORMAT+1; i <= vindex; i++) {
				vcf->n++;
				strcpy(vcf->sampleNames[vcf->n], values[i]);
				vcf->sampleColumns[vcf->n] = i;
				if (id->verbose) {
					printf ("\n[%s:%d] - sample ID: %s column number %d", __FILE__, __LINE__, vcf->sampleNames[vcf->n], vcf->sampleColumns[vcf->n]);
				}
			}
			if (id->verbose) {
				printf ("\n\n");
			}
		} else {
			
			if (vcf->n == 0) {
				printf ("\n[%s:%d] - Please use -S, -C and -G to indicate your sample names, genotypes and genotype column format numbers.\n\n", __FILE__, __LINE__);
				exit (1);
			}
			
			// for each of the samples 
			j = 0;
			for (i = VCF_COLUMN_FORMAT+1; i <= vindex; i++) {
				j++;
				if (id->verbose) {
					printf ("\n\n[%s:%d] - sample ID: %s ; column number %d ", __FILE__, __LINE__, vcf->sampleNames[j], vcf->sampleColumns[j]);
					printf ("\n[%s:%d] - genotype %s ; genotype format column # %d ", __FILE__, __LINE__, values[vcf->genotypeFormatColumn], vcf->genotypeFormatColumn);
					printf ("\n[%s:%d] - genotype %s", __FILE__, __LINE__, values[vcf->sampleColumns[j]]);
				}

				sprintf (outputStr, "[sample,%s\t", values[vcf->genotypeFormatColumn]);
				strcat(outputStr, vcf->sampleNames[j]);
					
				vcf_splitGenotypeFormat(values[vcf->genotypeFormatColumn], values[vcf->sampleColumns[j]], str);

				strcat (outputStr,"\t");
				strcat (outputStr,str);
				strcat (outputStr,"\t");
				strcat (outputStr,"]");
				strcpy(vcf->sampleData[j], outputStr);
			}

			if (id->verbose) {
				printf ("\n\n");
			}

			for (i = 1; i<= vcf->n; i++ ) {
				printf ("%s", vcf->sampleData[i]);
					printf ("\t");
			}
			printf ("%s", line);
		}
   }   
   fclose(id->inputFile);
}

/**
  header   => GT:AD:DP:GQ:PL
  genotype => 1/1:0,55:55:99:1451,138,0

  construct a uniform format for represent the genotype

  returns: 12 columns strings

  **/
void vcf_splitGenotypeFormat(char header[], char genotype[], char outputStr[]) {

	int dlength;
	char **dptr;
	int hlength;
	char **hptr;
	int i,j;
	int ptrLength;
	char **ptr;
	int totalDP;
	char str[1024];
	char geno[1024];

	strcpy(outputStr,"");

	if (strstr(genotype,"./.")) {
		for (i = 0; i < 12; i++) {
			if (i==0) {
				strcat(outputStr,"{");
				strcat(outputStr,".");
				strcat(outputStr,"\t");
			} else if (5==0) {
				strcat(outputStr,"}");
				strcat(outputStr,"\t");
			} else {
				strcat(outputStr,".");
				strcat(outputStr,"\t");
			}
		}
		// remove the last '\t'
		outputStr[strlen(outputStr)-1] = '\0';
		return ;
	}

	hptr = common_str2array(header, ':', &hlength);
	dptr = common_str2array(genotype, ':', &dlength);
	for (i = 0; i < hlength; i++) {
		if (strstr(hptr[i],"GT")) {
			if (strstr(dptr[i],"0/0")) {
				strcpy(geno,"AA_homozygous");
			} else if (strstr(dptr[i],"1/1")) {
				strcpy(geno,"BB_homozygous");
			} else if (strstr(dptr[i],"0/1")) {
				strcpy(geno,"AB_heterozygous");
			} else if (strstr(dptr[i],"0/2")) {
				strcpy(geno,"?????");
			} else if (strstr(dptr[i],"1/2")) {
				strcpy(geno,"TRI-ALLELIC");
			} else {
				strcpy(geno,"?????");
			}
		} else if (strstr(hptr[i],"AD")) {
			ptr = common_str2array(dptr[i],',', &ptrLength);
			totalDP = 0;
			for (j = 0; j < ptrLength; j++) {
				totalDP += atoi(ptr[j]);
			}
			strcat(outputStr, "{");
			strcat(outputStr, dptr[i]);
			// assumes always tri-allelic
			int N = 3;
			for (j = 0; j < N; j++) {
				if (j < ptrLength) {
					strcat(outputStr, "\t");
					strcat(outputStr, ptr[j]);
					strcat(outputStr, "\t");
					sprintf(str, "%.2f",(100.0 * atoi(ptr[j])) / totalDP);
					strcat(outputStr, str);
				} else {
					strcat(outputStr, "\t");
					strcat(outputStr, ".");
					strcat(outputStr, "\t");
					sprintf(str, ".");
					strcat(outputStr, str);
				}
			}
			strcat(outputStr, "\t}\t");
		} else {
			strcat (outputStr,dptr[i]);
			strcat(outputStr, "\t");
		}
	}
	strcat(outputStr, geno);
}
