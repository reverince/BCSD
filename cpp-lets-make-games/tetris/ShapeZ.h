#pragma once
#include "Shape.h"

class ShapeZ : public Shape
{
public:

	ShapeZ();
	~ShapeZ();

	virtual bool init();
	virtual void rotate();
};
