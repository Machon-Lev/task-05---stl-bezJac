#include "Coordinate.h"

Coordinate::Coordinate() : _x(0), _y(0) {}

Coordinate::Coordinate(double x, double y) : _x(x), _y(y) {}

bool Coordinate::operator<(const Coordinate& other) const {
	if (_x < other._x) {
		return true;
	}
	else if (_x > other._x) {
		return false;
	}
	else {
		return _y < other._y;
	}
}

bool Coordinate::operator!=(const Coordinate other) const
{
	return _x != other._x && _y != other._y;
}