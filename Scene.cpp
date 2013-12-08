#include "Scene.h"
#include "Transformation.h"
#include <iostream>
using namespace std;

Intensity Scene::raytrace (Ray& ray, int depth)
{
	int obj_ind = -1;
	double closest = -1;
	// if(ray.debug)
	// 	cout<<"RT: "<<depth<<" Ray from "<<ray.origin<<" direction "<<ray.direction<<endl;

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
		// if(obj_ind==0)
			// cout<<"int "<<intersection.point<<endl;
			// return Intensity(1.0,1.0,1.0);
		retVal = shade (ray, intersection, depth);
	}/*else if(ray.debug)
		cout<<"RT: "<<depth<<" Not hitting anything"<<endl;*/
	
	return retVal;
}

Intensity Scene::shade (Ray& ray, Intersection& intersection, int depth)
{
	Intensity retVal = iA*intersection.material.kA;

	if(ray.debug)
		cout<<"SH: "<<depth<<" MAX "<<MAX_DEPTH<<endl;
	if (depth > MAX_DEPTH)
		return retVal;

	Vector L = iP.position - intersection.point;
	L.normalize ();
	Vector R = reflect (L, intersection.normal);
	Vector V = ray.origin - intersection.point;
	V.normalize ();

	if(ray.debug)
		cout<<"SH: "<<depth<<" L "<<L<<" R "<<R<<" V "<<V<<endl;
		
	Ray shadow (intersection.point, L, ray.debug);
	double dist = L.length ();
	double t;
	Coefficient shadow_factor (1.0, 1.0, 1.0);
	for (int i = 0; i < objects.size (); ++i)
	{
		bool intersect = objects[i]->intersect (shadow, t);
		if (intersect)
		{
			if(t<dist) {
				shadow_factor.set (shadow_factor.r*(objects[i]->material.kT.r),
									shadow_factor.g*(objects[i]->material.kT.g),
									shadow_factor.b*(objects[i]->material.kT.b));
				if(shadow.debug)
					cout<<"SH: "<<depth<<" shadow intersected "<<i<<endl;
			}
		}
	}
	
	if(ray.debug)
		cout<<"SH: "<<depth<<" shadow factor "<<shadow_factor<<endl;

	Ray reflected (intersection.point, R, ray.debug);
	Intensity ref = raytrace (reflected, depth+1);
	ref.clamp ();

	Intensity tra (0.0,0.0,0.0);
	if (intersection.material.kT >0.0 && intersection.material.kR > 0.0 && ray.kR > 0.0)
	{
		Vector T = refract (V, intersection.normal, intersection.material.kR/ray.kR);
		Ray refracted (intersection.point, T, intersection.material.kR, ray.debug);
		tra = raytrace (refracted, depth+1);
		tra.clamp ();
		if(ray.debug)
			cout<<"refracting "<<T<<endl;
	}

	if(ray.debug)
		cout<<"SH: "<<depth<<" material "<<intersection.material.kS<<endl;
	retVal = retVal + shadow_factor*(lighting_model (intersection, abs(intersection.normal*L), abs(R*V), ray.debug)
					+ ref*intersection.material.kS*0.7 + tra*intersection.material.kT);
	
	if(ray.debug)
		cout<<"SH: "<<depth<<" Final intensity "<<retVal<<endl;
	retVal.clamp ();
	return retVal;
}

Intensity Scene::lighting_model (Intersection& intersection, double costTheta, double cosAlpha, bool debug)
{
	double cosAlphaN = pow (cosAlpha, intersection.material.n);
	Intensity i = iP*(intersection.material.kD*costTheta);
	i.clamp ();
	Intensity specular = iP*(intersection.material.kS*cosAlphaN);
	specular.clamp ();
	if(debug)
		cout<<"LM: diffuse "<<i<<" specular "<<specular<<endl;
	return i+specular;
}

Vector Scene::reflect (Vector& l, Vector& normal)
{
	Vector retVal = (2*(l*normal)*normal - l);
	retVal.normalize ();

	// Vector vPrime = v / (v*normal);
	// Vector retVal = vPrime + 2*normal;
	// retVal.normalize ();
	return retVal;
}

Vector Scene::refract (Vector& v, Vector& n, double kN)
{
	// Vector vPrime = v / (v*normal);
	// double kF = kN*vPrime.length ();
	// kF *= kF;
	// double len = (normal+vPrime).length ();
	// kF -= len*len;
	// kF = sqrt (kF);
	// Vector retVal = kF*(normal+vPrime) - normal;
	// retVal.normalize ();
	// return retVal;

	double cos1 = n*v;
	double cos2 = sqrt(1- kN*kN*(1-cos1*cos1));
	Vector r = (-kN)*v + (kN*cos1+cos2)*n;
	r.normalize ();
	return r;
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