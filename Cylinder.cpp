#include "Cylinder.h"
#include <cmath>

bool Cylinder::intersect (const Ray& ray, double& t)
{
	Point p0 (ray.origin.x-center.x, ray.origin.y-center.y, ray.origin.z-center.z);
	double a = ray.direction.x*ray.direction.x+ray.direction.z*ray.direction.z;
	double b = ray.direction.x*p0.x +ray.direction.z*p0.z;
	double c = p0.x*p0.x+p0.z*p0.z-radius*radius;

	double delta = b*b - a*c;
	if (delta < 0)
		return false;

	t = (-b - sqrt (delta))/a;
	double epsilon = 0.00000001;
	if (t<=epsilon)
		return false;

	
	double y = p0.y+t*ray.direction.y;

	if (y > height+epsilon || y < -epsilon) {
		double dist;
		bool b1 = intersect_base (ray, Vector(0,1,0), center2, dist);
		if(b1) t=dist;
		bool b2 = intersect_base (ray, Vector(0,-1,0), center, dist);
		if(b2 && dist>epsilon && t>=dist)
			t=dist;
		return b1 || b2;
	}

	return true;

}

bool Cylinder::intersect_base (const Ray& ray, Vector normal, const Point& c, double& t)
{

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

Vector Cylinder::normal_in (const Point& p)
{
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
	{
	 	Point c0 (center.x, p.y, center.z);
	 	Vector v = p-c0;
	 	v.normalize ();
	 	return v;
	}
}