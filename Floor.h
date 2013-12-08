#ifndef FLOOR_H
#define FLOOR_H
#include "Rect.h"

// Represents the floor, made up of squares of different colors
class Floor : public Rect
{
	public:
		// material of the second type of square
		// the first one is coming from the base class Rect
		Material material2;
		//number of squares in the width direction
		int sq_w;
		// ..and height direction
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

		// Get material depending on the point of intersection
		// so that we can have squares of different colors
		// This resembles texture mapping in some aspects
		Material get_material (const Point& p)
		{
			double dx = xMax-xMin;
			double dz = zMax-zMin;
			double w = dx/sq_w;
			double h = dz/sq_h;
			double epsilon = 0.0000001;
			if ((int)((p.x-xMin)/w) % 2 == 0)
			{

				for(int i=0;i<sq_h;i++)
				{
					if((p.z-zMin) > i*sq_h+epsilon && (p.z-zMin)<(i+1)*sq_h-epsilon)
						if(i%2==0)
							return material2;
						else
							return material;
				}
				// if ((int)((p.z-zMin)/h) % 2 == 0)
				// 	return material;
				// else
				// 	return material2;
			} else
			{

				for(int i=0;i<sq_h;i++)
				{
					if((p.z-zMin) > i*sq_h+epsilon && (p.z-zMin)<(i+1)*sq_h-epsilon)
						if(i%2==0)
							return material2;
						else
							return material;
				}
				// if ((int)((p.z-zMin)/h) % 2 == 0)
				// 	return material2;
				// else
				// 	return material;
			}
		}
};

#endif