QJJ_annotator
==============

Flat file sequence annotator

File guide:

main : directs flow to relevant file depending on input.  Either: dbSNP, fastq, or vcf
|
|->	dbSNP : handles dbSNP data
|
|->	fastq : handles fastq data
|	|
|	|->	ACGTN : defines ACGTN struct and relevant utility functions
|
|->	vcf: handles vcf data

InputData : used by various classes.  Utility functions related to input

OutputData : used by various classes.  Utility functions related to output

Commons : utility funtions ( not sure where this is used )