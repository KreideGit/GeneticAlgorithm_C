#include "Chromosome.h"

static void Mutate(Chromosome* chromosome);

Chromosome* ChromosomeCreate(DNA_DATA_TYPE* dnas, int dnasLength, MutationFunction mutate, FitnessFunction evaluateFitness)
{
	Gene** genes = (Gene**)calloc(dnasLength, sizeof(Gene*));
	RETURN_NULL_CHECK(genes == NULL);

	for (int i = 0; i < dnasLength; i++)
	{
		Gene* gene = GeneCreate(dnas[i]);
		RETURN_NULL_CHECK(gene == NULL);

		genes[i] = gene;
	}

	Chromosome* chromosome = (Chromosome*)calloc(1, sizeof(Chromosome));
	RETURN_NULL_CHECK(chromosome == NULL);

	chromosome->Genes = genes;
	chromosome->GenesLength = dnasLength;
	chromosome->Mutate = mutate;
	chromosome->EvaluateFitness = evaluateFitness;
	return chromosome;
}

void ChromosomeDestroy(Chromosome* chromosome)
{
	RETURN_VOID_CHECK(chromosome == NULL);
	for (int i = 0; i < chromosome->GenesLength; i++)
	{
		GeneDestroy(chromosome->Genes[i]);
	}
	free(chromosome->Genes);
	free(chromosome);
}

Chromosome* ChromosomeCross(Chromosome* chromosomeA, Chromosome* chromosomeB)
{
	RETURN_NULL_CHECK(chromosomeA == NULL);
	RETURN_NULL_CHECK(chromosomeB == NULL);
	RETURN_NULL_CHECK(chromosomeA->GenesLength != chromosomeB->GenesLength);
	RETURN_NULL_CHECK(chromosomeA->Mutate != chromosomeB->Mutate);
	RETURN_NULL_CHECK(chromosomeA->EvaluateFitness != chromosomeB->EvaluateFitness);

	DNA_DATA_TYPE* dnas = (DNA_DATA_TYPE*)calloc(chromosomeA->GenesLength, sizeof(DNA_DATA_TYPE));
	Chromosome* child = ChromosomeCreate(dnas, chromosomeA->GenesLength, chromosomeA->Mutate, chromosomeA->EvaluateFitness);
	free(dnas);
	RETURN_NULL_CHECK(child == NULL);

	for (int i = 0; i < child->GenesLength; i++)
	{
		Chromosome* targetChromosome = rand() % 2 == 0 ? chromosomeA : chromosomeB;
		child->Genes[i]->DNA = targetChromosome->Genes[i]->DNA;
	}

	Mutate(child);
	return child;
}

void ChromosomeEvaluateFitness(Chromosome* chromosome)
{
	RETURN_VOID_CHECK(chromosome == NULL);
	chromosome->Fitness = chromosome->EvaluateFitness(chromosome->Genes, chromosome->GenesLength);
}

static void Mutate(Chromosome* chromosome)
{
	RETURN_VOID_CHECK(chromosome == NULL);
	for (int i = 0; i < chromosome->GenesLength; i++)
	{
		chromosome->Genes[i]->DNA = chromosome->Mutate(chromosome->Genes[i]->DNA);
	}
}