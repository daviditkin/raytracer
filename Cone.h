#ifndef CONE_H
#define CONE_H
#include "Vector.h"
#include "Object.h"

class Cone : public Object
{
	public:
		double cosAlphaSq;
		double sinAlphaSq;
		Point center;
		double height;
		double radius;
		Cone (const Point& c, double h, double r) : center (c), height (h), radius (r) { calculateAngle ();}
		Cone (double x, double y, double z, double h, double r) : center (Point (x, y, z)), height (h), radius (r) { calculateAngle ();}
		bool intersect (const Ray& ray, double& t);
		Vector normal_in (const Point& p);
		Material get_material (const Point& p) { return material; }

		void calculateAngle ()
		{
			Point p1 (center.x+radius, center.y, center.z);
			Point p2 (center.x, center.y+height, center.z);
			double d = (p2-p1).length ();
			cosAlphaSq = height/d;
			sinAlphaSq = radius/d;
		}
};

#endif