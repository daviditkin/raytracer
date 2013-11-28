#ifndef OBJECT_H
#define OBJECT_H
#include "Matrix.h"
#include "Ray.h"
#include "Intersection.h"
#include "Material.h"

class Object
{
	public:
		Material material;
		virtual bool intersect (double& t, Matrix& m) = 0;
		virtual Vector normal_in (const Point& p) = 0;
};

#endif