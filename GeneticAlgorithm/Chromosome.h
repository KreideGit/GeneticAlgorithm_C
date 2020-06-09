#pragma once

#include "Gene.h"

typedef DNA_DATA_TYPE(*MutationFunction)(DNA_DATA_TYPE);
typedef float(*FitnessFunction)(Gene**, int);

typedef struct
{
	Gene** Genes;
	int GenesLength;
	float Fitness;
	MutationFunction Mutate;
	FitnessFunction EvaluateFitness;
} Chromosome;

Chromosome* ChromosomeCreate(DNA_DATA_TYPE* dnas, int dnasLength, MutationFunction mutate, FitnessFunction evaluateFitness);
void ChromosomeDestroy(Chromosome* chromosome);
Chromosome* ChromosomeCross(Chromosome* chromosomeA, Chromosome* chromosomeB);
void ChromosomeMutate(Chromosome* chromosome);
void ChromosomeEvaluateFitness(Chromosome* chromosome);