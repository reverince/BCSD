#include "pch.h"
#include "ShapeI.h"

ShapeI::ShapeI()
{
}

ShapeI::~ShapeI()
{
}

bool ShapeI::init()
{
	if (!Shape::init()) return false;

	// ¡à¡à¡à¡à
	// ¡à¡à¡à¡à
	// ¡à¡à¡à¡à
	// ¡á¡á¡á¡á
	shape[3][0] = '1';
	shape[3][1] = '1';
	shape[3][2] = '1';
	shape[3][3] = '1';

	widthCount = 4;

	pivot.y = 0;
	pivot.x = 0;

	return true;
}

void ShapeI::rotate()
{
	dir = (dir == RD_UP) ? RD_RIGHT : RD_UP;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			shape[i][j] = '0';
		}
	}

	switch (dir) {
	case RD_UP:
		shape[3][0] = '1';
		shape[3][1] = '1';
		shape[3][2] = '1';
		shape[3][3] = '1';
		break;
	case RD_RIGHT:
		shape[0][0] = '1';
		shape[0][1] = '1';
		shape[0][2] = '1';
		shape[0][3] = '1';
		break;
	}
}