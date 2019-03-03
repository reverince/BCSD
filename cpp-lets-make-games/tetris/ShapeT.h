#pragma once
#include "Shape.h"

class ShapeT : public Shape
{
public:

	ShapeT();
	~ShapeT();

	virtual bool init();
	virtual void rotate();
};
