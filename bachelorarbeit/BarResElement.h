#pragma once

#include "WORD.h"

#include <iostream>
#include <map>
#include <deque>
#include <sstream>
#include <string>

template <typename Numeric>
class BarResElement : public std::map<std::deque<WORD>, Numeric>//Definition von Elementen der Bar-Auflösung als geordnete (via von Compiler generiertem operator<) Map von Paaren (Basiselement, Koeffizient) womit Basiselemente eindeutig sind
{
public:
	BarResElement<Numeric> boundaryOperator() const //Randoperator 
	{
		BarResElement<Numeric> res;

		for (auto const& x : *this)
		{
			res += x.second * (boundaryOperatorOnBasis(x.first));
		}

		return res;
	}

	Numeric norm() const //Definition der l^1-Norm
	{
		Numeric res = 0;
		for (auto const& x : *this)
		{
			res += abs(x.second);
		}
		return res;
	}

	friend std::ostream& operator<<(std::ostream& os, const BarResElement<Numeric>& elem) {
		std::ios_base::fmtflags f(std::cout.flags());
		
		for (auto const& x : elem)
		{
			os << std::showpos << x.second << "*" << x.first;	
		}

		std::cout.flags(f);
		return os;
	}

	friend BarResElement<Numeric> operator+(BarResElement<Numeric> elemx, const BarResElement<Numeric>& elemy) //Definition der Addition von Elementen der Bar-Auflösung
	{
		for (auto const& y : elemy)
			elemx.addSingleSummand(y.first, y.second);

		return elemx;
	}

	friend void operator+=(BarResElement<Numeric>& elemx, const BarResElement<Numeric>& elemy) //Definition der Addition von Elementen der Bar-Auflösung
	{
		for (auto const& y : elemy)
			elemx.addSingleSummand(y.first, y.second);

	}

	friend BarResElement<Numeric> operator*(Numeric r, BarResElement<Numeric> elem) //Definition der Skalarmultiplikation von Elementen der Bar-Auflösung
	{
		if (r == 0)
		{
			BarResElement empty;
			return empty;
		}

		for (auto const& x : elem)
		{
			elem[x.first] *= r;
		}
		return elem;
	}


private:
	void addSingleSummand(const std::deque<WORD>& basiselem, Numeric coeff) //Addition einzelner Summanden
	{
		if (this->count(basiselem) == 0)
			(*this)[basiselem] = coeff;
		else
		{
			(*this)[basiselem] += coeff;
			if ((*this)[basiselem] == 0)
				this->erase(basiselem);
		}
	}

	BarResElement<Numeric> boundaryOperatorOnBasis(const std::deque<WORD>& basisElement) const //Randoperator auf den Basiselementen, basisElement.size()>0 muss gelten (für unseren Fall gegeben)
	{
		BarResElement res;
		std::deque<WORD> tmp;

		for (unsigned int i = 0; i < basisElement.size() - 1; i++) {
			tmp = basisElement;
			tmp[i] = tmp[i] * tmp[i + 1];
			tmp.erase(tmp.begin() + (i+1));

			res.addSingleSummand(tmp, parity(i));
		}

		tmp = basisElement;
		tmp.pop_back();

		res.addSingleSummand(tmp, parity(basisElement.size()-1));

		return res;
	}
	static inline int parity(int i) {
		return i % 2 == 0 ? 1 : -1;
	}

};


