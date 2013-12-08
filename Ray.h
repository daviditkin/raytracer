#ifndef RAY_H
#define RAY_H
#include <iostream>
using namespace std;
#include "Vector.h"

// A single ray with an origin a direction
// and the refractive coefficient of the material
// it is travelling in
class Ray
{
	public:
		Point origin;
		Vector direction;
		bool debug;
		//Refractive index of material it is travelling in
		double kR;
		Ray (Point& o, Vector dir, double kr = 1.0, bool d = false)
		 : origin (o), direction (dir), debug (d), kR (kr) { direction.normalize (); }
};

#endif