#ifndef SPHERE_H
#define SPHERE_H

#include "GameObject.h"
#include "Vector.h"
#include <list>

class Sphere : public GameObject
{
	double radius;
public:
	Sphere(Vector3 p, double r, RGB col);
	Sphere(Vector3 p, double r, RGB col, double reflex);
	Sphere();
	void construct(Vector3 p, double r, RGB col, double reflex);
	std::list<Intersection> intersect (Vector3& origin, Vector3& direction);
	double getRadius();
};

#endif
