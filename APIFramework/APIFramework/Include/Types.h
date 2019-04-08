#pragma once
#include "Flag.h"
#include <vector>

typedef struct Resolution
{
	unsigned int w, h;

	Resolution() : w(0), h(0) { }
	Resolution(UINT _w, UINT _h) : w(_w), h(_h) { }
} RESOLUTION;

typedef struct Position
{
	float x, y;

	Position() : x(0.f), y(0.f) { }
	Position(float _x, float _y) : x(_x), y(_y) { }
	Position(const Position & pos) { x = pos.x; y = pos.y; }
	Position(const POINT & pt) { x = (float)pt.x; y = (float)pt.y; }

	// = 오버라이딩
	void operator = (const Position & pos) { x = pos.x; y = pos.y; }
	void operator = (const POINT & pt) { x = (float)pt.x; y = (float)pt.y; }

	// + 오버라이딩
	Position operator + (const Position & pos) const
	{
		Position ret;
		ret.x = x + pos.x;
		ret.y = y + pos.y;
		return ret;
	}
	Position operator + (const POINT & pt) const
	{
		Position ret;
		ret.x = x + (float)pt.x;
		ret.y = y + (float)pt.y;
		return ret;
	}

	// += 오버라이딩
	void operator += (const Position & pos) { x = x + pos.x; y = y + pos.y; }
	void operator += (const POINT & pt) { x = x + (float)pt.x; y = y + (float)pt.y; }

	// -= 오버라이딩
	void operator -= (const Position & pos) { x = x - pos.x; y = y - pos.y; }
	void operator -= (const POINT & pt) { x = x - (float)pt.x; y = y - (float)pt.y; }

	// - 오버라이딩
	Position operator - (const Position & pos) const
	{
		Position ret;
		ret.x = x - pos.x;
		ret.y = y - pos.y;
		return ret;
	}
	Position operator - (const POINT & pt) const
	{
		Position ret;
		ret.x = x - (float)pt.x;
		ret.y = y - (float)pt.y;
		return ret;
	}

	// * 오버라이딩
	Position operator * (const Position & pos) const
	{
		Position ret;
		ret.x = x * pos.x;
		ret.y = y * pos.y;
		return ret;
	}
	Position operator * (const POINT & pt) const
	{
		Position ret;
		ret.x = x * (float)pt.x;
		ret.y = y * (float)pt.y;
		return ret;
	}
	Position operator * (float f) const
	{
		Position ret;
		ret.x = x * f;
		ret.y = y * f;
		return ret;
	}

	// 나눗셈 오버라이딩
	Position operator / (const Position & pos) const
	{
		Position ret;
		ret.x = x / pos.x;
		ret.y = y / pos.y;
		return ret;
	}
	Position operator / (const POINT & pt) const
	{
		Position ret;
		ret.x = x / (float)pt.x;
		ret.y = y / (float)pt.y;
		return ret;
	}
} POSITION, _SIZE;

typedef struct Rectangle
{
	float l, t, r, b;

	Rectangle() : l(0.f), t(0.f), r(0.f), b(0.f) { }
	Rectangle(float _l, float _t, float _r, float _b) : l(_l), t(_t), r(_r), b(_b) { }
} RECTANGLE;

typedef struct Circle
{
	POSITION p;
	float r;

	Circle() : p(0.f, 0.f), r(0.f) { }
} CIRCLE;

typedef struct Pixel
{
	UCHAR r, g, b;
} PIXEL;

typedef struct AnimationClip
{
	ANIMATION_TYPE type;
	ANIMATION_OPTION option;
	std::vector<class Texture *> textures;
	float time;
	float timeMax;
	float timeFrame;
	float optionTime;
	float optionTimeMax;
	int frameX, frameY;
	int frameMaxX, frameMaxY;
	int startX, startY, lengthX, lengthY;
	_SIZE sizeFrame;
} ANIMATIONCLIP;
