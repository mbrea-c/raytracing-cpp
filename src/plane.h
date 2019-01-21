#ifndef PLANE_H
#define PLANE_H

#include "vector.h"
#include "object.h"

class Plane : public Object
{
private:
	Vector3 normal;
	double offset;

public:
	Plane(Vector3 n, double c, RGB col);
	Plane(Vector3 n, double c, RGB col, double r);
	std::list<Intersection> intersect(Vector3& origin, Vector3& direction);


};







#endif
