#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Material.h"

// Represents an intersection of a ray with an object
class Intersection
{
	public:
		//point of intersection
		Point point;
		//normal in the intersection point
		Vector normal;
		//material of the object
		Material material;
};

#endif