#include "Rect.h"

bool Rect::intersect (const Ray& ray, double& t)
{
	double A = normal[0];
	double B = normal[1];
	double C = normal[2];
	double D = - (A*points[0].x +B*points[0].y+C*points[0].z);

	if (A*ray.direction[0]+B*ray.direction[1]+C*ray.direction[2]==0)
		return false;
	
	double dist = - (A*ray.origin.x+B*ray.origin.y+C*ray.origin.z+D)/(A*ray.direction[0]+B*ray.direction[1]+C*ray.direction[2]);

	if (dist < 0)
		return false;

	Point p;
	p.x = ray.origin.x+dist*ray.direction[0];
	p.y = ray.origin.y+dist*ray.direction[1];
	p.z = ray.origin.z+dist*ray.direction[2];

	double epsilon = 0.000001;
	if (p.x > xMax+epsilon || p.x < xMin-epsilon || p.y > yMax+epsilon || 
		p.y < yMin-epsilon || p.z > zMax+epsilon || p.z < zMin-epsilon)
		return false;
	t = dist;
	return true;
}

Vector Rect::normal_in (const Point& p)
{
	return normal;
}

void Rect::calculate_normal ()
{
	Vector v1 = points[1] - points[0];
	Vector v2 = points[2] - points[1];

	normal = (v2^v1);
	normal.normalize ();
}

void Rect::calculate_bounds ()
{
	xMin = xMax = points[0].x;
	yMin = yMax = points[0].y;
	zMin = zMax = points[0].z;

	for (int i=1;i<points.size ();i++)
	{
		if (points[i].x > xMax)
			xMax = points[i].x;
		if (points[i].x < xMin)
			xMin = points[i].x;

		if (points[i].y > yMax)
			yMax = points[i].y;
		if (points[i].y < yMin)
			yMin = points[i].y;

		if (points[i].z > zMax)
			zMax = points[i].z;
		if (points[i].z < zMin)
			zMin = points[i].z;
	}
	cout<<"bounds "<<xMin<<","<<xMax<<","<<yMin<<","<<yMax<<","<<zMin<<","<<zMax<<endl;
}