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
		virtual bool intersect (const Ray& ray, double& t) = 0;
		virtual Vector normal_in (const Point& p) = 0;
		virtual Material get_material (const Point& p) = 0;
};

#endif