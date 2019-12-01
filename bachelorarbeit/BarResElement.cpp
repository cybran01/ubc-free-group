#include "BarResElement.h"
/*
template <typename Numeric>
BarResElement<Numeric> operator+(BarResElement<Numeric> elemx, const BarResElement<Numeric>& elemy) //Definition der Addition von Elementen der Bar-Auflösung
{
	for (auto const& y : elemy)
		elemx.addSingleSummand(y.first,y.second);

	return elemx;
}

template <typename Numeric>
void operator+=(BarResElement<Numeric>& elemx, const BarResElement<Numeric>& elemy) //Definition der Addition von Elementen der Bar-Auflösung
{
	for (auto const& y : elemy)
		elemx.addSingleSummand(y.first, y.second);

}

template <typename Numeric>
BarResElement<Numeric> operator*(int r, BarResElement<Numeric> elem) //Definition der Skalarmultiplikation von Elementen der Bar-Auflösung
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

template <typename Numeric>
Numeric BarResElement<Numeric>::norm(const BarResElement<Numeric>& elem) //Definition der l^1-Norm
{
	Numeric res = 0;
	for (auto const& x : elem)
	{
		res += abs(x.second);
	}
	return res;
}

std::ostream& operator<<(std::ostream& os, const std::deque<WORD>& elem) {
	std::ios_base::fmtflags f(std::cout.flags());

	os << "[";
	for (unsigned int i = 0; i < elem.size(); i++)
	{
		os << elem[i];

		if (i < elem.size() - 1)
			os << " | ";
	}
	os << "]";

	std::cout.flags(f);
	return os;
}

template <typename Numeric>
std::ostream& operator<<(std::ostream& os, const BarResElement<Numeric>& elem) {
	std::ios_base::fmtflags f(std::cout.flags());

	for (auto const& x : elem)
	{

		os << std::showpos << x.second << "*" << x.first;
	}

	std::cout.flags(f);
	return os;
}


template <typename Numeric>
BarResElement<Numeric> BarResElement<Numeric>::boundaryOperator(const BarResElement<Numeric>& elem) //Randoperator 
{
	BarResElement<Numeric> res;

	for (auto const& x : elem)
	{
		res += x.second * (boundaryOperatorOnBasis(x.first));
	}

	return res;
}

template <typename Numeric>
BarResElement<Numeric> BarResElement<Numeric>::boundaryOperatorOnBasis(const std::deque<WORD>& basisElement) //Randoperator auf den Basiselementen, basisElement.size()>0 muss gelten (für unseren Fall gegeben)
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

template <typename Numeric>
void BarResElement<Numeric>::addSingleSummand(const std::deque<WORD>& basiselem, int coeff) //Addition einzelner Summanden
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
*/

