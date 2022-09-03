#include "Point.h"
#include <iostream>
#include <cstdlib>
#pragma once
class ShipPosition
{
public:
	Point p;
	bool x_orient;
	ShipPosition() :p(0, 0) {
		x_orient = true;
	}
	ShipPosition(int x, int y, bool xo) :p(x, y) {
		x_orient = xo;
	}
	~ShipPosition() {};
};