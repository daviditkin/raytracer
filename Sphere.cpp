#include "Sphere.h"
#include <cmath>

bool Sphere::intersect (double& t, Matrix& m)
{
	Point c = m*center;
	double delta = radius*radius - c.x*c.x-c.y*c.y;
	if (delta < 0)
		return false;

	t = c.z - sqrt (delta);
}

Vector Sphere::normal_in (const Point& p)
{
	Vector v ((p.x-center.x)/radius, (p.y-center.y)/radius, (p.z-center.z)/radius);
	v.normalize ();
	return v;
}