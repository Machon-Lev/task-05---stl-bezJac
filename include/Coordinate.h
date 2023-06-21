#pragma once

/**
* @brief struct representing an (x,y) coordinate.
*/
struct Coordinate {

	double _x;
	double _y;

	Coordinate();
	Coordinate(double x, double y);
	bool operator<(const Coordinate& other) const;
	bool operator!=(const Coordinate& other) const;
};