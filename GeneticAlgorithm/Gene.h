#pragma once

#include "NullCheck.h"
#include <stdlib.h>

#define DNA_DATA_TYPE char

typedef struct
{
	DNA_DATA_TYPE DNA;
} Gene;

Gene* GeneCreate(DNA_DATA_TYPE dna);
void GeneDestroy(Gene* gene);