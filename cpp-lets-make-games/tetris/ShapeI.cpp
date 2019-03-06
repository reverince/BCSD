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
		// ¡à¡à¡à¡à
		// ¡à¡à¡à¡à
		// ¡à¡à¡à¡à
		// ¡á¡á¡á¡á
		shape[3][0] = '1';
		shape[3][1] = '1';
		shape[3][2] = '1';
		shape[3][3] = '1';
		widthCount = 4;
		break;
	case RD_RIGHT:
		// ¡à¡á¡à¡à
		// ¡à¡á¡à¡à
		// ¡à¡á¡à¡à
		// ¡à¡á¡à¡à
		shape[1][0] = '1';
		shape[1][1] = '1';
		shape[1][2] = '1';
		shape[1][3] = '1';
		widthCount = 1;
		break;
	}
}