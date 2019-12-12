#include "WORD.h"

WORD operator*(WORD op1, WORD op2)//Gruppenoperation auf F_2, berechnet Ergebnis der Verknüpfung der (bereits reduzierten) Wörter op1*op2 rekursiv und gibt Ergebnis in reduzierter Darstellung aus
{
	if (op1.isTrivial())
	{
		return WORD::normalize(op2);
	}
	if (op2.isTrivial())
	{
		return WORD::normalize(op1);
	}

	bool secondStartsWithA = (op2[0] != 0);//bestimmt, ob op2 mit mit a oder b anfängt
	bool firstEndNotSecondBegin = ((op1.size() % 2) == 0) == secondStartsWithA;//bestimmt, ob das Ende von op1 ungleich dem Anfang von op2 ist

	if (!secondStartsWithA)//Entferne vorhergehende 0 falls op2 mit b anfängt 
		op2.pop_front();

	if(firstEndNotSecondBegin)//ist das Ende von op1 ungleich dem Anfang von op2, so können op1 und op2 einfach konkateniert werden
	{
		op1.insert(op1.end(),op2.begin(),op2.end());
		return op1;
	}

	else //falls das Ende von op1 gleich dem Anfang von op2, so addieren sich die Koeffzienten und heben sich möglicherweise auf
	{
		op1.back() += op2.front();

		if(op1.back() == 0)
			op1.pop_back();

		if (secondStartsWithA)//falls op2 mit a angefangen hat, beginnt das neue op2 mit b
			op2[0] = 0;
		else
			op2.pop_front();

		return op1*op2;

	}

}

std::ostream& operator<<(std::ostream& os, const WORD &word) {
	std::ios_base::fmtflags f(std::cout.flags());
	std::cout << std::showpos;

	if (word.size() == 0)
		return (os << "e");

	int i = 0;
	if (word[0] == 0)
		i++;

	for (; i < word.size(); i++)
	{
		if (i % 2 == 0)
			os << "a" << word[i];
		else
			os << "b" << word[i];

		if (i < word.size() - 1)
			os << " ";
	}

	std::cout.flags(f);
	return os;
}
