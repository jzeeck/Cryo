#include "util.h"


bool openFile(FILE** filePointer, const char * filename, const char* mode) {

	(*filePointer) = fopen(filename, mode);

	if((*filePointer) == NULL)
	{
		char* temp = concat("Error while opening", filename);
		char* message = concat(temp, "\n");
		perror(message);
		free(temp);
		free(message);
		exit(EXIT_FAILURE);
	}
	return true;
}

char* concat(const char *s1, const char *s2) {
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	char *result = malloc(len1+len2+1);//+1 for the zero-terminator
	//in real code you would check for errors in malloc here
	if(result == NULL){  
		printf("Out of memory\n");  
		exit(-1);  
	}
	memcpy(result, s1, len1);
	memcpy(result+len1, s2, len2+1);//+1 to copy the null-terminator
	return result;
}