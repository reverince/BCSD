#include "pch.h"
#include "Rectangle.h"

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}

bool Rectangle::init()
{
	if (!Shape::init()) return false;

	// ¡à¡à¡à¡à
	// ¡à¡à¡à¡à
	// ¡á¡á¡à¡à
	// ¡á¡á¡à¡à
	shape[2][0] = '1';
	shape[2][1] = '1';
	shape[3][0] = '1';
	shape[3][1] = '1';

	widthCount = 2;

	pivot.y = 0;
	pivot.x = 0;

	return true;
}
