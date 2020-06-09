#include "Gene.h"

Gene* GeneCreate(DNA_DATA_TYPE dna)
{
	Gene* gene = (Gene*)calloc(1, sizeof(Gene));
	RETURN_NULL_CHECK(gene == NULL);

	gene->DNA = dna;
	return gene;
}

void GeneDestroy(Gene* gene)
{
	RETURN_VOID_CHECK(gene == NULL);
	free(gene);
}