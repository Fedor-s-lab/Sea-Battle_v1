#include "Ship.h"
#include "ShipPosition.h"
#include "Point.h"
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
using namespace std;
Ship::Ship() {
	size = 1;
	x = 0;
	y = 0;
	direction = 'N';
}
Ship::Ship(int value) {
	srand(time(0));
	size = value;
	x = 0;
	y = 0;
	direction = 'N'; // non direction
	switch (size) {
	case 1:
		x = (rand() % 9);
		y = (rand() % 9);
		break;
	case 2:
		x = (rand() % 8);
		y = (rand() % 8);
		direction = 'D'; // down direction
		break;
	case 3:
		x = (rand() % 7);
		y = (rand() % 7);
		direction = 'D'; // down direction
		break;
	case 4:
		x = (rand() % 6);
		y = (rand() % 6);
		direction = 'R'; // right direction
		break;
	}
}
Ship::~Ship() {}
void Ship::Add_on_field_1(char gf[10][10]) const
{
	switch (direction) {
	case 'N':
		gf[x][y] = 'K';
		break;
	case 'D':
		for (int i = 0; i < size; i++) gf[x + i][y] = 'K';
		break;
	case 'R':
		for (int i = 0; i < size; i++) gf[x][y + i] = 'K';
		break;
	}
}