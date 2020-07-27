#include "Random.h"

int Random::getIntRand(int min, int max)
{
	return min + rand() % max + 1;
}

double Random::getDoubleRand(double min, double max)
{
	return min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
}