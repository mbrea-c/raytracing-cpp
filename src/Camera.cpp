#include <math.h>
#include <list>
#include <unistd.h>
#include <iostream>
#include "Camera.h"
#include "GameObject.h"
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "RGB.h"
#include "Light.h"
#include "Image.h"

#define PI 3.14159265

using namespace std;

Camera::Camera(int depth, double ambient, double eyeDist) {
	this->depth = depth;
	this->ambient = ambient;
	this->eyeDist = eyeDist;
	this->pos = Vector3(0, 0, 0);
	this->dir = Vector3(0, 0, 1);
}

Camera::Camera(Vector3 pos, Vector3 dir, int depth, double ambient, double eyeDist) {
	this->depth = depth;
	this->ambient = ambient;
	this->eyeDist = eyeDist;
	this->pos = pos;
	this->dir = dir.norm();
}

void Camera::translate(Vector3 mov) {
	pos = Vector3(pos.x + mov.x, pos.y + mov.y, pos.z + mov.z);
}

void Camera::translateRelative(Vector3 mov) {
	const Vector3 UP    = Vector3(0,1,0);
	Vector3 basisY = (UP - ((dir * UP) * dir)).norm();
	Vector3 basisX = (basisY.cross(dir)).norm();
	pos = pos + mov.x * basisX + mov.y * basisY + mov.z * dir; 
}

//TODO: Use quaternions like a civilised human
void Camera::rotate(double x, double y) {
	const Vector3 UP    = Vector3(0,1,0);
	const Vector3 RIGHT = Vector3(1,0,0);
	const Vector3 FORWARD = Vector3(0,0,1);
	Vector3 dirOrtY = dir - ((dir * UP) * UP);
	Vector3 dirOrtX = dir - dirOrtY;
	double angleToForward = acos((dirOrtY * FORWARD) / dirOrtY.len());
	double angleToRight;
	if (angleToForward > PI/2)
	{
		angleToRight   = -acos((dirOrtY * RIGHT) / dirOrtY.len());
	} else {

		angleToRight   = acos((dirOrtY * RIGHT) / dirOrtY.len());
	}

	double angleToUp      = acos(dir * UP);

	if (angleToUp + y > 0 && angleToUp + y < PI )
	{
		angleToUp += y;
	}

	angleToRight = fmod(angleToRight + x, 2*PI);
	dir = Vector3(cos(angleToRight)*sin(angleToUp), cos(angleToUp), sin(angleToRight)*sin(angleToUp)).norm();
}


void Camera::renderImage(Image* target, list<GameObject*>& scn, list<Light>& lights) {
		// Shoot rays to render the scene
		const double stepSize = heightImg / (float)target->getHeight();
		const double widthImg = stepSize * (float)target->getWidth();

		for (int i = 0; i < target->getHeight(); i++)
		{
			for (int j = 0; j < target->getWidth(); j++)
			{
				// We compute a basis to a two dimensional subspace orthogonal
				// to the direction vector
				Vector3 basisY = Vector3(0,1,0) - (((dir * Vector3(0,1,0)) * (1/dir.len())) * dir.norm());
				basisY = basisY.norm();
				Vector3 basisX = basisY.cross(dir).norm();
				Vector3 pixPos = pos + dir*eyeDist + basisX*(-widthImg / 2 + (float)j*stepSize)
						+ basisY*(heightImg / 2 - (float)i*stepSize);
				Vector3 dir = (pixPos - pos).norm();
				target->setPixel(j, i, ray(pos, dir, scn, lights, ambient, depth));
			}
		}

}

RGB Camera::ray(Vector3& origin, Vector3& dir, list<GameObject*>& scn, list<Light>& lights, double ambient, int depth)
{

	list<Intersection> minimumList = intersection(origin, dir, scn);
	RGB pixColor;
	
	// If there are no intersections
	if (minimumList.size() < 1) 
	{
		pixColor.r = 0;
		pixColor.g = 0;
		pixColor.b = 0;
		return pixColor;
	}

	Intersection minimum = minimumList.front();
	pixColor = minimum.col;

	// Shadow and shading
	for ( auto light : lights )
	{
		Vector3 lVec = (light.pos - minimum.p);
		Vector3 lDir = lVec.norm();
		// Computes the shadow, if applicable
		list<Intersection> shadowing = intersection(minimum.p, lDir, scn);
		if ((shadowing.size() > 0) && (lVec.len() > (shadowing.front().p - minimum.p).len())) 
		{
			pixColor.r *= ambient;
			pixColor.g *= ambient;
			pixColor.b *= ambient;
		} 
		// Computes shading
		else
		{
			double cosine = lDir*minimum.n;
			if (cosine < 0) cosine = 0;
			cosine = ambient + (cosine * (1-ambient));
			pixColor.r *= cosine;
			pixColor.g *= cosine;
			pixColor.b *= cosine;
		}
	}

	// Exit condition in recursion
	if (depth <= 1) return pixColor;

	// Recursively calls ray to produce reflections
	Vector3 reflexDir = ((2*(minimum.n * (((-1)*dir) * minimum.n)))+dir);
	RGB reflexCol = ray(minimum.p, reflexDir, scn, lights, ambient, depth-1);

	double reflex  = minimum.reflex;
	double nreflex = 1 - reflex;

	pixColor.r = nreflex*pixColor.r + reflex*reflexCol.r;
	pixColor.g = nreflex*pixColor.g + reflex*reflexCol.g;
	pixColor.b = nreflex*pixColor.b + reflex*reflexCol.b;
	
	return pixColor;
}

list<Intersection> Camera::intersection(Vector3& origin, Vector3& dir, list<GameObject*>& scn)
{
	list<Intersection> candidates;
	list<Intersection> result;

	// Get all potential intersections 
	for (auto obj : scn)
	{
		for (auto x : obj->intersect(origin, dir)) candidates.push_front(x);
	}

	if (candidates.size() < 1) return result;

	// Find intersection that is closest to origin
	Intersection minimum = candidates.front();
	double minimumLen    = (minimum.p - origin).len();
	candidates.pop_front();

	for (auto cand : candidates)
	{
		double localLen = (cand.p - origin).len();
		if ((localLen < minimumLen) && (localLen > 0))
		{
			minimum    = cand;
			minimumLen = (minimum.p - origin).len();
		}
	}


	result.push_front(minimum);

	return result;
}
