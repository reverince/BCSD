#pragma once
#include "value.h"

class Shape
{
protected:

	char shape[4][4];
	int widthCount;
	int dir;
	Position pos;

public:

	Shape();
	virtual ~Shape();

	char getBlock(int y, int x) const { return shape[y][x]; };
	void setPos(int y, int x) { pos.y = y; pos.x = x; }
	void setPos(const Position & _pos) { pos = _pos; }
	Position getPos() const { return pos; }

	virtual bool init();
	virtual void rotate();

	void render();
	void renderNext();
	bool moveDown();
	void moveLeft();
	void moveRight();
};
