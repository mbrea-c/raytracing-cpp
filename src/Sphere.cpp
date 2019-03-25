#include <iostream>
#include <cmath>
#include "Sphere.h"


Sphere::Sphere(Vector3 p, double r, RGB col)
{
	construct(p, r, col, 0);
}

Sphere::Sphere(Vector3 p, double r, RGB col, double reflex)
{
	construct(p, r, col, reflex);
}

void Sphere::construct(Vector3 p, double r, RGB col, double reflex)
{

	pos    = p;
	radius = r;
	color  = col;

	if      (reflex > 1) reflectiveness = 1;
	else if (reflex < 0) reflectiveness = 0;
	else 		     reflectiveness = reflex;
}

std::list<Intersection> Sphere::intersect(Vector3& p0, Vector3& d)
{
	Vector3 pc = getPos();
	double r   = getRadius();
	std::list<Intersection> returnList;


	double a = d*d;
	double b = (d*2)*(p0 - pc); 
	double c = ((p0 - pc)*(p0 - pc)) - (r*r);

	double discr = b*b - 4*a*c;
	
	if (discr < 0)
	{
		return returnList;
	}


	// Parameter t in P = O + tD
	double t0 = ( sqrt(discr)-b)/(2*a);
	double t1 = (-sqrt(discr)-b)/(2*a);

	double t  = std::min(t0, t1);

	if (t <= 0.05) return returnList;
	

	
	//std::cout << "sphere t: " << t0 << " " << t1 << std::endl;


	// Points of intersection
	Vector3 ip0 = p0 + (d*t);

	// Normal vectors at intersections
	Vector3 n0 = (ip0 - pc).norm();

	Intersection pair0;
	pair0.p      = ip0;
	pair0.n      = n0;
	pair0.col    = color;
	pair0.reflex = reflectiveness;

	
	returnList.push_front(pair0);

	return returnList;


}

	

double Sphere::getRadius()
{
	return radius;
}
