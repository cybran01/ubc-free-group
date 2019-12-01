#pragma once
#include "BarResElement.h"

template<typename Numeric>
class BarResElementGenerator	{
public:
	virtual BarResElement<Numeric> nextElement(int elementMaxlength, int wordMaxlength, int expMax, int maxKoeff, int degree) = 0;

};

