#ifndef CAMERA_H
#define CAMERA_H

#include <list>
#include "Vector.h"
#include "Image.h"
#include "GameObject.h"
#include "Light.h"

using namespace std;

class Camera {
	Vector3 pos;
	Vector3 dir;
	int depth;
	double ambient;
	double eyeDist;

	// Compute image height and width in abstract scene units
	// This ensures aspect ratio is preserved and scale is kept
	// constant in different resolutions
	double heightImg = 200; 

	public:
		Camera(int depth, double ambient, double eyeDist);
		Camera(Vector3 pos, Vector3 dir, int depth, double ambient, double eyeDist);
		void renderImage(Image* target, list<GameObject*>& scn, list<Light>& lights);
		void translate(Vector3 mov);
		void translateRelative(Vector3 mov);
		void rotate(double x, double y);
	private:
		list<Intersection> intersection(Vector3& origin, Vector3& dir, list<GameObject*>& scn); // Finds closest intersection to ray origin in a scene
		RGB ray(Vector3& origin, Vector3& dir, list<GameObject*>& scn, list<Light>& lights, 
			double ambient, int depth); // Finds ray color
};

#endif
