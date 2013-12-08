#include "Cylinder.h"
#include <cmath>

// Find intersection with infinite cylinder with center in the origin
// to do that, translate the ray origin so that the center of the bottom base
// is at the origin, then calculate intersection with the canonical infinite cylinder
// and check if the ray intersects the lateral surface of the cylinder within our
// bases, if not check if it's intersecting the bases and if not, it's not intersecting
// our actual cylinder
bool Cylinder::intersect (const Ray& ray, double& t)
{
	// translate the ray origin
	Point p0 (ray.origin.x-center.x, ray.origin.y-center.y, ray.origin.z-center.z);

	// coefficients for the intersection equation
	// got them mathematically intersecting the line equation with the cylinder equation
	double a = ray.direction.x*ray.direction.x+ray.direction.z*ray.direction.z;
	double b = ray.direction.x*p0.x +ray.direction.z*p0.z;
	double c = p0.x*p0.x+p0.z*p0.z-radius*radius;

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
	if (t<=epsilon)
		return false;

	
	double y = p0.y+t*ray.direction.y;

	// check if we intersect one of the bases
	if (y > height+epsilon || y < -epsilon) {
		double dist;
		bool b1 = intersect_base (ray, center2, dist);
		if(b1) t=dist;
		bool b2 = intersect_base (ray, center, dist);
		if(b2 && dist>epsilon && t>=dist)
			t=dist;
		return b1 || b2;
	}

	return true;

}

// Calculate intersection with the base having center c
// We do this by calculating the intersection with the plane
// and then checking if the intersection is within the base circle
bool Cylinder::intersect_base (const Ray& ray, const Point& c, double& t)
{
	Vector normal = normal_in (c);
	Point p0 (ray.origin.x-center.x, ray.origin.y-center.y, ray.origin.z-center.z);
	double A = normal[0];
	double B = normal[1];
	double C = normal[2];
	double D = - (A*(c.x-center.x) +B*(c.y-center.y)+C*(c.z-center.z));

	if (A*ray.direction[0]+B*ray.direction[1]+C*ray.direction[2]==0)
		return false;
	
	double dist = - (A*p0.x+B*p0.y+C*p0.z+D)/(A*ray.direction[0]+B*ray.direction[1]+C*ray.direction[2]);

	double epsilon = 0.00000001;
	if (dist < epsilon)
		return false;

	Point p;
	p.x = p0.x+dist*ray.direction[0];
	p.y = p0.y+dist*ray.direction[1];
	p.z = p0.z+dist*ray.direction[2];
	if (p.x*p.x+p.z*p.z-radius*radius > epsilon)
		return false;

	t = dist;
	return true;
}

// Calculate the normal in a point on the surface
// it is a vertical vector in the bases and a vector
// having the direction of the vector from the axis to the point
Vector Cylinder::normal_in (const Point& p)
{
	// Point is on one of the bases
	if (p.x<center.x+radius && p.x>center.x-radius && p.z<center.z+radius && p.z>center.z-radius)
	{
		double epsilon = 0.00000001;
		if (p.y < center.y+height+epsilon && p.y>center.y+height-epsilon){
			return Vector (0,1,0);
		}
		if (p.y < center.y+epsilon && p.y>center.y-epsilon){
			return Vector (0,-1,0);
		}
	}

	// Point is on lateral surface
 	Point c0 (center.x, p.y, center.z);
 	Vector v = p-c0;
 	v.normalize ();
 	return v;
}