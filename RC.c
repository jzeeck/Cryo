#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //uint8_t
#include <string.h> //strcmp

#define swap(type, i, j) {type t = i; i = j; j = t;}

static const char *NAME = "Cryo";
static const char *VERSION = "1.0";

static int KEY_MAX_LENGTH = 256;
uint8_t c, keyLength, k;



FILE *fpPlaintext;

void printhelp();


int main(int argc, char const *argv[])
{
	//parse arguments
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
			}
			if (strcmp("-h", argv[i]) == 0)
			{
				printhelp();
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


	//TODO make command option to specify the key
	uint8_t key[KEY_MAX_LENGTH],S[KEY_MAX_LENGTH];
	FILE *fp;
	printf("Reading key\n");
	fp = fopen("key","r");
	if( fp == NULL )
	{
		perror("Error while opening key file.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < KEY_MAX_LENGTH; ++i)
	{
		c = fgetc(fp);
		if(feof(fp) || i >= KEY_MAX_LENGTH)
		{
			break;
		}
		key[i] = c;
		keyLength = i + 1;
	}

	//TODO move to own RC4 function
    /* Initialization */
	for (int i = 0; i < KEY_MAX_LENGTH; ++i)
	{
		S[i] = i;
	}
	/* Initial Permutation of S */
	int j,i;
	j = 0;
	for (i = 0; i < KEY_MAX_LENGTH; ++i)
	{
		j = (j + S[i] + key[i % keyLength]) % 256;
		swap(uint8_t, S[i],S[j]);
	}


	printf("Encrypting plaintext\n");
	fp = fopen("plaintext","r");
	if( fp == NULL )
	{
		perror("Error while opening plaintext file.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;j = 0;
	while(1) {
		c = fgetc(fp);//get next char
		if(feof(fp))
		{
			break;
		}
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		swap(uint8_t, S[i],S[j]);

		k = S[(S[i] + S[j]) % 256];
		printf("%02X", c^k);
		//TODO print output to output file
	}
	printf("\n");

	return 0;
}


void printhelp(void) {
	printf("Usage: cryo [options] file...\n");
	printf("Options:\n");
	printf("  -h\t\t\tDisplay this information\n");
	printf("  --help\t\tDisplay this information\n");
	printf("  --version\t\tDisplay version informatio\n");
	exit(0);
}