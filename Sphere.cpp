#include "Sphere.h"
#include <cmath>
#include <iostream>
using namespace std;

// Calculate intersection by translating the ray origin so that the center
// of the sphere is at the origin, so that calculations are simpler
bool Sphere::intersect (const Ray& ray, double& t)
{
	Point p (ray.origin.x - center.x, ray.origin.y - center.y, ray.origin.z - center.z);
	double b = p.x*ray.direction.x + p.y*ray.direction.y + p.z*ray.direction.z;
	double delta2 = b*b + radius*radius - p.x*p.x-p.y*p.y-p.z*p.z;

	double epsilon = 0.00000001;
	if (delta2 < epsilon)
		return false;

	double t1 = -b - sqrt (delta2);

	if (t1<=epsilon)
		return false;

	if(ray.debug)
		cout<<"t "<<t1<<endl;
	
	t = t1;
	return true;

 // 	Matrix m = Transformation::translation_matrix (-center.x, -center.y, -center.z);
	// Point p0 = m * ray.origin;
	// double b = ray.direction[0]*p0.x+ray.direction[1]*p0.y+ray.direction[2]*p0.z;
	// double delta = b*b;
	// delta -= p0.x*p0.x+p0.y*p0.y+p0.z*p0.z-radius*radius;

	// // No intersection
	// if (delta < 0)
	// 	return false;

	// double d = -b - sqrt (delta);
	// if (d < 0)
	// 	return false;
	// t=d;
	// return true;

	/*double a = ray.direction.length ();
	double dx = ray.origin.x-center.x;
	double dy = ray.origin.y-center.y;
	double dz = ray.origin.z-center.z;
	double b = ray.direction.x*dx+ray.direction.y*dy+ray.direction.z*dz;
	double c = dx*dx+dy*dy+dz*dz-radius*radius;

	double delta = b*b-a*c;
	if (delta<0)
		return false;

	double s1 = -b + sqrt (delta);
	double s2 = -b - sqrt (delta);

	if (s1<0.0001 && s2<0.0001)
		return false;
	else if (s1<0.0001 && s2>0.0001)
		t= s2;
	else if (s1>0.0001 && s2<0.0001)
		t=s1;
	else
		t= s1<s2? s1 : s2;
	return true;*/
}

// Calculate sphere normal
Vector Sphere::normal_in (const Point& p)
{
	Vector v ((p.x-center.x)/radius, (p.y-center.y)/radius, (p.z-center.z)/radius);
	v.normalize ();
	return v;
}

Material Sphere::get_material (const Point& p)
{
	return material;
}