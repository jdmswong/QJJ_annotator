//
// written by Quang.Trinh@oicr.on.ca
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/**
  inputStr should be comma-separated 
  **/
char ** common_str2array(char inputStr[], char delimeter, int *length) {

	char *ptr = inputStr;
	int i,j,n;
	char str[1024];
	char **array ;

	// count the number of strings separated by commas
	n = 0;
	while (*ptr) {
		if (*ptr == delimeter)
			n++;
		ptr++;
	}
	// one more at the end 
	n++;



	// create array and set it to NULL
	array = (char **) malloc ((n+1) * sizeof(char *));
	for (i = 0; i <= n; i++)
		array[i] = NULL;

	ptr = inputStr;
	i = 0;
	j = 0;
	while (*ptr) {
		if (*ptr == delimeter) {
			str[i] = '\0';
			//printf ("\n string '%s' length %d", str,strlen(str));
			array[j] = (char *) malloc ((strlen(str) + 1)* sizeof(char));
			strcpy(array[j], str);
			j++;
			i = 0;
		} else {
			str[i] = *ptr;
			i++;
		}
		ptr++;
	}
	// get the last string 
	str[i] = '\0';
	//printf ("\n string '%s'", str);
	array[j] = (char *) malloc ((strlen(str)+1) * sizeof(char));
	strcpy(array[j], str);

	*length = n;
	/*
	for (i = 0; i < n; i++)
		printf ("\n n %d length %d before returning '%s' ", n,*length, array[i]);
		*/
	return array;
}

/**
  delimeter: delimeter to stop
**/
void common_getSubstring(char *inputStr, char delimeter, char outputSubString[]) {
  int i = 0;
  char *ptr = inputStr;
  while ((*ptr != delimeter) && (*ptr != '\0')) {
	  outputSubString[i] = *ptr;
	  i++;
	  ptr++;
  }
  outputSubString[i] = '\0';
  if ((*ptr != '\0') && (delimeter != '\0'))
	  outputSubString = NULL;
}
