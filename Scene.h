#ifndef SCENE_H
#define SCENE_H

#include <vector>
using namespace std;
#include "Object.h"
#include "Light.h"

class Scene
{
	public:
		Intensity iA;
		Light iP;
		Point cop;
		int MAX_DEPTH;
		vector<Object*> objects;
		Scene (int max, Point c) : cop (c), MAX_DEPTH (max) {}
		void set_ambient (Intensity i);
		void set_pls (Point p, Intensity i);
		Intensity raytrace (Ray& ray, int depth);
		Intensity shade (int obj_index, Ray& ray, Intersection& intersection, int depth);
		Matrix intersection_matrix (const Ray& ray);

		Intensity lighting_model (int obj, double costTheta, double cosAlpha);

		Vector reflect (Vector& v, Vector& normal);

};

#endif