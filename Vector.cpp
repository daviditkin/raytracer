#include <cmath>
using namespace std;

#include "Vector.h"

double Vector::length () const
{
	return sqrt (x*x+y*y+z*z);
}

// Create a unit vector by normalizing
void Vector::normalize ()
{
	double l = length ();
	x /= l;
	y /= l;
	z /= l;
}

// Vector CROSS PRODUCT
Vector operator^ (const Vector& v1,const Vector& v2)
{
	double x1 = v1.y * v2.z - v1.z * v2.y;
	double y1 = v1.z * v2.x - v1.x * v2.z;
	double z1 = v2.x * v2.y - v1.y * v2.x;
	
	return Vector (x1, y1, z1);
}

// Dot product
double Vector::operator* (const Vector& v2)
{
	return x*v2.x+y*v2.y+z*v2.z;
}

// Vector sum
Vector Vector::operator+ (const Vector& v2)
{
	double v[3];
	v [0] = x + v2.x;
	v [1] = y + v2.y;
	v [2] = z + v2.z;
	return Vector (v[0], v[1], v[2]);
}

// Vector sum
Vector Vector::operator- (const Vector& v2)
{
	double v[3];
	v [0] = x - v2.x;
	v [1] = y - v2.y;
	v [2] = z - v2.z;
	return Vector (v[0], v[1], v[2]);
}

/* To access the components easier in a loop */
double& Vector::operator[] (const int index)
{
	switch (index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}
	
	throw BadIndex("Matrix subscript out of bounds");
}

double Vector::operator[] (const int index) const
{
	switch (index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}
	
	throw BadIndex("Matrix subscript out of bounds");
}

// Override the equality operator
bool Vector::operator== (const Vector& v)
{
	return (x == v.x && y == v.y && z == v.z);
}

// Override the inequality operator
bool Vector::operator!= (const Vector& v)
{
	return (x != v.x || y != v.y || z != v.z);
}

// a*v is different from v*a, ovveriding both
Vector operator* (double a, const Vector& v)
{
	return v * a;
}

Vector operator* (const Vector& v, double a)
{
	double vec[] = { a*v.x, a*v.y, a*v.z };
	return Vector (vec[0], vec[1], vec[2]);
}

Vector operator/ (const Vector& v, double a)
{
	double vec[] = { a/v.x, a/v.y, a/v.z };
	return Vector (vec[0], vec[1], vec[2]);
}

// Override difference between points
Vector operator- (const Point& p2, const Point& p1)
{
	// we have to normalize the points to calculate the difference
	return Vector (p1, p2);
}

Point operator+ (const Vector& v, const Point& p)
{
	return Point (p.x+v.x, p.y+v.y, p.z+v.z);
}

Point operator+ (const Point& p, const Vector& v)
{
	return v+p;
}