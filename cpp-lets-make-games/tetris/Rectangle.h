#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle();
	~Rectangle();

	virtual bool init();
};
