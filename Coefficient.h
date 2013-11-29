#ifndef COEFFICIENT_H
#define COEFFICIENT_H

class Coefficient
{
	public:
		float r;
		float g;
		float b;
		Coefficient () : r (0.0f), g (0.0f), b(0.0f) {}
		Coefficient (float _r, float _g, float _b) : r (_r), g (_g), b(_b) {}
		void set (float _r, float _g, float _b)
		{
			r = _r;
			g = _g;
			b = _b;
		}
		Coefficient operator* (const Coefficient& k)
		{
			return Coefficient (r*k.r, g*k.g, b*k.b);
		}
		Coefficient operator+ (const Coefficient& k)
		{
			return Coefficient (r+k.r, g+k.g, b+k.b);
		}
};

Coefficient operator* (const Coefficient& k, double a);

Coefficient operator* (double a, const Coefficient& k);

#endif