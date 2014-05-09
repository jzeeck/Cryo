#include "keygen.h"

static SimpleRandomKISS_t rng_kiss;
static SimpleRandomCong_t rng_cong;

static const int DIVISIBLE_BY_FOUR_BITMASK = 0b11;

static const int HEX_FIRST_FOUR_BITMASK = 0xFF;
static const int HEX_SECOND_FOUR_BITMASK = 0xFF00;
static const int HEX_THIRD_FOUR_BITMASK = 0xFF0000;
static const int HEX_LAST_FOUR_BITMASK = 0xFF000000;

void init_random_key_gen(void) {

	time_t t;
	srand((unsigned) time(&t));
	int n, i;
	n = 16;

	uint32_t seed_array[n];

	for( i = 0 ; i < n ; i++ ) {
		seed_array[i] = rand();
	}

	simplerandom_kiss_seed_array(&rng_kiss, seed_array, n, true);
	simplerandom_cong_seed_array(&rng_cong, seed_array, n, true);
} 

int generate(const int number_of_bytes) {
	//sanity check
	if (number_of_bytes <= 0)
	{
		printf("Please request a positive number divisable by four.\n");
		return -1;
	}
	//check divisibility by four
	if ((number_of_bytes & DIVISIBLE_BY_FOUR_BITMASK) != 0)
	{
		printf("Please request a positive number divisable by four.\n");
		return -1;
	}
	init_random_key_gen();
	uint8_t key[number_of_bytes];

	time_t t;
	uint32_t random_number;
	srand((unsigned) time(&t));
	int i;

	for (i = 0; i < number_of_bytes; i += 4)
	{
		random_number = simplerandom_cong_next(&rng_cong);
		//printf("%u\n",random_number);
		key[i]			= random_number & HEX_FIRST_FOUR_BITMASK;
		key[i + 1]	= (random_number & HEX_SECOND_FOUR_BITMASK) >> 8;
		key[i + 2]	= (random_number & HEX_THIRD_FOUR_BITMASK) >> 16;
		key[i + 3]	= (random_number & HEX_LAST_FOUR_BITMASK) >> 24;
	}



	printf("Below is the generated key.\n");
	printf("==============================================================\n");
	for (i = 0; i < number_of_bytes; ++i)
	{
		printf("%02X", key[i]);
	}
	printf("\n");
	printf("==============================================================\n");

	return 0;
}