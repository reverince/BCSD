#pragma once

#include <iostream>
#include <cstdlib>
#include <list>
#include <time.h>
#include <Windows.h>
#include "macro.h"
#include "flag.h"

#define STAGE_HEIGHT 15
#define STAGE_WIDTH 10

using namespace std;

struct Position {
	int y, x;

	Position() : y(0), x(0) { }
	Position(const Position & pos) { *this = pos; }
	Position(int _y, int _x) : y(_y), x(_x) { }

	void operator=(const Position & pos) {
		y = pos.y;
		x = pos.x;
	}
	Position operator+(const Position & pos) {
		Position res;
		res.y = y + pos.y;
		res.x = x + pos.x;
		return res;
	}
	Position operator+(int i) {
		Position res;
		res.y = y + i;
		res.x = x + i;
		return res;
	}
	void operator+=(const Position & pos) {
		y += pos.y;
		x += pos.x;
	}
	Position operator-(const Position & pos) {
		Position res;
		res.y = y - pos.y;
		res.x = x - pos.x;
		return res;
	}
	Position operator-(int i) {
		Position res;
		res.y = y - i;
		res.x = x - i;
		return res;
	}
	void operator-=(const Position & pos) {
		y -= pos.y;
		x -= pos.x;
	}
};  // end of struct Position
