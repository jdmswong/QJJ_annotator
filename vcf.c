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
	int vindex, i,j,k,l;
	char str[1024];
	struct VCF *vcf = vcf_Init();

	int length;
	char **pptr;
	char **vptr;

	char tmpStr[1024];


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
					printf ("\n[%s:%d] - genotype format column # %d; sample ID: %s ; column number %d ; genotype format %s ; \tgenotype %s", __FILE__, __LINE__, vcf->genotypeFormatColumn, vcf->sampleNames[j], vcf->sampleColumns[j], values[vcf->genotypeFormatColumn], values[vcf->sampleColumns[j]]);
				}

				sprintf (str, "[sample,%s\t", values[vcf->genotypeFormatColumn]);
				strcat(str, vcf->sampleNames[j]);
				pptr = common_str2array(values[vcf->sampleColumns[j]], ':', &length);
				for (k = 0; k < length; k++) {
					if (k == 1) {
						strcat (str, "\t{");
						strcat (str, pptr[k]);

						vptr = common_str2array(pptr[k], ',', &l);
						int rdepth = atoi(vptr[0]);
						int vdepth = atoi(vptr[1]);
						double d;

						strcat (str, "\t");
						strcat (str, vptr[0]);
						strcat (str, "\t");
						d = (100.0 * rdepth)/(rdepth+vdepth);
						sprintf (tmpStr,"%.2f",d);
						strcat (str,tmpStr);

						strcat (str, "\t");
						strcat (str, vptr[1]);
						strcat (str, "\t");
						d = (100.0 * vdepth)/(rdepth+vdepth);
						sprintf (tmpStr,"%.2f",d);
						strcat (str,tmpStr);
						strcat (str, "\t");
						strcat (str, "}");
						free(vptr);
					} else {
						strcat (str, "\t");
						strcat (str, pptr[k]);
					}
				}
				strcat (str, "\t");
				strcat (str, "]");

				free(pptr);
				strcpy(vcf->sampleData[j], str);
			}

			if (id->verbose) {
				printf ("\n\n");
			}

			for (i = 1; i<= vcf->n; i++ ) {
				printf ("%s", vcf->sampleData[i]);
				if (i < vcf->n)
					printf ("\t");
				else
					printf ("\n");
			}
		}
   }   
   fclose(id->inputFile);
}


