//
// written by xxxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void fastq_misc_Usage(int argc, char *argv[], struct InputData *id);
void fastq_misc(int argc, char *argv[]);

void fastq_count(struct InputData *id, struct OutputData *od);
void fastq_acgtnDistributions(struct InputData *id, struct OutputData *od);
void fastq_showReads(struct InputData *id);
