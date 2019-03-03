#include "pch.h"
#include "ShapeT.h"

ShapeT::ShapeT()
{
}

ShapeT::~ShapeT()
{
}

bool ShapeT::init()
{
	if (!Shape::init()) return false;

	// ¡à¡à¡à¡à
	// ¡à¡à¡à¡à
	// ¡á¡á¡á¡à
	// ¡à¡á¡à¡à	
	shape[2][0] = '1';
	shape[2][1] = '1';
	shape[3][2] = '1';
	shape[3][1] = '1';

	widthCount = 3;

	pivot.y = 0;
	pivot.x = 0;

	return true;
}

void ShapeT::rotate()
{
	++dir;
	dir %= RD_END;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			shape[i][j] = '0';
		}
	}

	switch (dir) {
	case RD_UP:
		break;
	case RD_RIGHT:
		break;
	case RD_DOWN:
		break;
	case RD_LEFT:
		break;
	}
}
