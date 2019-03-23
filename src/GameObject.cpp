#include "GameObject.h"

Vector3 GameObject::getPos()
{
	return pos;
}

void GameObject::translate(Vector3 mov)
{
	this->pos = Vector3(this->pos.x + mov.x, this->pos.y + mov.y, this->pos.z + mov.z);
}

std::list<Intersection> GameObject::intersect(Vector3& origin, Vector3& direction)
{
	return std::list<Intersection>();
}
