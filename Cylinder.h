#ifndef CYLINDER_H
#define CYLINDER_H
#include "Vector.h"
#include "Object.h"

class Cylinder : public Object
{
	public:
		Point center;
		Point center2;
		double radius;
		double height;
		Cylinder (const Point& c, double h, double r) : center (c), height (h), radius (r) {center2.set (c.x,c.y+height,c.z);}
		Cylinder (double x, double y, double z, double h, double r) : center (Point (x, y, z)), height (h), radius (r) {center2.set (x,y+height,z);}
		bool intersect (const Ray& ray, double& t);
		bool intersect_base (const Ray& ray, Vector normal, const Point& p, double& t);
		Vector normal_in (const Point& p);
		Material get_material (const Point& p) { return material; }
};

#endif