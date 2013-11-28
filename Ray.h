#ifndef RAY_H
#define RAY_H
#include "Vector.h"

class Ray
{
	public:
		Point origin;
		Vector direction;
		//Refractive index of material it is travelling in
		float kR;
		Ray (Point& o, Vector dir) : origin (o), direction (dir) {}
};

#endif