#include "pch.h"
#include "StageManager.h"
#include "Stage.h"
#include "Shape.h"
#include "Core.h"

Shape::Shape()
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			shape[i][j] = '0';
		}
	}

	widthCount = 0;
	dir = RD_UP;
}

Shape::~Shape()
{
}

bool Shape::init()
{
	return true;
}

void Shape::render()
{
	for (int i = 0; i < 4; ++i) {
		int yIdx = pos.y - (3 - i);
		// 화면 위 잘린 부분 생략
		if (yIdx < 0) continue;

		for (int j = 0; j < 4; ++j) {
			if (pos.x + j >= STAGE_WIDTH) continue;

			// 출력 좌표 설정
			Core::getInst()->setConsolePos(yIdx, pos.x + j);

			if (shape[i][j] == '1')
				cout << "■";
		}
		cout << '\n';
	}
}

void Shape::renderNext()
{
	for (int i = 0; i < 4; ++i) {
		int yIdx = pos.y - (3 - i);
		for (int j = 0; j < 4; ++j) {
			// 출력 좌표 설정
			Core::getInst()->setConsolePos(yIdx, pos.x + j);

			if (shape[i][j] == '1')
				cout << "■";
		}
		cout << '\n';
	}
}

void Shape::rotate()
{
}


// 바닥에 닿은 경우 true 반환
bool Shape::moveDown()
{
	Stage * pStage = StageManager::getInst()->getCurStage();

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (shape[i][j] == '1') {
				if (pStage->isBlock(pos.y - (3 - i) + 1, pos.x + j)) {
					return true;
				}
			}
		}
	}

	++pos.y;

	return false;
}

void Shape::moveLeft()
{
	if (pos.x == 0) return;

	Stage * pStage = StageManager::getInst()->getCurStage();

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (shape[i][j] == '1') {
				if (pStage->isBlock(pos.y + (3 - i), pos.x + j - 1)) {
					return;
				}
			}
		}
	}

	--pos.x;
}

void Shape::moveRight()
{
	if (pos.x + widthCount == STAGE_WIDTH) return;

	Stage * pStage = StageManager::getInst()->getCurStage();

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (shape[i][j] == '1') {
				if (pStage->isBlock(pos.y + (3 - i), pos.x + j + 1)) {
					return;
				}
			}
		}
	}

	++pos.x;
}
