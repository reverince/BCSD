#include "pch.h"
#include <iostream>
using namespace std;

struct Point {
	int x, y;

	Point() : x(0), y(0) { };
	Point(int _x, int _y) : x(_x), y(_y) { };

	Point operator+(const Point &pt) {
		Point res;
		res.x = x + pt.x;
		res.y = y + pt.y;
		return res;
	}

	bool operator==(const Point &pt) {
		return (x == pt.x && y == pt.y);
	}
};

int main()
{
	Point a(1, 3), b(1, 3);

	cout << (a == b) << '\n';

	return 0;
}
