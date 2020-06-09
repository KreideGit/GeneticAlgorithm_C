#pragma once

#include "Chromosome.h"

typedef DNA_DATA_TYPE(*InitializerFunction)(void);

typedef struct
{
	Chromosome** Chromosomes;
	int ChromosomesLength;
	int Generation;
	Chromosome* Fittest;
} Population;

Population* PopulationCreate(int chromosomesLength, int dnas, MutationFunction mutate, FitnessFunction evaluateFitness, InitializerFunction getInitialDNAValue);
void PopulationDestroy(Population* population);
void PopulationNextGeneration(Population* population);