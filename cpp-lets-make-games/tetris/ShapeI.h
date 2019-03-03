#pragma once
#include "Shape.h"

class ShapeI : public Shape
{
public:

	ShapeI();
	~ShapeI();

	virtual bool init();
	virtual void rotate();
};
