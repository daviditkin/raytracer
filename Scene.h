#ifndef SCENE_H
#define SCENE_H

#include <vector>
using namespace std;
#include "Object.h"
#include "Light.h"
#define EPSILON 0.00001

// Represents the scene
class Scene
{
	public:
		// ambient light
		Intensity iA;
		// point light source
		Light iP;
		// max depth of the ray tree
		int MAX_DEPTH;
		// objects in the scene
		vector<Object*> objects;

		Scene (int max) : MAX_DEPTH (max) {}

		void set_ambient (Intensity i);
		void set_pls (Point p, Intensity i);
		//raytrace a ray
		Intensity raytrace (Ray& ray, int depth);
		Intensity shade (Ray& ray, Intersection& intersection, int depth);

		Intensity lighting_model (Intersection& intersection, double costTheta, double cosAlpha, bool debug);

		Vector reflect (Vector& v, Vector& normal);
		Vector refract (Vector& v, Vector& normal, double kN);

};

#endif