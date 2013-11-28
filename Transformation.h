#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include <cmath>
#include <cstdlib>
using namespace std;

#include "Point.h"
#include "Matrix.h"
#define X 0
#define Y 1
#define Z 2
#define PI 3.14159265

struct Viewport
{
	double xMax;
	double xMin;
	double yMax;
	double yMin;
	double zMax;
	double zMin;
};

class Transformation
{
	public:

		/* Rotation matrices around the 3 axes */

		static Matrix x_rotation_matrix (double cosTheta, double sinTheta)
		{
			double a[] = {  1,	0, 						0,						0,
							0,	cosTheta,	-sinTheta,	0,
							0,	sinTheta,	cosTheta,	0,
							0,	0, 						0, 						1 };
			return Matrix (a);
		}

		static Matrix y_rotation_matrix (double cosTheta, double sinTheta)
		{
			double a[] = { cosTheta,	0,	sinTheta,	0,
						   0, 					 	1,	0,						0,
						  -sinTheta, 	0,	cosTheta,   0,
						   0, 					 	0,	0,						1 };

			return Matrix (a);
		}

		static Matrix z_rotation_matrix (double cosTheta, double sinTheta)
		{
			double a[] = { cosTheta,	-sinTheta,	0,	0,
						   sinTheta,	cosTheta,	0,	0,
						   0, 						0, 						1,	0,
						   0, 					  	0, 						0,	1 };

			return Matrix (a);
		}
		
		// Utility functions
		static double to_rad (double degrees) { return degrees * PI / 180.0; }
		static double to_deg (double radians) { return radians * 180.0 / PI; }

		/* Angle in degrees 
		 * A quicker function than the generic one if we want to rotate around
		 * one of the 3 axis of the coordinate system
		 */
		static Matrix axis_rotation_matrix (double theta, int axis)
		{
			if (axis == X)
				return generic_rotation (Point (0,0,0), Point (1,0,0),theta);
			if (axis == Y)
				return generic_rotation (Point (0,0,0), Point (0,1,0),theta);

			return generic_rotation (Point (0,0,0), Point (0,0,1),theta);
		}

		// Generic rotation around an axis defined by the line from P1 to P2
		static Matrix generic_rotation (Point p1, Point p2, double theta)
		{
			// 1)Translate so that p1 is at the origin
			Matrix translation = translation_matrix (-p1.x, -p1.y, -p1.z);
			Matrix inv_translation = translation_matrix (p1.x, p1.y, p1.z);

			// 2)Rotate space about the x axis so that 
			// the rotation axis lies in the xz plane
			Vector v = (p2-p1);
			v.normalize ();

			double d = sqrt (v[1]*v[1] + v[2]*v[2]);
			// If U(a,b,c) is the unit vector in the direction of P1-P2
			// and the projection on the yz plane has length d=sqrt(b^2+c^2),
			// the angle of rotation around the x axis has cos=c/d and sin=b/d
			Matrix x_rotation = x_rotation_matrix (v[2]/d, v[1]/d);
			Matrix inv_x_rotation = x_rotation_matrix (v[2]/d, -v[1]/d);

			// 3)Rotate space about the y axis so that 
			// the rotation axis lies along the positive z axis
			Matrix y_rotation = y_rotation_matrix (d, -v[0]);
			Matrix inv_y_rotation = y_rotation_matrix (d, v[0]);

			// 4)Actual rotation
			Matrix rotation = z_rotation_matrix (cos (to_rad (theta)), sin (to_rad (theta)));

			// 5)Inverse transformations after the actual rotation
			Matrix ret = inv_translation*inv_x_rotation*inv_y_rotation*rotation*y_rotation*x_rotation*translation;
			return ret;
		}

		// Translation matrix
		static Matrix translation_matrix (double dx, double dy, double dz)
		{
			double a[] = {  1, 0, 0, dx,
							0, 1, 0, dy,
							0, 0, 1, dz,
							0, 0, 0, 1 };
			return Matrix (a);
		}

		// Scaling matrix
		static Matrix scaling_matrix (double sx, double sy, double sz)
		{
			double a[] = {  sx, 0,  0,  0,
							0,  sy, 0,  0,
							0,  0,  sz, 0,
							0,  0,  0,  1 };
			return Matrix (a);
		}

		/* Shearing matrices for the 3 planes */

		//s1=SHx s2=SHy
		static Matrix shear_xy (double s1, double s2) {
			double a[] = {  1, 	0,  s1, 0,
							0,  1, 	s2, 0,
							0,  0,  1, 	0,
							0,  0,  0,  1 };
			return Matrix (a);
		}

		//s1=SHy s2=SHz
		static Matrix shear_yz (double s1, double s2) {
			double a[] = {  1, 	0,  0, 	0,
							s1,  1, 	0, 	0,
							s2,  0,  1, 	0,
							0,  0,  0,  1 };
			return Matrix (a);
		}

		//s1=SHx s2=SHz
		static Matrix shear_xz (double s1, double s2) {
			double a[] = {  1, 	s1,	0, 	0,
							0,  1,	0, 	0,
							0,  s2, 1, 	0,
							0,  0,  0,	1 };
			return Matrix (a);
		}

		static Matrix perspective_to_parallel (double zMin)
		{
			double f1 = 0;
			double f2 = 0;
			if (zMin!=-1)
			{
				f1 = 1/(1+zMin);
				f2 = -zMin/(1+zMin);
			}

			double a[] = { 	1, 0, 	0,	0,
							0, 1, 	0,	0,
							0, 0, 	f1,	f2,
							0, 0,  -1,	0 };
			Matrix ret (a);
			return ret;
		}

		/* Projection matrices */

		static Matrix perspective_matrix (double d)
		{
			double a[] = {  1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 0, 0,
							0, 0, 1/d, 1 };
			return Matrix (a);
		}

		static Matrix parallel_matrix ()
		{
			double a[] = {  1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 0, 0,
							0, 0, 0, 1 };
			return Matrix (a);
		}
};

#endif