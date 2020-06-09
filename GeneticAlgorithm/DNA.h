#pragma once

#include "NullCheck.h"
#include <stdlib.h>

#define DNA_DATA_TYPE char

typedef struct
{
	DNA_DATA_TYPE Value;
} DNA;

DNA* DNACreate(DNA_DATA_TYPE value);
void DNADestroy(DNA* dna);