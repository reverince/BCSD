#pragma once
#include "value.h"

class Stage
{
	char stage[STAGE_HEIGHT][STAGE_WIDTH];
	int speed;

	Stage();
	~Stage();

	friend class StageManager;

public:

	int getSpeed() const { return speed; }
	void setSpeed(int _speed) { speed = _speed; }

	void addBlock(class Shape * pShape);
	bool isBlock(int y, int x);

	bool init();
	void render();
};
