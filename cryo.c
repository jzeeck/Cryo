#include "cryo.h"

static const char *NAME = "Cryo";
static const char *VERSION = "1.0";

static bool generateKey = false;
char * keyFile = "key";
char * outFile = "output";
FILE* fpPlaintext;



int main(int argc, char const *argv[])
{
	//parse arguments
	//TODO maybe make something else than strcmp? possible buffer overflow?
	//Suggestion might be to use c++ string variable. 
	if (argc < 2) // no arguments were passed
	{
		printf("%s-%s: fatal error: no input files\n", NAME, VERSION);
		exit(0);
	}

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			if (strcmp("--help", argv[i]) == 0)
			{
				printhelp();
				exit(0);
			}
			if (strcmp("-h", argv[i]) == 0)
			{
				printhelp();
				exit(0);
			}
			if (strcmp("--version", argv[i]) == 0)
			{
				printf("%s-%s\n", NAME, VERSION);
				exit(0);
			}
			//Generate key
			if (strcmp("-G", argv[i]) == 0)
			{
				generateKey = true;
				continue;
			}
			if (strcmp("-k", argv[i]) == 0)
			{
				//specify keyfile or value straight after
				if (i + 1 >= argc)
				{
					printf("No keyfile was given.\n"); 
					exit(-1);
				}
				++i;
				size_t len1 = strlen(argv[i]);
				keyFile = malloc(len1);//+1 for the zero-terminator
				if(keyFile == NULL){  
					printf("Out of memory\n");  
					exit(-1);  
				}
				memcpy(keyFile, argv[i], len1);
				continue;
			}
			if (strcmp("-kx", argv[i]) == 0)
			{
				//this is for the key specified as hex as next argument
			}

			//output
			if (strcmp("-o", argv[i]) == 0)
			{
				if (i + 1 >= argc)
				{
					printf("No output file was given.\n"); 
					exit(-1);
				}
				++i;
				size_t len1 = strlen(argv[i]);
				outFile = malloc(len1);
				if(outFile == NULL){  
					printf("Out of memory\n");  
					exit(-1);  
				}
				memcpy(outFile, argv[i], len1);
				continue;
			}
			if (strcmp("-O", argv[i]) == 0)
			{
				//Surpresses fileoutput only output will be in stdout as hex digits
			}

			//input
			if (strcmp("-x", argv[i]) == 0)
			{
				//input is in hex
			}

			else{
				printf("%s-%s: error: unrecognized command line option '%s'\n", NAME, VERSION, argv[i]);
				exit(0);
			}
		}
		else {
			fpPlaintext = fopen(argv[i],"r");
			if( fpPlaintext == NULL )
			{
				printf("%s-%s: error: %s: No such file or directory\n", NAME, VERSION, argv[argc - 1]);
				printf("terminated\n");
				exit(0);
			}
		}
	}

	if(generateKey)
	{
		return generate(256);//later specify number of bytes as parameter
	} 

	return rc4(true, keyFile, true, outFile);
}




void printhelp(void) {
	printf("Usage: cryo [options] file...\n");
	printf("Options:\n");
	printf("  -h\t\t\tDisplay this information\n");
	printf("  --help\t\tDisplay this information\n");
	printf("  --version\t\tDisplay version information\n");
	exit(0);
}