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
	inline std::string toString()
	{
		std::stringstream strstream;
		strstream << boundaryOperator(*this);

		return strstream.str();
	}
	static BarResElement<Numeric> boundaryOperator(const BarResElement<Numeric>& elem) //Randoperator 
	{
		BarResElement<Numeric> res;

		for (auto const& x : elem)
		{
			res += x.second * (boundaryOperatorOnBasis(x.first));
		}

		return res;
	}

	static Numeric norm(const BarResElement<Numeric>& elem) //Definition der l^1-Norm
	{
		Numeric res = 0;
		for (auto const& x : elem)
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

	friend 	BarResElement<Numeric> operator*(Numeric r, BarResElement<Numeric> elem) //Definition der Skalarmultiplikation von Elementen der Bar-Auflösung
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

	static BarResElement<Numeric> boundaryOperatorOnBasis(const std::deque<WORD>& basisElement) //Randoperator auf den Basiselementen, basisElement.size()>0 muss gelten (für unseren Fall gegeben)
	{
		BarResElement res;
		std::deque<WORD> tmp = basisElement;
		tmp.pop_front();
		res[tmp] = 1;

		for (unsigned int i = 0; i < basisElement.size() - 1; i++) {
			tmp = basisElement;
			tmp[i + 1] = tmp[i] * tmp[i + 1];
			tmp.erase(tmp.begin() + i);

			res.addSingleSummand(tmp, parity(i + 1));
		}

		tmp = basisElement;
		tmp.pop_back();

		res.addSingleSummand(tmp, parity(basisElement.size()));

		return res;
	}
	static inline int parity(int i) {
		return i % 2 == 0 ? 1 : -1;
	}

};


