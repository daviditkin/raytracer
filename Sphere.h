#ifndef SPHERE_H
#define SPHERE_H
#include "Object.h"

class Sphere : public Object
{
	public:
		Point center;
		double radius;
		Sphere (const Point& c, double r) : center (c), radius (r) {}
		Sphere (double x, double y, double z, double r) : center (Point (x, y, z)), radius (r) {}
		bool intersect (double& t, Matrix& m);
		Vector normal_in (const Point& p);
};

#endif