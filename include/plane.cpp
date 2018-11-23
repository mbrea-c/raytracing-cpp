#include <iostream>
#include "plane.h"

Plane::Plane(Vector3 n, double c, RGB col)
{
	normal = n;
	offset = c;
	color  = col;
	reflectiveness = 0;
}

Plane::Plane(Vector3 n, double c, RGB col, double r)
{
	normal = n;
	offset = c;
	color  = col;

	if      (r > 1)	reflectiveness = 1;
	else if (r < 0) reflectiveness = 0;
	else 		reflectiveness = r;
}

std::list<Intersection> Plane::intersect(Vector3& p0, Vector3& d)
{
	double t = -(offset + (normal*p0)) / (normal*d);

	std::list<Intersection> returnList;

	if (t <= 0.05) return returnList;

	//std::cout << "plane t: " << t << std::endl;

	Intersection res;
	res.p = p0 + t*d;
	res.n = normal;
	res.col = color;
	res.reflex = reflectiveness;

	returnList.push_front(res);

	return returnList;

}
