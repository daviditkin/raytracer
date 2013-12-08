#include "Cone.h"
#include <cmath>

bool Cone::intersect (const Ray& ray, double& t)
{
	Point p0 (ray.origin.x-center.x, ray.origin.y-center.y-height, ray.origin.z-center.z);
	double a = cosAlphaSq*ray.direction.x*ray.direction.x+cosAlphaSq*ray.direction.z*ray.direction.z-sinAlphaSq*ray.direction.y*ray.direction.y;
	double b = cosAlphaSq*ray.direction.x*p0.x +cosAlphaSq*ray.direction.z*p0.z-sinAlphaSq*ray.direction.y*p0.y;
	double c = cosAlphaSq*p0.x*p0.x+cosAlphaSq*p0.z*p0.z-sinAlphaSq*p0.y*p0.y;

	double delta = b*b - a*c;
	if (delta < 0)
		return false;

	t = (-b - sqrt (delta))/a;
	double epsilon = 0.00000001;
	if (t<epsilon)
		return false;

	double y = p0.y+t*ray.direction.y;

	if (y < -height-epsilon || y > epsilon)
		return false;

	return true;
}

Vector Cone::normal_in (const Point& p)
{
 	Point c0 (center.x, p.y, center.z);
 	Point c1 (center.x, center.y+height, center.z);
 	Vector v = p-center;
 	v.y = 0;
 	v.normalize ();
 	Vector n;
 	n.x = v.x*height/radius;
 	n.z = v.z*height/radius;
 	n.y = radius/height;
 	return n;
}