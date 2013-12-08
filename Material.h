#ifndef MATERIAL_H
#define MATERIAL_H
#include "Coefficient.h"

// A material for objects, with its coefficients for lights
class Material
{
	public:
		Coefficient kA;
		Coefficient kD;
		Coefficient kS;
		Coefficient kT;

		// Refractive index
		double kR;
		int n;
};

#endif