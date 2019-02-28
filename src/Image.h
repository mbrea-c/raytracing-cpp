#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <string>
#include "RGB.h"

class Image {
	private:
		SDL_Surface* surface;
		int widthPx, heightPx;

	public:
		Image(int widthPx, int heightPx);
		~Image();
		void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
		void setPixel(int x, int y, RGB color);
		void writePPM(std::string filename);
		void blitToSurface(SDL_Surface* dest);
};

#endif
