#include "Cone.h"
#include <cmath>

// Calculate intersection with the infinite cone with
// its top vertex in the origin, by using the ray we would have
// if we would translate the cone to have the vertex in the origin
bool Cone::intersect (const Ray& ray, double& t)
{
	// translate ray origin so that the cone vertex would be at the origin
	Point p0 (ray.origin.x-center.x, ray.origin.y-center.y-height, ray.origin.z-center.z);

	// coefficients for the intersection equation
	// got them mathematically intersecting the line equation with the cone equation
	double a = cosAlphaSq*ray.direction.x*ray.direction.x+cosAlphaSq*ray.direction.z*ray.direction.z-sinAlphaSq*ray.direction.y*ray.direction.y;
	double b = cosAlphaSq*ray.direction.x*p0.x +cosAlphaSq*ray.direction.z*p0.z-sinAlphaSq*ray.direction.y*p0.y;
	double c = cosAlphaSq*p0.x*p0.x+cosAlphaSq*p0.z*p0.z-sinAlphaSq*p0.y*p0.y;

	double delta = b*b - a*c;

	//use epsilon because of computation errors between doubles
	double epsilon = 0.00000001;

	// delta < 0 means no intersections
	if (delta < epsilon)
		return false;

	// nearest intersection
	t = (-b - sqrt (delta))/a;

	// t<0 means the intersection is behind the ray origin
	// which we don't want
	if (t<epsilon)
		return false;

	double y = p0.y+t*ray.direction.y;

	// if the intersection with the cone is lower than
	// the base of the cone (y<-height) or higher than the vertex (y>0)
	// it's not actually intersecting our cone
	// We use epsilon because of errors when doing operations with doubles
	if (y < -height-epsilon || y > epsilon)
		return false;

	return true;
}

// Calculate normal in a point p of the surface
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