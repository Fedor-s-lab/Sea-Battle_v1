#include <iostream>
#include <cstdlib>
#pragma once
class Point
{
private:
	int x_k, y_k; // x_k - row , y_k - column
public:
	Point(int x, int y) {
		x_k = x;
		y_k = y;
	}
	~Point() {};
	int givePoint_x() const {
		return x_k;
	}
	int givePoint_y() const {
		return y_k;
	}
};
