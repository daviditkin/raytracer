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
		intersection.material = objects[obj_ind]->get_material (intersection.point);
		retVal = shade (ray, intersection, depth);
	}
	
	return retVal;
}

Intensity Scene::shade (Ray& ray, Intersection& intersection, int depth)
{
	Intensity retVal = iA*intersection.material.kA;

	if (depth > MAX_DEPTH)
		return retVal;

	Vector L = iP.position - intersection.point;
	L.normalize ();
	Vector R = reflect (L, intersection.normal);
	Vector V = ray.origin - intersection.point;
	V.normalize ();

	Ray shadow (intersection.point, L);
	double t;
	Coefficient shadow_factor (1.0, 1.0, 1.0);
	for (int i = 0; i < objects.size (); ++i)
	{
		bool intersect = objects[i]->intersect (shadow, t);
		if (intersect)
		{
			shadow_factor.set (shadow_factor.r*(1-objects[i]->material.kT.r),
								shadow_factor.g*(1-objects[i]->material.kT.g),
								shadow_factor.b*(1-objects[i]->material.kT.b));
		}
	}
	
	Ray reflected (intersection.point, R);
	Intensity ref = raytrace (reflected, depth+1);

	retVal = retVal + /*shadow_factor**/(lighting_model (intersection, L*intersection.normal, abs(R*V)) + ref*intersection.material.kS);
	return retVal;
}

Intensity Scene::lighting_model (Intersection& intersection, double costTheta, double cosAlpha)
{
	double cosAlphaN = pow (cosAlpha, intersection.material.n);
	Intensity specular = iP*(intersection.material.kS*cosAlphaN);
	specular.clamp ();
	Intensity i = iP*(intersection.material.kD*costTheta);
	//i.clamp ();
	return i;//+specular;
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