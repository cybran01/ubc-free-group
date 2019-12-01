#pragma once
class INTERFACE_FILTER	{
public:
	virtual ~INTERFACE_FILTER();
	virtual bool accepted() = 0;
};

