#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
using namespace std;
#include "Vector.h"

class Matrix
{
	private:
		vector<double> _matrix;
		int abs_pos (int x, int y) const;
		static const int _r = 4;
		static const int _c = 4;
	public:
		// All 0s if false, identity matrix if true
		Matrix ();
		Matrix (double array[]);
		Matrix (Vector Rx, Vector Ry, Vector Rz);
		// Get element at (x, y)
		double at (int x, int y) const;

		int get_rows () const { return _r; };
		int get_columns () const { return _c; };

		// Redefine matrix operations overloading + and *
		Matrix operator+ (const Matrix& M);
		Matrix operator* (const Matrix& M);

		// Overload () to access a single element using
		// M(i, j)
		double& operator() (unsigned int row, unsigned int col);
		double operator() (unsigned int row, unsigned int col) const;

		// Overload << to print the matrix easily
		friend ostream& operator<< (ostream& os, const Matrix& M)
		{
			for(int i=0; i<M.get_rows (); i++)
			{
				for(int j=0; j<M.get_columns (); j++)
					os << M.at (j,i) << " ";
				os << endl;
			}
			return os;
		}
};

// Overload * to multiply a matrix by a scalar
Matrix operator* (const Matrix& m, double a);
Matrix operator* (double a, const Matrix& m);
		
// Overload the * operator for multiplication with a point
Point operator* (const Point& p, const Matrix& m);
Point operator* (const Matrix& m, const Point& p);

// Overload the * operator for multiplication with a vector
Vector operator* (const Vector& v, const Matrix& m);
Vector operator* (const Matrix& m, const Vector& v);

#endif