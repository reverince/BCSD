#include "pch.h"
#include "ShapeZ.h"

ShapeZ::ShapeZ()
{
}

ShapeZ::~ShapeZ()
{
}

bool ShapeZ::init()
{
	if (!Shape::init()) return false;

	// ¡à¡à¡à¡à
	// ¡à¡à¡à¡à
	// ¡á¡á¡à¡à
	// ¡à¡á¡á¡à
	shape[2][0] = '1';
	shape[2][1] = '1';
	shape[3][1] = '1';
	shape[3][2] = '1';
	widthCount = 3;

	return true;
}

void ShapeZ::rotate()
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
		// ¡á¡á¡à¡à
		// ¡à¡á¡á¡à
		shape[2][0] = '1';
		shape[2][1] = '1';
		shape[3][1] = '1';
		shape[3][2] = '1';
		widthCount = 3;
		break;
	case RD_RIGHT:
		// ¡à¡à¡à¡à
		// ¡à¡á¡à¡à
		// ¡á¡á¡à¡à
		// ¡á¡à¡à¡à
		shape[1][1] = '1';
		shape[2][0] = '1';
		shape[2][1] = '1';
		shape[3][0] = '1';
		widthCount = 2;
		break;
	}
}
