#ifndef OBJECT_H
#define OBJECT_H

#include <list>
#include "Vector.h"
#include "RGB.h"

// This should only be here temporarily(TM)
struct Intersection
{
	Vector3 p;
	Vector3 n;
	RGB col;
	double reflex;
};

class GameObject
{
protected:
	Vector3 pos;
	RGB color;
	double reflectiveness;
public:
	Vector3 getPos();
	void translate(Vector3 mov);
	virtual std::list<Intersection> intersect (Vector3& origin, Vector3& direction);
};

#endif
