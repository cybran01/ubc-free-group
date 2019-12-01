#include "RandomGenerator.h"


template <>
double RandomGenerator<double>::nextCoefficient(int maxkoeff)//generiert einen Koeffizienten größer 0 und <=maxkoeff
{
	return ((rand() + 1.0) / (RAND_MAX+1.0))*maxkoeff;

}

template<>
int RandomGenerator<int>::nextCoefficient(int maxkoeff)//generiert einen Koeffizienten größer 0 und <=maxkoeff
{
	return (rand() % maxkoeff)+1;

}