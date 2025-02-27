#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <iostream>
#include <algorithm>



class WORD : public std::deque<int> //Definition von Elementen von F_2 (�ber dem Alphabet {a,b}). Wir speichern nur die Exponenten der reduzierten Darstellung ab, wobei jedes Wort mit a beginnt (d.h. W�rter die mit b beginnen, beginnen in dieser Darstellung mit einer 0) 

{
public: 
	inline bool isTrivial() const
	{
		if (this->size() == 0 || (this->size() == 1 && (*this)[0] == 0)) //Es gibt zwei M�glichkeiten ({} oder {0}) f�r das neutrale Element in der Exponentendarstellung, da es "weder mit a noch mit b beginnt"
			return true;
		return false;
	}
	static inline WORD normalize(WORD w)
	{
		if (w.isTrivial())
		{
			WORD empty;
			return empty;
		}
		return w;
	}

	friend WORD operator*(WORD op1, WORD op2);//Deklaration von Gruppenoperation
	friend std::ostream& operator<<(std::ostream& os, const WORD& word);
};

inline std::ostream& operator<<(std::ostream& os, const std::deque<WORD>& elem) {
	std::ios_base::fmtflags f(std::cout.flags());

	if (elem.size() > 0 && elem[0].size() > 0)
		os << elem[0] << "*";

	os << "[";
	for (unsigned int i = 1; i < elem.size(); i++)
	{
		os << elem[i];

		if (i < elem.size() - 1)
			os << " | ";
	}
	os << "]";

	std::cout.flags(f);
	return os;
}