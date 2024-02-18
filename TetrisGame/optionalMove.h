#pragma once
#include "point.h"

class optionalMove
{
	point* destination;
	int numOfRotations;

public:
	point* getDestination() const { return destination; }
	int getNumOfRotations() const { return numOfRotations; }
	void setDestination(point* dest) { destination = dest; }
	void setNumOfRotations(int num) { numOfRotations = num; }

	optionalMove& operator=(const optionalMove& other)
	{
		destination = other.getDestination();
		numOfRotations = other.getNumOfRotations();
		return *this;
	}
};

