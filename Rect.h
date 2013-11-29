#ifndef RECT_H
#define RECT_H
#include "Object.h"
#include <vector>
using namespace std;

class Rect : public Object
{
	public:
		vector<Point> points;
		Vector normal;
		double xMax, xMin, yMax, yMin, zMax, zMin;
		Rect (const Point& p1, const Point& p2, const Point& p3, const Point& p4)
		{
			points.push_back (p1);
			points.push_back (p2);
			points.push_back (p3);
			points.push_back (p4);
			calculate_normal ();
			calculate_bounds ();
		}
		Rect (Point ps[])
		{
			points.push_back (ps[0]);
			points.push_back (ps[1]);
			points.push_back (ps[2]);
			points.push_back (ps[3]);
			calculate_normal ();
			calculate_bounds ();
		}
		bool intersect (const Ray& ray, double& t);
		Vector normal_in (const Point& p);
	private:
		void calculate_normal ();
		void calculate_bounds ();
};

#endif