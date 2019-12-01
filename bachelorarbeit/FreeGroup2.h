#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <iostream>
#include <algorithm>


/*
Definition von Elementen von F_2 (über dem Alphabet {a,b}). Wir speichern nur die Exponenten der reduzierten Darstellung ab, wobei jedes Wort mit a beginnt (d.h. Wörter die mit b beginnen, beginnen in dieser Darstellung mit einer 0) 
*/
typedef class : public std::deque<int>
{
public: 
	inline bool isTrivial() const
	{
		if (this->size() == 0 || (this->size() == 1 && (*this)[0] == 0)) //Es gibt zwei Möglichkeiten ({} oder {0}) für das neutrale Element in der Exponentendarstellung, da es weder mit a noch mit b beginnt.
			return true;
		return false;
	}
} WORD;


WORD operator*(WORD op1, WORD op2);//Deklaration von Gruppenoperation
std::ostream& operator<<(std::ostream& os, const WORD& word);
bool operator<(const WORD& op1, const WORD& op2);