#include "pch.h"
#include "ShapeS.h"

ShapeS::ShapeS()
{
}

ShapeS::~ShapeS()
{
}

bool ShapeS::init()
{
	if (!Shape::init()) return false;

	// กเกเกเกเ
	// กเกเกเกเ
	// กเกแกแกเ
	// กแกแกเกเ
	shape[2][1] = '1';
	shape[2][2] = '1';
	shape[3][0] = '1';
	shape[3][1] = '1';
	widthCount = 3;

	return true;
}

void ShapeS::rotate()
{
	dir = (dir == RD_UP) ? RD_RIGHT : RD_UP;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			shape[i][j] = '0';
		}
	}

	switch (dir) {
	case RD_UP:
		// กเกเกเกเ
		// กเกเกเกเ
		// กเกแกแกเ
		// กแกแกเกเ
		shape[2][1] = '1';
		shape[2][2] = '1';
		shape[3][0] = '1';
		shape[3][1] = '1';
		widthCount = 3;
		break;
	case RD_RIGHT:
		// กเกเกเกเ
		// กแกเกเกเ
		// กแกแกเกเ
		// กเกแกเกเ
		shape[1][0] = '1';
		shape[2][0] = '1';
		shape[2][1] = '1';
		shape[3][1] = '1';
		widthCount = 2;
		break;
	}
}
