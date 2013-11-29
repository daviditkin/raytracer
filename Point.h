#ifndef POINT_H
#define POINT_H
#include <exception>
#include <ostream>
using namespace std;

// A custom exception, thrown when using a bad index
// when accessing an element using M(i, j), or P[i] for points
class BadIndex : public exception
{
	public:
		BadIndex (char* str) { msg = str; }
		char const* what () const throw() { return msg; }
	private:
		char* msg;
};

class Point
{
	public:
		double x;
		double y;
		double z;
		double w;
		Point () : x (0), y(0), z(0), w(1) {}
		Point (double _x, double _y, double _z) : x (_x), y(_y), z(_z), w(1) {}

		// Overload equality operator
		bool operator== (const Point& p)
		{
			return (x == p.x && y == p.y && z == p.z);
		}

		// Overload inequality operator
		bool operator!= (const Point& p)
		{
			return (x != p.x || y != p.y || z != p.z);
		}

		double operator[] (const int index) const
		{
			switch (index)
			{
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				case 3:
					return w;
			}

			throw BadIndex("Matrix subscript out of bounds");
		}
		
		// Overload << operator, so that we can print a Point easily
		friend ostream& operator<< (ostream& os, const Point p)
		{
			os << "(" << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ")";
			return os;
		}
};

#endif