#include "RandomGenerator.h"
#include "BarResElement.h"

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;



typedef int CoeffType; //Datentyp f�r Koeffizienten der Bar-Aufl�sung; durch �berladen von den notwendigen arithmetischen Operatoren und spezifizieren einer Methode f�r Zufallsgeneration des Datentyps in RandomGenerator.cpp (wie f�r den Typ double) k�nnen hier auch benutzerdefinierte Typen benutzt werden, z.B. f�r exakte rationale Arithmetik 


int main() {
	int seed, datalength, elementMaxlength, wordMaxlength, expMax, maxKoeff;
	cout << "Gr\x94\xE1" << "e des Datensatzes eingeben: ";
	cin >> datalength;
	cout << "Seed eingeben (-1 um Systemzeit zu benutzen, -2 f\x81r default-Werte): ";
	cin >> seed;
	if (seed == -2)
	{//Default-Parameter, die f�r den Datensatz der Bachelorarbeit verwendet werden
		seed = 1;
		elementMaxlength = 6;
		wordMaxlength = 4;
		expMax = 4;
		maxKoeff = 6;
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

	ofstream FILE("experiment.csv", ofstream::trunc);
	if (!FILE.is_open())
	{
		cout << "Datei kann nicht geschrieben werden.";
		return 0;
	}

	for (int i = 0; i < datalength; i++)
	{
		curelem = elemgen->nextElement(elementMaxlength, wordMaxlength, expMax, maxKoeff, 4);//generiere n�chstes Element

		curelemboundary = curelem.boundaryOperator();//wende Randoperator auf das Element an

		FILE << "\"" << curelem << "\";\"" << curelemboundary << "\";" << static_cast<double>(curelem.norm()) / curelemboundary.norm() << endl;//schreibe Tripel (curelem,curelemboundary,||curelem||/||curelemboundary||) in Datensatz

		if (i * 100.0 / datalength == i * 100 / datalength)
			cout << "\r" << i * 100 / datalength << "%";
	}


	FILE.close();
	cout << "\rDatei generiert!";
	delete elemgen;
	
	return 0;
}
