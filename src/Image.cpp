#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Image.h"

using namespace std;

Image::Image(int widthPx, int heightPx)
{
	//Uint32 rmask, gmask, bmask, amask;

//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	//rmask = 0xff000000;
	//gmask = 0x00ff0000;
	//bmask = 0x0000ff00;
	//amask = 0x000000ff;
//#else
	//rmask = 0x000000ff;
	//gmask = 0x0000ff00;
	//bmask = 0x00ff0000;
	//amask = 0xff000000;
//#endif

	surface = SDL_CreateRGBSurface(0, widthPx, heightPx, 32, 0,0,0,0);
	if (surface == NULL)
	{
		//TODO: Implement proper error handling
		printf("Something went wrong in Image::Image\n");
		exit(1);
	}
}

void Image::blitToSurface(SDL_Surface* dest)
{
	if (SDL_BlitSurface(surface, NULL, dest, NULL) < 0)
	{
		//TODO: Implement proper error handling
		printf("Something went wrong in Image::blitToSurface\n");
		exit(1);
	}
}

void Image::setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
	Uint32 pixel = SDL_MapRGB(surface->format, r, g, b);
	Uint8  bytesPerPixel = surface->format->BytesPerPixel;
	Uint8 *target_pixel = (Uint8 *) surface->pixels + y * surface->pitch + x * bytesPerPixel;
	
	*(Uint32*)target_pixel = pixel;
}

void Image::writePPM(string filename)
{
	//ofstream imgFile;
	//imgFile.open(filename);

	//imgFile << "P3" << endl;
	//imgFile << widthPx << " " << heightPx << endl;
	//imgFile << "255" << endl;

	//for (int i = 0; i < heightPx; i++)
	//{
		//for (int j = 0; j < widthPx; j++)
		//{
			//int r = buffer[i][j].r;
			//int g = buffer[i][j].g;
			//int b = buffer[i][j].b;

			//imgFile << r << " " << g << " " << b << " ";
		//}
		//imgFile << endl;
	//}
	
	SDL_SaveBMP(surface, filename.c_str());
}





