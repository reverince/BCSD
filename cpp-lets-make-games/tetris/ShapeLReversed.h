#pragma once
#include "Shape.h"

class ShapeLReversed : public Shape
{
public:

	ShapeLReversed();
	~ShapeLReversed();

	virtual bool init();
	virtual void rotate();
};

