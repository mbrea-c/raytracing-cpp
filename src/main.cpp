#include <iostream>
#include <fstream>
#include <cmath>
#include <list>
#include "GameObject.h"
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
#include "RGB.h"
#include "Light.h"
#include "Image.h"
#include "Camera.h"

using namespace std;


// Takes care of SDL initialization
SDL_Window* init(int widthPx, int heightPx);

int main(int argc, char** argv)
{
	// ---- PARAMETERS -------
	const int widthPx  = 100;
	const int heightPx = 100;

	const int windowScale = 8;

	const double ambient = 0.2;

	int eyeDist  = 300;
	int depth = 2;

	// controls
	double turnSpeed = 0.05; // radians per second
	double moveSpeed = 5; // arbitrary units per second
	// -----------------------
	
	 //Parsing command-line arguments
	//for (int i = 0; i < argc; i++)
		//if (strcmp(argv[i], "-v") == 0) {
			
		//}

	// Compute window size
	const int windowWidth  = widthPx  * windowScale;
	const int windowHeight = heightPx * windowScale;

	Camera *mainCamera = new Camera(Vector3(0,220,-eyeDist), Vector3(0,-0.5,1), depth, ambient, eyeDist);

	// Create Image GameObject, initialize SDL for showing graphics
	// window
	Image* img = new Image(widthPx, heightPx);
	SDL_Window*  gWindow  = init(windowWidth, windowHeight);
	SDL_Surface* gSurface = SDL_GetWindowSurface(gWindow);
	list<GameObject*> scene;

	// --- Adding GameObjects to the scene ---
	scene.push_front(new  Plane(Vector3(0,1,0),     50, (RGB){200,0,0}, 0.6));
	scene.push_front(new  Plane(Vector3(0,-1,0),    1000,(RGB){0,140,255}, 0.0));
	scene.push_front(new Sphere(Vector3(-75,0,100),  50, (RGB){0,200,0}, 0.5));
	scene.push_front(new Sphere(Vector3(-25,75,0),   50, (RGB){0,0,200}, 0.5));
	// -----------------------------------

	list<Light> lights;

	// --- Adding lights to the scene ---
	// NOTE: Only one light is supported right now
	// 	 You can add more if you want, but weird
	// 	 things might happen.
	lights.push_front((Light){Vector3(100,500,-500), 100});
	// ----------------------------------

	// Main application loop
	SDL_Event eventHandler;
	const Uint8* keyboard = SDL_GetKeyboardState(NULL); // Valid throughout lifetime of application
	bool exitFlag = false;
	while (!exitFlag)
	{
		// Handle events
		while (SDL_PollEvent( &eventHandler ) != 0)
		{
			switch (eventHandler.type)
			{
				case SDL_QUIT:
					exitFlag = true;
					break;
				case SDL_KEYDOWN:
					switch (eventHandler.key.keysym.sym)
					{
						case SDLK_q:
							exitFlag = true;
							break;
						case SDLK_p:
							printf("Writing image to file...\n");
							img->writePPM("test.bmp");
							printf("Done!\n");
							break;
					}
					break;
			}

		}
		
		// Handle keyboard
		if (keyboard[SDL_SCANCODE_LSHIFT])
		{
			mainCamera->translateRelative(Vector3(0,-moveSpeed,0));
		}
		if (keyboard[SDL_SCANCODE_SPACE])
		{
			mainCamera->translateRelative(Vector3(0,moveSpeed,0));
		}
		if (keyboard[SDL_SCANCODE_A])
		{
			mainCamera->translateRelative(Vector3(-moveSpeed,0,0));
		}
		if (keyboard[SDL_SCANCODE_D])
		{
			mainCamera->translateRelative(Vector3(moveSpeed,0,0));
		}
		if (keyboard[SDL_SCANCODE_W])
		{
			mainCamera->translateRelative(Vector3(0,0,moveSpeed));
		}
		if (keyboard[SDL_SCANCODE_S])
		{
			mainCamera->translateRelative(Vector3(0,0,-moveSpeed));
		}
		if (keyboard[SDL_SCANCODE_UP])
		{
			mainCamera->rotate(0,-turnSpeed);
		}
		if (keyboard[SDL_SCANCODE_DOWN])
		{
			mainCamera->rotate(0,turnSpeed);
		}
		if (keyboard[SDL_SCANCODE_RIGHT])
		{
			mainCamera->rotate(-turnSpeed,0);
		}
		if (keyboard[SDL_SCANCODE_LEFT])
		{
			mainCamera->rotate(turnSpeed,0);
		}

		mainCamera->renderImage(img, scene, lights);

		// Writing final image to screen buffer
		img->blitToSurface(gSurface);
		SDL_UpdateWindowSurface(gWindow);

	}

	return 0;
}

SDL_Window* init(int widthPx, int heightPx)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize!: %s\n", SDL_GetError());
		return NULL;
	}

	//Create window
	SDL_Window* gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, 
	                           SDL_WINDOWPOS_UNDEFINED, widthPx, 
	                           heightPx, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created!: %s\n", SDL_GetError());
		return NULL;
	}

	return gWindow;
}


