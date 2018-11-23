#include "object.h"

Vector3 Object::getPos()
{
	return pos;
}

std::list<Intersection> Object::intersect(Vector3& origin, Vector3& direction)
{
		return std::list<Intersection>();
}
