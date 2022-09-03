#include "Point.h"
#include "ShipPosition.h"
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#pragma once
class Ship
{
private:
	int size, x, y; // x - row , y - column
	char direction;
public:
	Ship();
	Ship(int value);
	~Ship();
	void Add_on_field_1(char gf[10][10]) const;
};
