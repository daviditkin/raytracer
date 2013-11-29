#include "Scene.h"
#include "Transformation.h"
#include <iostream>
using namespace std;

Intensity Scene::raytrace (Ray& ray, int depth)
{
	int obj_ind = -1;
	double closest = -1;

	double t = -1;
	for (int i=0;i<objects.size ();i++)
	{
		bool intersect = objects[i]->intersect (ray, t);
		if (intersect && (t<closest || closest == -1))
		{
			closest = t;
			obj_ind = i;
		}
	}


	Intensity retVal;
	if (obj_ind >=0) {
		Intersection intersection;
		intersection.point.x = ray.origin.x + closest*ray.direction.x;
		intersection.point.y = ray.origin.y + closest*ray.direction.y;
		intersection.point.z = ray.origin.z + closest*ray.direction.z;
		intersection.normal = objects[obj_ind]->normal_in (intersection.point);
		retVal = shade (obj_ind, ray, intersection, depth);
	}
	
	return retVal;
}

Intensity Scene::shade (int obj_index, Ray& ray, Intersection& intersection, int depth)
{
	Intensity retVal = iA*objects[obj_index]->material.kA;

	if (depth > MAX_DEPTH)
		return retVal;

	Vector L = iP.position - intersection.point;
	L.normalize ();
	Vector R = reflect (L, intersection.normal);
	Vector V = cop - intersection.point;
	V.normalize ();
	
	retVal = retVal + lighting_model (obj_index, L*intersection.normal, R*V);
	
	return retVal;
}

Intensity Scene::lighting_model (int obj, double costTheta, double cosAlpha)
{
	double cosAlphaN = pow (cosAlpha, objects[obj]->material.n);
	Intensity i = iP*(objects[obj]->material.kD*costTheta);// + objects[obj]->material.kS*cosAlphaN);
	i.clamp ();
	return i;
}

Vector Scene::reflect (Vector& v, Vector& normal)
{
	// Vector retVal = (2*(normal*v)*normal - v);
	// retVal.normalize ();

	Vector vPrime = v / (v*normal);
	Vector retVal = vPrime + 2*normal;
	retVal.normalize ();
	return retVal;
}

void Scene::set_ambient (Intensity i)
{
	iA = i;
}

void Scene::set_pls (Point p, Intensity i)
{
	iP.position = p;
	iP.intensity = i;
}