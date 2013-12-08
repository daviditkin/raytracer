#ifndef FLOOR_H
#define FLOOR_H
#include "Rect.h"

class Floor : public Rect
{
	public:
		Material material2;
		int sq_w;
		int sq_h;
		Floor (const Point& p1, const Point& p2, const Point& p3, const Point& p4, int w=6, int h=20)
		: Rect (p1,p2,p3,p4)
		{
			sq_w = w;
			sq_h = h;
		}

		Floor (Point ps[], int w=6, int h=20)
		: Rect (ps)
		{
			sq_w = w;
			sq_h = h;
		}

		Material get_material (const Point& p)
		{
			double dx = xMax-xMin;
			double dz = zMax-zMin;
			double w = dx/sq_w;
			double h = dz/sq_h;
			if ((int)((p.x-xMin)/w)% 2 == 0)
			{
				if ((int)((p.z-zMin)/h)% 2 == 0)
					return material;
				else
					return material2;
			} else
			{
				if ((int)((p.z-zMin)/h)% 2 == 0)
					return material2;
				else
					return material;
			}
		}
};

#endif