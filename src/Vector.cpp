#include <cmath>
#include <iostream>
#include "Vector.h"



using namespace std;

Vector3::Vector3(double x0, double y0, double z0)
{
	x = x0;
	y = y0;
	z = z0;
}

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}


double operator*(Vector3 v0, Vector3 v1)
{
	return(v0.x*v1.x + v0.y*v1.y + v0.z*v1.z);
}

Vector3 operator*(Vector3 v, double c)
{
	return Vector3(v.x*c, v.y*c, v.z*c);
}

Vector3 operator*(double c, Vector3 v)
{
	return Vector3(v.x*c, v.y*c, v.z*c);
}

Vector3 operator+(Vector3 v0, Vector3 v1)
{
	return Vector3(v0.x+v1.x, v0.y+v1.y, v0.z+v1.z);
}

Vector3 operator-(Vector3 v0, Vector3 v1)
{
	return Vector3(v0.x-v1.x, v0.y-v1.y, v0.z-v1.z);
}


double Vector3::len()
{
	return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3::norm()
{
	return (*this)*(1/len());
}

Vector3 Vector3::cross(Vector3 v)
{
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}
