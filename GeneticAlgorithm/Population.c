#include "Population.h"

static Chromosome* SelectParent(Population* population);
static void FindFittest(Population* population);

Population* PopulationCreate(int chromosomesLength, int dnasLength, MutationFunction mutate, FitnessFunction evaluateFitness, InitializerFunction getInitialDNAValue)
{
	Chromosome** chromosomes = (Chromosome**)calloc(chromosomesLength, sizeof(Chromosome*));
	RETURN_NULL_CHECK(chromosomes == NULL);

	for (int i = 0; i < chromosomesLength; i++)
	{
		DNA_DATA_TYPE* dnas = (DNA_DATA_TYPE*)calloc(dnasLength, sizeof(DNA_DATA_TYPE));
		RETURN_NULL_CHECK(dnas == NULL);

		for (int j = 0; j < dnasLength; j++)
		{
			dnas[j] = getInitialDNAValue();
		}

		Chromosome* chromosome = ChromosomeCreate(dnas, dnasLength, mutate, evaluateFitness);
		RETURN_NULL_CHECK(chromosome == NULL);

		free(dnas);
		chromosomes[i] = chromosome;
	}

	Population* population = (Population*)calloc(1, sizeof(Population));
	RETURN_NULL_CHECK(population == NULL);

	population->Chromosomes = chromosomes;
	population->ChromosomesLength = chromosomesLength;
	population->Generation = 0;
	FindFittest(population);
	return population;
}

void PopulationDestroy(Population* population)
{
	RETURN_VOID_CHECK(population == NULL);
	for (int i = 0; i < population->ChromosomesLength; i++)
	{
		ChromosomeDestroy(population->Chromosomes[i]);
	}
	free(population->Chromosomes);
	free(population);
}

void PopulationNextGeneration(Population* population)
{
	Chromosome** children = (Chromosome**)calloc(population->ChromosomesLength, sizeof(Chromosome*));
	RETURN_VOID_CHECK(children == NULL);

	for (int i = 0; i < population->ChromosomesLength; i++)
	{
		children[i] = ChromosomeCross(SelectParent(population), SelectParent(population));
	}

	for (int i = 0; i < population->ChromosomesLength; i++)
	{
		ChromosomeDestroy(population->Chromosomes[i]);
	}
	free(population->Chromosomes);

	population->Chromosomes = children;
	FindFittest(population);
	population->Generation++;
}

static Chromosome* SelectParent(Population* population)
{
	RETURN_NULL_CHECK(population == NULL);

	float fitnessSum = 0;
	for (int i = 0; i < population->ChromosomesLength; i++)
	{
		fitnessSum += population->Chromosomes[i]->Fitness;
	}

	float randomSector = (float)rand() / (float)RAND_MAX * fitnessSum;
	for (int i = 0; i < population->ChromosomesLength; i++)
	{
		if (randomSector < population->Chromosomes[i]->Fitness)
		{
			return population->Chromosomes[i];
		}
		randomSector -= population->Chromosomes[i]->Fitness;
	}

	return population->Chromosomes[0];
}

static void FindFittest(Population* population)
{
	RETURN_VOID_CHECK(population == NULL);

	float highestFitness = 0;
	for (int i = 0; i < population->ChromosomesLength; i++)
	{
		ChromosomeEvaluateFitness(population->Chromosomes[i]);
		if (population->Chromosomes[i]->Fitness >= highestFitness)
		{
			highestFitness = population->Chromosomes[i]->Fitness;
			population->Fittest = population->Chromosomes[i];
		}
	}
}