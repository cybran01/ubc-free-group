#pragma once
#include "BarResElementGenerator.h"
#include <cstdlib>

template<typename Numeric>
class RandomGenerator : public BarResElementGenerator<Numeric>	{
public:
	RandomGenerator(int _rndSeed) : rndSeed(_rndSeed)	{
		srand(rndSeed); //Initialisierung des Zufallsgenerators mit dem vorgegebenen Seed
	}
	BarResElement<Numeric> RandomGenerator<Numeric>::nextElement(int elementMaxlength, int wordMaxlength, int expMax, int maxKoeff, int degree)//generiert ein Element aus der Bar-Auflösung vom Grad degree
	{
		BarResElement<Numeric> res;

		int length = (rand() % elementMaxlength) + 1;//einziges Element der Länge 0 ist das Nullelement und uninteressant
		for (int i = 0; i < length; i++) {

			BarResElement<Numeric> tmpelem;
			std::deque<WORD> tmpbasis;


			for (int ii = 0; ii < degree+1; ii++)//generiert ein Basiselement
			{
				tmpbasis.push_back(nextWord(wordMaxlength, expMax));
			}

			tmpelem[tmpbasis] = rand() % 2 == 0 ? nextCoefficient(maxKoeff) : -nextCoefficient(maxKoeff);//generiert Koeffizienten und entscheidet Vorzeichen, wobei beide Optionen gleiche Wahrscheinlichkeit haben sollen
			res += tmpelem;
		}
		return res;

	}

private:
	int rndSeed;
	Numeric nextCoefficient(int maxkoeff) const;
	WORD nextWord(int maxlength, int maxexp) const//generiert ein Word der maximalen Länge maxlength und mit maximalem Exponenten maxexp
	{
		WORD res;
		int length = rand() % (maxlength + 1);
		if (length == 0)//Nur triviales Element hat Länge 0
			return res;

		if (rand() % 2 == 1)//Wahrscheinlichkeit, ob Wort mit a oder b anfängt soll jeweils 1/2 sein
			res.push_back(0);

		for (int i = 0; i < length; i++)
		{
			int nextExp = (rand() % maxexp) + 1;
			res.push_back(rand() % 2 == 0 ? nextExp : -nextExp);//generiert Exponenten und entscheidet Vorzeichen
		}
		return res;
	}

};

