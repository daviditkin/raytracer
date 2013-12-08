#ifndef OBJECT_H
#define OBJECT_H
#include "Ray.h"
#include "Intersection.h"
#include "Material.h"

// abstract class representing an object in the scene
// Sphere, Rect, Floor, Cone and Cylinder are all subclasses of this
class Object
{
	public:
		Material material;
		virtual bool intersect (const Ray& ray, double& t) = 0;
		virtual Vector normal_in (const Point& p) = 0;
		virtual Material get_material (const Point& p) = 0;
};

#endif