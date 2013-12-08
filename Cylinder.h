#ifndef CYLINDER_H
#define CYLINDER_H
#include "Vector.h"
#include "Object.h"

// A cylinder object
class Cylinder : public Object
{
	public:
		// center of the bottom base
		Point center;
		// center of the top base
		Point center2;
		// radius of the bases
		double radius;
		// height of the cylinder
		double height;

		// See implementations for comments

		Cylinder (const Point& c, double h, double r) : center (c), height (h), radius (r) {center2.set (c.x,c.y+height,c.z);}
		Cylinder (double x, double y, double z, double h, double r) : center (Point (x, y, z)), height (h), radius (r) {center2.set (x,y+height,z);}
		
		bool intersect (const Ray& ray, double& t);
		bool intersect_base (const Ray& ray, const Point& p, double& t);
		Vector normal_in (const Point& p);
		Material get_material (const Point& p) { return material; }
};

#endif