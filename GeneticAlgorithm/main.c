#include "Population.h"
#include <stdio.h>
#include <time.h>

//Specify valid characters and the target string
char validCharacters[] = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ.";
char targetString[] = "To be or not to be.";

//Calculate string lengths
int validCharactersLength = sizeof(validCharacters) / sizeof(validCharacters[0]) - 1;
int targetStringLength = sizeof(targetString) / sizeof(targetString[0]) - 1;

DNA_DATA_TYPE Mutate(DNA_DATA_TYPE value)
{
	//Mutation rate 1%
	if ((float)rand() / (float)RAND_MAX < 0.01f)
	{
		//Choose a random character from the validCharacters array
		return validCharacters[rand() % validCharactersLength];
	}
	//Otherwise, do not mutate the value
	return value;
}

float EvaluateFitness(Gene** genes, int genesLength)
{
	//Loop through the genes and compare it to the target string
	//The more characters are in the right position the better
	//Scales with a power of 2

	int goodCharacters = 0;
	for (int i = 0; i < genesLength; i++)
	{
		if (genes[i]->DNA == targetString[i])
		{
			goodCharacters++;
		}
	}
	return (float)(goodCharacters * goodCharacters);
}

DNA_DATA_TYPE GetInitialDNAValue(void)
{
	//Choose a random character from the validCharacters array
	return validCharacters[rand() % validCharactersLength];
}

int main(int argc, char** argv)
{
	//Random seeding
	time_t t;
	srand((unsigned)time(&t));

	//Time measurement
	clock_t clk;
	double totalTime = 0;

	//Create the population with a size of 100, specify the gene length and the required functions
	Population* population = PopulationCreate(500, targetStringLength, Mutate, EvaluateFitness, GetInitialDNAValue);

	while(1)
	{
		clk = clock();

		//Print the genes(char[]) of the fittest chromosome
		for (int i = 0; i < population->Fittest->GenesLength; i++)
		{
			printf("%c", population->Fittest->Genes[i]->DNA);
		}
		printf("\n");

		//If a chromosome hits the max fitness
		if (population->Fittest->Fitness == targetStringLength * targetStringLength)
		{
			printf("\nGeneration: %i | Average generation time: %f\n", population->Generation, totalTime / population->Generation);
			break;
		}

		//Create the next generation
		PopulationNextGeneration(population);

		//Add the elapsed time 
		clk = clock() - clk;
		totalTime += ((double)clk) / CLOCKS_PER_SEC;
	}

	PopulationDestroy(population);
	return 0;
}