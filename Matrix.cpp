#include "Matrix.h"

/* Creates an identity n*n Matrix,
   or a matrix of 0s			*/
Matrix::Matrix ()
{
	_matrix.resize (_r*_c, 0);
	for (int i=0; i<_r; i++)
		(*this) (i, i) = 1.0;
}

// Creates a matrix from a 4x4 array
Matrix::Matrix (double array[])
{
	_matrix = vector<double> (array, array + _r*_c);
}

/* Creates a matrix from the 3 vectors,
   adding the last row and column 	*/
Matrix::Matrix (Vector Rx, Vector Ry, Vector Rz)
{
	double a[16];
	for (int i = 0; i < 4; ++i)
	{
		a[i] = Rx[i];
		a[4+i] = Ry[i];
		a[8+i] = Rz[i];
		a[12+i] = 0;
	}
	a[15] = 1;
	_matrix = vector<double> (a, a + _r*_c);
}

double Matrix::at (int x, int y) const
{
	return _matrix [abs_pos (x, y)];
}

// Calculate absolute position of (x,y) in the linearized array
int Matrix::abs_pos (int x, int y) const
{
	return y * _c + x;
}

// Overload + to have matrix sum
Matrix Matrix::operator+ (const Matrix& M)
{
	Matrix ret;

	for(int i=0; i<get_rows (); i++)
	{
		for(int j=0; j<get_columns (); j++)
			ret (i, j) = (*this) (i, j) + M (i, j);
	}

	return ret;
}

// Overload * to have matrix multiplication
Matrix Matrix::operator* (const Matrix& M)
{
	Matrix ret;

	for(int i=0; i<get_rows (); i++)
	{
		for(int j=0; j<get_columns (); j++)
		{
			double val = 0.0;
			for(int k=0; k<get_columns (); k++) {
				val += (*this) (i, k) * M (k, j);
			}

			ret (i, j) = val;
		}
	}
	return ret;
}

// Overload so that if we use m(x,y) it's the same as m.at(x,y)
double& Matrix::operator() (unsigned int row, unsigned int col)
{
	if (row >= _r || col >= _c)
		throw BadIndex("Matrix subscript out of bounds");

	return _matrix [abs_pos (col, row)];
}

double Matrix::operator() (unsigned int row, unsigned int col) const
{
	if (row >= _r || col >= _c)
		throw BadIndex("Matrix subscript out of bounds");

	return _matrix [abs_pos (col, row)];
}

// Override m*a and a*m to have matrix-scalar product
Matrix operator* (double a, const Matrix& m)
{
	return m * a;
}

Matrix operator* (const Matrix& m, double a)
{
	Matrix ret;

	for(int i=0; i<m.get_rows (); i++)
	{
		for(int j=0; j<m.get_columns (); j++)
		{
			ret (i, j) = a * m (i, j);
		}
	}
	return ret;
}

// Override m*p and p*m to have matrix-point product
Point operator* (const Point& p, const Matrix& m)
{
	double v[4];
	for (int i=0; i<4; i++) {
		v[i] = 0;
		for (int j = 0; j < 4; ++j)
		{
			v[i] += m(j,i)*p[i];
		}
	}

	for (int j = 0; j < 3; ++j)
	{
		v[j] /= v[3];
	}
	return Point (v[0], v[1], v[2]);
}

Point operator* (const Matrix& m, const Point& p)
{
	double v[4];
	for (int i=0; i<4; i++) {
		v[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			v[i] += m(i,j)*p[j];
		}
	}

	for (int j = 0; j < 3; ++j)
	{
		v[j] /= v[3];
	}
	return Point (v[0], v[1], v[2]);
}

// Override m*v and v*m to have matrix-vector product
Vector operator* (const Vector& v, const Matrix& m)
{
	Vector ret;

	for (int i=0; i<m.get_columns (); i++)
	{
		double val = 0;
		for (int j=0; j<m.get_rows (); j++)
			val += v[j] * m(j, i);
		ret[i] = val;
	}
	
	return ret;
}

Vector operator* (const Matrix& m, const Vector& v)
{
	Vector ret;

	for (int i=0; i<m.get_rows (); i++)
	{
		double val = 0;
		for (int j=0; j<m.get_columns (); j++)
			val += v[j] * m(i, j);
		ret[i] = val;
	}

	return ret;
}