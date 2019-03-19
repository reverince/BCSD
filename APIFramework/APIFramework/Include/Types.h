#pragma once
#include <Windows.h>

struct Resolution
{
	unsigned int w, h;
};

typedef struct Position
{
	float x, y;

	Position() :
		x(0.f), y(0.f)
	{ }
	Position(float _x, float _y) :
		x(_x), y(_y)
	{ }
	Position(const Position & pos)
	{
		x = pos.x;
		y = pos.y;
	}
	Position(const POINT & pt)
	{
		x = (float)pt.x;
		y = (float)pt.y;
	}

	// = 오버라이딩
	void operator = (const Position & pos)
	{
		x = pos.x;
		y = pos.y;
	}
	void operator = (const POINT & pt)
	{
		x = (float)pt.x;
		y = (float)pt.y;
	}
	void operator = (float f[2])
	{
		x = f[0];
		y = f[1];
	}
	void operator = (float f)
	{
		x = f;
		y = f;
	}

	// + 오버라이딩
	Position operator + (const Position & pos)
	{
		Position ret;
		ret.x = x + pos.x;
		ret.y = y + pos.y;
		return ret;
	}
	Position operator + (const POINT & pt)
	{
		Position ret;
		ret.x = x + (float)pt.x;
		ret.y = y + (float)pt.y;
		return ret;
	}
	Position operator + (float f[2])
	{
		Position ret;
		ret.x = x + f[0];
		ret.y = y + f[1];
		return ret;
	}
	Position operator + (float f)
	{
		Position ret;
		ret.x = x + f;
		ret.y = y + f;
		return ret;
	}

	// - 오버라이딩
	Position operator - (const Position & pos)
	{
		Position ret;
		ret.x = x - pos.x;
		ret.y = y - pos.y;
		return ret;
	}
	Position operator - (const POINT & pt)
	{
		Position ret;
		ret.x = x - (float)pt.x;
		ret.y = y - (float)pt.y;
		return ret;
	}
	Position operator - (float f[2])
	{
		Position ret;
		ret.x = x - f[0];
		ret.y = y - f[1];
		return ret;
	}
	Position operator - (float f)
	{
		Position ret;
		ret.x = x - f;
		ret.y = y - f;
		return ret;
	}

	// * 오버라이딩
	Position operator * (const Position & pos)
	{
		Position ret;
		ret.x = x * pos.x;
		ret.y = y * pos.y;
		return ret;
	}
	Position operator * (const POINT & pt)
	{
		Position ret;
		ret.x = x * (float)pt.x;
		ret.y = y * (float)pt.y;
		return ret;
	}
	Position operator * (float f[2])
	{
		Position ret;
		ret.x = x * f[0];
		ret.y = y * f[1];
		return ret;
	}
	Position operator * (float f)
	{
		Position ret;
		ret.x = x * f;
		ret.y = y * f;
		return ret;
	}

	// 나눗셈 오버라이딩
	Position operator / (const Position & pos)
	{
		Position ret;
		ret.x = x / pos.x;
		ret.y = y / pos.y;
		return ret;
	}
	Position operator / (const POINT & pt)
	{
		Position ret;
		ret.x = x / (float)pt.x;
		ret.y = y / (float)pt.y;
		return ret;
	}
	Position operator / (float f[2])
	{
		Position ret;
		ret.x = x / f[0];
		ret.y = y / f[1];
		return ret;
	}
	Position operator / (float f)
	{
		Position ret;
		ret.x = x / f;
		ret.y = y / f;
		return ret;
	}
} POSITION, _SIZE;
