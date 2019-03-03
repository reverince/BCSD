#pragma once
#include "Shape.h"

class ShapeL : public Shape
{
public:

	ShapeL();
	~ShapeL();

	virtual bool init();
	virtual void rotate();
};
