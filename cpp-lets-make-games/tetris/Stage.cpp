#include "pch.h"
#include "Core.h"
#include "Stage.h"
#include "Shape.h"

Stage::Stage() :
	speed(2)
{
}

Stage::~Stage()
{
}

void Stage::addBlock(Shape * pShape)
{
	Position pos = pShape->getPos();
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (pos.y - (3 - i) >= STAGE_HEIGHT || pos.x + j >= STAGE_WIDTH)
				continue;
			if (pShape->getBlock(i, j) == '1') {
				stage[pos.y - (3 - i)][pos.x + j] = '1';
			}
		}
	}
}

bool Stage::isBlock(int y, int x)
{
	if (y >= STAGE_HEIGHT) return true;
	if (x < 0 || x >= STAGE_WIDTH) return true;

	return (stage[y][x] == '1');
}

bool Stage::init()
{
	// stage 0으로 초기화
	memset(stage, 0, STAGE_HEIGHT * STAGE_WIDTH);

	return true;
}

void Stage::render()
{
	for (int i = 0; i < STAGE_HEIGHT + 1; ++i) {
		for (int j = 0; j < STAGE_WIDTH + 2; ++j) {
			if (i == STAGE_HEIGHT || j == 0 || j == STAGE_WIDTH + 1)
				cout << "■";  // 바깥 테두리
			else if (stage[i][j - 1] == '1')
				cout << "■";
			else
				cout << "  ";
		}
		cout << '\n';
	}

	for (int i = 0; i < 7; ++i) {
		Core::getInst()->setConsolePos(i, 17);
		cout << "■";
	}
	for (int i = 0; i < 6; ++i) {
		Core::getInst()->setConsolePos(6, 11 + i);
		cout << "■";
	}
}
