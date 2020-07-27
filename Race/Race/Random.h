#pragma once
#include <cstdlib>


class Random
{
public:
	Random() = delete;
	static int getIntRand(int min, int max);
	static double getDoubleRand(double min, double max);
};

