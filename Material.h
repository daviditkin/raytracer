#ifndef MATERIAL_H
#define MATERIAL_H
#include "Coefficient.h"

class Material
{
	public:
		Coefficient kA;
		Coefficient kD;
		Coefficient kS;
		Coefficient kT;

		// Refractive index
		float kR;
		int n;
};

#endif