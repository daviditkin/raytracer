#ifndef SCENE_H
#define SCENE_H

#include <vector>
using namespace std;
#include "Object.h"
#include "Light.h"

class Scene
{
	public:
		Point cop;
		vector<Object*> objects;
		Scene (int MAX_DEPTH, Point c) : cop (c) {}
		Intensity raytrace (const Ray& ray, int depth);
		Intensity shade ();
		Matrix intersection_matrix (const Ray& ray);

};

#endif