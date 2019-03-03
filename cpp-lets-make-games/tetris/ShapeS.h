#pragma once
#include "Shape.h"

class ShapeS : public Shape
{
public:

	ShapeS();
	~ShapeS();

	virtual bool init();
	virtual void rotate();
};
