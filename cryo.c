#include "rc.h"
#include "cryo.h"

static const char *NAME = "Cryo";
static const char *VERSION = "1.0";

char * keyFile = "key";
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



	return rc4(true, keyFile);
}




void printhelp(void) {
	printf("Usage: cryo [options] file...\n");
	printf("Options:\n");
	printf("  -h\t\t\tDisplay this information\n");
	printf("  --help\t\tDisplay this information\n");
	printf("  --version\t\tDisplay version informatio\n");
	exit(0);
}