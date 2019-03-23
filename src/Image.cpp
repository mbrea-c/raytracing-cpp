#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Image.h"

using namespace std;

Image::Image(int widthPx, int heightPx)
{
	surface = SDL_CreateRGBSurface(0, widthPx, heightPx, 32, 0,0,0,0);
	if (surface == NULL)
	{
		//TODO: Implement proper error handling
		printf("Something went wrong in Image::Image\n");
		exit(1);
	}

	this->widthPx  = widthPx;
	this->heightPx = heightPx;
}

Image::Image(int widthPx, int heightPx, Uint32 format)
{
	surface = SDL_CreateRGBSurfaceWithFormat(0, widthPx, heightPx, 32, format);
	if (surface == NULL)
	{
		//TODO: Implement proper error handling
		printf("Something went wrong in Image::Image\n");
		exit(1);
	}

	this->widthPx  = widthPx;
	this->heightPx = heightPx;
}

void Image::blitToSurface(SDL_Surface* dest)
{
	SDL_Rect stretchRect = {0,0, dest->w, dest->h};
	if (SDL_BlitScaled(surface, NULL, dest, &stretchRect) < 0)
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

void Image::setPixel(int x, int y, RGB color)
{
	this->setPixel(x, y, color.r, color.g, color.b);
}

void Image::writePPM(string filename)
{
	SDL_SaveBMP(surface, filename.c_str());
}

int Image::getHeight() {
	return heightPx;
}

int Image::getWidth() {
	return widthPx;
}

Image::~Image()
{
	SDL_FreeSurface(surface);
	surface = NULL;
}



