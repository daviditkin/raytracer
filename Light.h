#ifndef LIGHT_H
#define LIGHT_H
#include "Point.h"
#include "Intensity.h"

// A light source, with a position and intensity
class Light
{
	public:
		Point position;
		Intensity intensity;
};

// Overload operators
Intensity operator* (const Light& l, const Coefficient& k);

Intensity operator* (const Coefficient& k, const Light& l);

Intensity operator* (const Light& l, const double a);

Intensity operator* (const double a, const Light& l);

#endif