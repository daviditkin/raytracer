#include "Light.h"

Intensity operator* (const Light& l, const Coefficient& k)
{
	return l.intensity*k;
}

Intensity operator* (const Coefficient& k, const Light& l)
{
	return l*k;
}

Intensity operator* (const Light& l, const double a)
{
	return l.intensity*a;
}

Intensity operator* (const double a, const Light& l)
{
	return l*a;
}
