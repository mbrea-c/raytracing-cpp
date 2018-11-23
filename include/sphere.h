#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "vector.h"
#include <list>

class Sphere : public Object
{
	double radius;
public:
	Sphere(Vector3 p, double r, RGB col);
	Sphere(Vector3 p, double r, RGB col, double reflex);
	Sphere();
	std::list<Intersection> intersect (Vector3& origin, Vector3& direction);
	double getRadius();
};

#endif
