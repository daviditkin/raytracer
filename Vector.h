#ifndef VECTOR_H
#define VECTOR_H
#include "Point.h"

class Vector
{
	public:
		double x;
		double y;
		double z;
		double w;
		Vector () : x (0), y(0), z(0), w(0) {}
		Vector (double _x, double _y, double _z) : x (_x), y(_y), z(_z), w(0) {}
		Vector (const Point& p1, const Point& p2)
		{
			x = p2.x - p1.x;
			y = p2.y - p1.y;
			z = p2.z - p1.z;
			w = 0;
		}

		double length () const;
		void normalize ();

		// Overload the * operator as the CROSS PRODUCT
		double operator* (const Vector& V);
		Vector operator+ (const Vector& V);
		Vector operator- (const Vector& V);
		// Overload the [] operator to access each
		// vector component individually via v[index]
		double& operator[] (const int index);
		double operator[] (const int index) const;
		// Overload equality operator
		bool operator== (const Vector& v);
		bool operator!= (const Vector& v);

		// Overload << operator to print the vector easily
		friend ostream& operator<< (ostream& os, const Vector& v)
		{
			os << "(" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
			return os;
		}
};

// Overload the * operator for multiplication with a scalar
Vector operator^ (const Vector& v1,const Vector& v2);
Vector operator* (const Vector& v, double a);
Vector operator* (double a, const Vector& v);
Vector operator/ (const Vector& v, double a);
Vector operator- (const Point& p2, const Point& p1);
Point operator+ (const Vector& v, const Point& p);
Point operator+ (const Point& p, const Vector& v);

#endif