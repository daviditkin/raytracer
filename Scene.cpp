#include "Scene.h"
#include "Transformation.h"
#include <iostream>
using namespace std;

Matrix Scene::intersection_matrix (const Ray& ray)
{
	Matrix t = Transformation::translation_matrix (-cop.x, -cop.y, -cop.z);

	double d = sqrt (ray.direction.x*ray.direction.x + ray.direction.z*ray.direction.z);
	Matrix y_rotation = Transformation::y_rotation_matrix (-ray.direction.z/d, ray.direction.x/d);

	d = sqrt (ray.direction.y*ray.direction.y + ray.direction.z*ray.direction.z);
	Matrix x_rotation = Transformation::x_rotation_matrix (-ray.direction.z/d, ray.direction.y/d);

	return y_rotation*x_rotation*t;
}

Intensity Scene::raytrace (const Ray& ray, int depth)
{
	int obj_ind = -1;
	double closest = -1;

	//find intersection
	Matrix m = intersection_matrix (ray);
	double t = -1;
	for (int i=0;i<objects.size ();i++)
	{
		bool intersect = objects[i]->intersect (t, m);
		if (intersect && (t<closest || closest == -1))
		{
			closest = t;
			obj_ind = i;
		}
	}

	Intensity retVal;
	if (obj_ind >0) {
		Intersection intersection;
		intersection.point.x = ray.origin + t*ray.direction.x;
		intersection.point.y = ray.origin + t*ray.direction.y;
		intersection.point.z = ray.origin + t*ray.direction.z;
		intersection.normal = objects[obj_ind]->normal_in (intersection.point);

		retVal = shade ();//obj_ind, ray, closest, depth);
	}
	
	return retVal;
}

Intensity Scene::shade ()//int obj_index, const Ray& ray, Intersection& intersection, int depth)
{

}