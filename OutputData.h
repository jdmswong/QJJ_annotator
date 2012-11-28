//
// written by xxxx
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OUTPUT_ORIENTATION_HORIZONTAL 1
#define OUTPUT_ORIENTATION_VERTICAL 2

struct OutputData {

	// 
	int outputOrientation;

	// output comments
	char outputComments[1024];

	// number of columns
	int n;
	char header[200][100];
	char data[200][100];


};

struct OutputData * OutputData_Init() ;
void OutputData_print(struct OutputData *od) ;
void OutputData_printHorizontal(struct OutputData *od) ;
void OutputData_printVertical(struct OutputData *od);
