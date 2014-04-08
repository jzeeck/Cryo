#include <stdbool.h> //bool
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //uint8_t
#include <string.h> //strcmp
#include "util.h"

#define RC_KEY_MAX_LENGTH 256
#define swap(type, i, j) {type t = i; i = j; j = t;}

int rc4(const bool, const char*, const bool, const char*);