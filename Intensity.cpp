#include "Intensity.h"

Intensity operator* (const Intensity& i, const Coefficient& k)
{
	return Intensity (i.r*k.r, i.g*k.g, i.b*k.b);
}

Intensity operator* (const Coefficient& k, const Intensity& i)
{
	return i*k;
}

Intensity operator* (const Intensity& i, const double a)
{
	return Intensity (i.r*a, i.g*a, i.b*a);
}

Intensity operator* (const double a, const Intensity& i)
{
	return i*a;
}
