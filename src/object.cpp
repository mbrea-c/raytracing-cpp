#include "object.h"

Vector3 Object::getPos()
{
	return pos;
}

void Object::translate(Vector3 mov)
{
	this->pos = Vector3(this->pos.x + mov.x, this->pos.y + mov.y, this->pos.z + mov.z);
}

std::list<Intersection> Object::intersect(Vector3& origin, Vector3& direction)
{
	return std::list<Intersection>();
}
