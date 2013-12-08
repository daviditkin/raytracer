#ifndef INTENSITY_H
#define INTENSITY_H
#include "Coefficient.h"
#include <ostream>
using namespace std;

// Represents a light intensity, with rgb components
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

		// Intensity values can not go above 1.0 or below 0.0
		void clamp ()
		{
			float eps = 0.0000001f;
			if (r>1.0f) r = 1.0f;
			if (g>1.0f) g = 1.0f;
			if (b>1.0f) b = 1.0f;
			if (r<eps) r = 0.0f;
			if (g<eps) g = 0.0f;
			if (b<eps) b = 0.0f;
		}
		
		// Overload << operator, so that we can print a Point easily
		friend ostream& operator<< (ostream& os, const Intensity i)
		{
			os << "(" << i.r << ", " << i.g << ", " << i.b << ")";
			return os;
		}
};

//Overload operators to do operations on intensities more easily
Intensity operator* (const Intensity& i, const Coefficient& k);

Intensity operator* (const Coefficient& k, const Intensity& i);

Intensity operator* (const Intensity& i, const double a);

Intensity operator* (const double a, const Intensity& i);

#endif