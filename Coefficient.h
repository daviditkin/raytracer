#ifndef COEFFICIENT_H
#define COEFFICIENT_H
#include <ostream>
using namespace std;

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

		bool operator> (const double& k)
		{
			return r>k && g>k && b>k;
		}
		
		// Overload << operator, so that we can print a Point easily
		friend ostream& operator<< (ostream& os, const Coefficient i)
		{
			os << "(" << i.r << ", " << i.g << ", " << i.b << ")";
			return os;
		}
};

Coefficient operator* (const Coefficient& k, double a);

Coefficient operator* (double a, const Coefficient& k);

#endif