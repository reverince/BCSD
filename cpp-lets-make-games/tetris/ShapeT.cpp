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
		// ¡à¡à¡à¡à
		// ¡à¡à¡à¡à
		// ¡á¡á¡á¡à
		// ¡à¡á¡à¡à	
		shape[2][0] = '1';
		shape[2][1] = '1';
		shape[3][2] = '1';
		shape[3][1] = '1';
		widthCount = 3;
		break;
	case RD_RIGHT:
		// ¡à¡à¡à¡à
		// ¡à¡á¡à¡à
		// ¡á¡á¡à¡à
		// ¡à¡á¡à¡à	
		shape[1][0] = '1';
		shape[2][0] = '1';
		shape[2][1] = '1';
		shape[3][1] = '1';
		widthCount = 2;
		break;
	case RD_DOWN:
		// ¡à¡à¡à¡à
		// ¡à¡à¡à¡à
		// ¡à¡á¡à¡à	
		// ¡á¡á¡á¡à
		shape[2][1] = '1';
		shape[3][0] = '1';
		shape[3][1] = '1';
		shape[3][2] = '1';
		widthCount = 3;
		break;
	case RD_LEFT:
		// ¡à¡à¡à¡à
		// ¡á¡à¡à¡à
		// ¡á¡á¡à¡à
		// ¡á¡à¡à¡à	
		shape[1][0] = '1';
		shape[2][0] = '1';
		shape[2][1] = '1';
		shape[3][0] = '1';
		widthCount = 2;
		break;
	}
}
