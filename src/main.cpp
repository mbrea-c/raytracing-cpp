#include <iostream>
#include <fstream>
#include <cmath>
#include <list>
#include "object.h"
#include "vector.h"
#include "sphere.h"
#include "plane.h"
#include "RGB.h"
#include "light.h"
#include "Image.h"

using namespace std;


list<Intersection> intersection(Vector3& origin, Vector3& dir, list<Object*>& scn);
RGB ray(Vector3& origin, Vector3& dir, list<Object*>& scn, list<Light>& lights, double ambient, int depth);



int main()
{
	// ---- PARAMETERS -------
	const int widthPx  = 600;
	const int heightPx = 600;

	const double ambient = 0.2;

	int eyeDist  = 300;
	int depth = 3;
	// -----------------------
	
	const double heightImg = 200; 
	const double stepSize = heightImg / (float)heightPx;

	const double widthImg = stepSize * (float)widthPx;
	
	Vector3 eyePos = Vector3(0,0,-eyeDist);

	Image* img = new Image(widthPx, heightPx);
	list<Object*> scene;

	// --- Adding objects to the scene ---
	scene.push_front(new Sphere(Vector3(-75,0,100),  50, (RGB){0,200,0}, 0.5));
	scene.push_front(new Sphere(Vector3(-25,75,0),   50, (RGB){0,0,200}, 0.5));
	scene.push_front(new  Plane(Vector3(0,1,0),     100, (RGB){200,0,0}, 0.1));
	scene.push_front(new  Plane(Vector3(0,0,-1),    350, (RGB){0,0,0},     1));
	scene.push_front(new  Plane(Vector3(0,0,1),     650, (RGB){0,0,0},     1));
	// ----------------------------------

	list<Light> lights;

	// --- Adding lights to the scene ---
	// NOTE: Only one light is supported right now
	// 	 You can add more if you want, but weird
	// 	 things might happen.
	lights.push_front((Light){Vector3(100,500,-500), 100});
	// ----------------------------------

	// Shoot rays to render the scene
	printf("Rendering scene...\n");
	for (int i = 0; i < heightPx; i++)
	{
		for (int j = 0; j < widthPx; j++)
		{
			Vector3 pixPos = Vector3(-widthImg / 2 + (float)j*stepSize, heightImg / 2 - (float)i*stepSize, 0);
			Vector3 dir = (pixPos - eyePos).norm();

			img->setPixel(j, i, ray(eyePos, dir, scene, lights, ambient, depth));
			
		}
	}
	
	// Write final image to file
	printf("Writing image to file...\n");
	img->writePPM("test.bmp");
	printf("Done!\n");

	return 0;
}

RGB ray(Vector3& origin, Vector3& dir, list<Object*>& scn, list<Light>& lights, double ambient, int depth)
{

	list<Intersection> minimumList = intersection(origin, dir, scn);
	RGB pixColor;
	
	if (minimumList.size() < 1) 
	{
		pixColor.r = 0;
		pixColor.g = 0;
		pixColor.b = 0;
		return pixColor;
	}

	Intersection minimum = minimumList.front();
	pixColor = minimum.col;

	// Compute the ray towards the point light
	for ( auto light : lights )
	{
		Vector3 lVec = (light.pos - minimum.p);
		Vector3 lDir = lVec.norm();
		list<Intersection> shadowing = intersection(minimum.p, lDir, scn);
		if ((shadowing.size() > 0) && (lVec.len() > (shadowing.front().p - minimum.p).len())) 
		{
			pixColor.r *= ambient;
			pixColor.g *= ambient;
			pixColor.b *= ambient;
		} else
		{
			double cosine = lDir*minimum.n;
			if (cosine < 0) cosine = 0;
			cosine = ambient + (cosine * (1-ambient));
			pixColor.r *= cosine;
			pixColor.g *= cosine;
			pixColor.b *= cosine;
		}
	}
	if(depth <= 1) return pixColor;

	Vector3 reflexDir = ((2*(minimum.n * (((-1)*dir) * minimum.n)))+dir);
	RGB reflexCol = ray(minimum.p, reflexDir, scn, lights, ambient, depth-1);

	double reflex  = minimum.reflex;
	double nreflex = 1 - reflex;


	pixColor.r = nreflex*pixColor.r + reflex*reflexCol.r;
	pixColor.g = nreflex*pixColor.g + reflex*reflexCol.g;
	pixColor.b = nreflex*pixColor.b + reflex*reflexCol.b;
	

	return pixColor;
}

list<Intersection> intersection(Vector3& origin, Vector3& dir, list<Object*>& scn)
{
	list<Intersection> candidates;
	list<Intersection> result;

	for (auto obj : scn)
	{
		for ( auto x : obj->intersect(origin, dir)) candidates.push_front(x);
	}

	if (candidates.size() < 1) return result;

	Intersection minimum = candidates.front();
	double minimumLen    = (minimum.p - origin).len();
	candidates.pop_front();

	for (auto cand : candidates)
	{
		double localLen = (cand.p - origin).len();
		if ((localLen < minimumLen) && (localLen > 0))
		{
			minimum    = cand;
		}
	}


	result.push_front(minimum);

	return result;
}
