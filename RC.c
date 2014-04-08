#include "rc.h"

uint8_t c, keyLength, k;

char * plaintextFile = "plaintext";

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


void setupKey(const bool readFromFile, const char *nameOrValue) {

	if (readFromFile)
	{
		openFile(&fp, nameOrValue, "r");

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
	} else {
		size_t len1 = strlen(nameOrValue);
		if (len1 > RC_KEY_MAX_LENGTH)
			len1 = RC_KEY_MAX_LENGTH;

		keyLength = len1;

		for (int i = 0; i < keyLength ; ++i)
		{
			key[i] = *(nameOrValue +i);
		}
	}
}

int rc4(const bool readKeyFromFile, const char* keyNameOrValue, const bool writeToFile, const char* opFile) {

	//get key
	setupKey(readKeyFromFile, keyNameOrValue);

	initS();

	openFile(&fp, plaintextFile, "r");
	openFile(&ofp, opFile, "w");

	int i, j;
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
		
		printf("%02X", c^k);//this outputs the hex number
		fputc(c^k, ofp);// writes to the file
	}
	printf("\n");

	fclose(fp);
	fclose(ofp);

	return 0;
}


