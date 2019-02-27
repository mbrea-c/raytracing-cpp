#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <string>

class Image {
	private:
		SDL_Surface* surface;

	public:
		Image(int widthPx, int heightPx);
		void setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b);
		void writePPM(std::string filename);
		void blitToSurface(SDL_Surface* dest);
};

#endif
