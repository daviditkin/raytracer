#include "Coefficient.h"

Coefficient operator* (const Coefficient& k, double a)
{
	return Coefficient (a*k.r, a*k.g, a*k.b);
}

Coefficient operator* (double a, const Coefficient& k)
{
	return k*a;
}