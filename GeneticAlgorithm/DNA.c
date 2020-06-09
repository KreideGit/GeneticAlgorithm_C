#include "DNA.h"

DNA* DNACreate(DNA_DATA_TYPE value)
{
	DNA* dna = (DNA*)calloc(1, sizeof(DNA));
	RETURN_NULL_CHECK(dna == NULL);

	dna->Value = value;
	return dna;
}

void DNADestroy(DNA* dna)
{
	RETURN_VOID_CHECK(dna == NULL);
	free(dna);
}