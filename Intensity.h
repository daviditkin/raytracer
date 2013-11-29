#ifndef INTENSITY_H
#define INTENSITY_H
#include "Coefficient.h"

class Intensity
{
	public:
		float r;
		float g;
		float b;
		Intensity () : r (0), g (0), b (0) {}
		Intensity (float _r, float _g, float _b) : r (_r), g (_g), b (_b) {}

		Intensity operator+ (const Intensity& i)
		{
			return Intensity (r+i.r, g+i.g, b+i.b);
		}

		void clamp ()
		{
			if (r>1.0f) r = 1.0f;
			if (g>1.0f) g = 1.0f;
			if (b>1.0f) b = 1.0f;
			if (r<0.0f) r = 0.0f;
			if (g<0.0f) g = 0.0f;
			if (b<0.0f) b = 0.0f;
		}
};

Intensity operator* (const Intensity& i, const Coefficient& k);

Intensity operator* (const Coefficient& k, const Intensity& i);

Intensity operator* (const Intensity& i, const double a);

Intensity operator* (const double a, const Intensity& i);

#endif