#ifndef VECTOR_H
#define VECTOR_H

using namespace std;

class Vector3
{
public:
	double x;
	double y;
	double z;

	Vector3(double x0, double y0, double z0);
	Vector3();

	double  len();
	Vector3 norm();
	Vector3 cross(Vector3 v);
};

Vector3 operator*(Vector3 v, double scalar);
Vector3 operator*(double scalar, Vector3 v);
Vector3 operator+(Vector3 v0, Vector3 v1);
Vector3 operator-(Vector3 v0, Vector3 v1);
double  operator*(Vector3 v0, Vector3 v1);



#endif
