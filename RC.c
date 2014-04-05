#include "rc.h"


uint8_t c, keyLength, k;

char * plaintextFile = "plaintext";
char * outputFile = "output";

uint8_t S[RC_KEY_MAX_LENGTH];
uint8_t key[RC_KEY_MAX_LENGTH];

FILE *fp;
FILE *ofp;

void initS(void) {
	int j,i;
	/* Initialization */
	for (i = 0; i < RC_KEY_MAX_LENGTH; ++i)
	{
		S[i] = i;
	}
	/* Initial Permutation of S */
	j = 0;
	for (i = 0; i < RC_KEY_MAX_LENGTH; ++i)
	{
		j = (j + S[i] + key[i % keyLength]) % 256;
		swap(uint8_t, S[i],S[j]);
	}
}

int rc4(bool readKeyFromFile, char* keyNameOrValue) {

	//read key
	fp = fopen(keyNameOrValue,"r");
	if( fp == NULL )
	{
		perror("Error while opening key file.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < RC_KEY_MAX_LENGTH; ++i)
	{
		c = fgetc(fp);
		if(feof(fp) || i >= RC_KEY_MAX_LENGTH)
		{
			break;
		}
		key[i] = c;
		keyLength = i + 1;
	}
	fclose(fp);
	fp = NULL;


	int j, i;
	initS();

	fp = fopen(plaintextFile,"r");
	if( fp == NULL )
	{
		perror("Error while opening plaintext file.\n");
		exit(EXIT_FAILURE);
	}

	ofp = fopen(outputFile,"w");
	if( ofp == NULL )
	{
		perror("Error while opening output file.\n");
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
		
		printf("Key :%d\n", k);
		printf("Char: %d\n", c);
		printf("New : %d\n", c^k);
		
		printf("%02X", c^k);
		
		printf("\n");

		fputc(c^k, ofp);
	}
	printf("\n");

	fclose(fp);
	fclose(ofp);

	return 0;
}


