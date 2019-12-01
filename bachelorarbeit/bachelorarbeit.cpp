#include "RandomGenerator.h"
#include "BarResElement.h"

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;



/*
struct KeyHasher //Hash-Funktion für Hash-Map
{
	std::size_t operator()(const BarResElement& elem) const
	{
		std::stringstream strstream;
		strstream << elem;

		return std::hash<std::string>()(strstream.str());
	}
};


unordered_map<BarResElement,BarResElement,KeyHasher> test; //Deklaration der HashMap


int main() {
	BarResElementGenerator* elemgen = new RandomGenerator(1);

	double max = 0;
	BarResElement maxelem;

	for (int i = 0; i < 1000; i++)
	{
		BarResElement elem = elemgen->nextElement(30, 10, 20, 10, 4);
		double norm = BarResElement::norm(elem);
		if (norm != 0)
		{
			double boundarynorm = BarResElement::norm(BarResElement::boundaryOperator(elem));
			if (boundarynorm/norm > max)
			{
				max = boundarynorm / norm;
				maxelem = elem;
			}
		}
		
	}
	cout << max << "\n" << maxelem << "\n" << BarResElement::boundaryOperator(maxelem);
	
	delete elemgen;

	return 0;
}
*/
/*
template <typename Numeric>
struct KeyHasher //Hash-Funktion für Hash-Map
{
	std::size_t operator()(const BarResElement<Numeric>& elem) const
	{
		std::stringstream strstream;
		strstream << elem;

		return std::hash<std::string>()(strstream.str());
	}
};

unordered_map<BarResElement, BarResElement, KeyHasher> test; //Deklaration der HashMap
*/

typedef int CoeffType;

int main() {
	
	int seed, datalength, elementMaxlength, wordMaxlength, expMax, maxKoeff;
	cout << "Gr\x94\xE1" << "e des Datensatzes eingeben: ";
	cin >> datalength;
	cout << "Seed eingeben (-1 um Systemzeit zu benutzen, -2 f\x81r default-Werte): ";
	cin >> seed;
	if (seed == -2)
	{
		seed = 1;
		elementMaxlength = 3;
		wordMaxlength = 3;
		expMax = 3;
		maxKoeff = 3;
	}
	else
	{
		if (seed == -1)
			seed = time(NULL);
		cout << "Maximale L\x84nge der generierten Werte: ";
		cin >> elementMaxlength;
		cout << "Maximale L\x84nge der generierten W\x94rter der freien Gruppe: ";
		cin >> wordMaxlength;
		cout << "Maximale Exponenten der generierten W\x94rter der freien Gruppe: ";
		cin >> expMax;
		cout << "Maximale Koeffizenten der Basisdarstellung: ";
		cin >> maxKoeff;
	}

	BarResElementGenerator<CoeffType>* elemgen = new RandomGenerator<CoeffType>(seed);
	BarResElement<CoeffType> curelem, curelemboundary;

	ofstream FILE("test.csv", ofstream::trunc);
	if (!FILE.is_open())
	{
		cout << "Datei kann nicht geschrieben werden.";
		return 0;
	}

	for (int i = 0; i < datalength; i++)
	{
		curelem = elemgen->nextElement(elementMaxlength, wordMaxlength, expMax, maxKoeff, 4);

		curelemboundary = BarResElement<CoeffType>::boundaryOperator(curelem);

		FILE << "\"" << curelem << "\";\"" << curelemboundary << "\";" << static_cast<double>(BarResElement<CoeffType>::norm(curelem))/BarResElement<CoeffType>::norm(curelemboundary) << endl;

		cout << "\r" << i * 100 / datalength << "%";
	}


	FILE.close();
	cout << "\rDatei generiert!";
	delete elemgen;
	
	
	/*
	WORD word1, word2, word3;
	BarResElement<int> elem1, elem2;

	
	word2.push_back(0);
	word2.push_back(-6);

	deque<WORD> basis1 = {word1,word2,word3};

	std::cout << basis1;
	

	word2.clear();
	deque<WORD> basis2 = {word1,word2,word3};
	
	return 0;
	*/
}
