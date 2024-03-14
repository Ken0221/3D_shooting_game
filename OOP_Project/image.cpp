#include "Image.h"
#include "SDL_image.h" 
#include <stdio.h>
#include <SDL.h> // Using SDL
#include <string.h>
#include "constants.h"


Image::Image()
{
	setPath(NULL);
}

Image::Image(const char* path, SDL_Renderer* renderer)
{
	setPath(path);
	setColorKey(NO_TRANSPARENT_BG);
	setRenderer(renderer);

	generateTexture();
}

Image::Image(const char* path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	setPath(path);
	setColorKey({ r, g, b, 255 });
	setRenderer(renderer);

	generateTexture();
}

void Image::generateTexture()
{
	// Load a surface from a PNG file.	
	SDL_Surface* imgSurface = IMG_Load(path);
	if (imgSurface == NULL)
	{
		// Call IMG_GetError to get the error string.
		printf("SDL_LoadBMP failed: %s\n", IMG_GetError());
		exit(0);
	}
	else
	{
		
		if (colorKey.a == 255)
		{
			
			SDL_SetColorKey(imgSurface, true, SDL_MapRGB(imgSurface->format, colorKey.r, colorKey.g, colorKey.b));
		}
		

			
		texture = SDL_CreateTextureFromSurface(renderer, imgSurface);

		

		if (texture == NULL)
		{
			printf("SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
		}

		width = imgSurface->w;
		height = imgSurface->h;

		
		SDL_FreeSurface(imgSurface);
	}
}

void Image::close()
{
	
	SDL_DestroyTexture(texture);
}

void Image::draw()
{
	SDL_Rect* d = &dstRegion, * s = &srcRegion;

	if (dstRegion.x == ALLREGION)
	{
		d = NULL;
	}
	if (srcRegion.x == ALLREGION)
	{
		s = NULL;
	}

	

	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) == -1)
	{
		printf("SDL_SetTextureBlendMode failed: %s\n", SDL_GetError());
		return;
	}

	// Modulate texture alpha	
	if (SDL_SetTextureAlphaMod(texture, alpha) == -1)
	{
		printf("SDL_SetTextureAlphaMod failed: %s\n", SDL_GetError());
		return;
	}

	
	SDL_RenderCopyEx(renderer, texture, s, d, angle, &center, flip);
	
}

void Image::draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src)
{
	setSrcRegion(src);
	setDstRegion(dst);

	draw();
}


int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}

void Image::setPath(const char* p)
{
	path = new char[strlen(p) + 1];
	strcpy_s(path, strlen(p) + 1, p);
}

void Image::setColorKey(SDL_Color c)
{
	colorKey = c;
}

void Image::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}

void Image::setSrcRegion(SDL_Rect s)
{
	srcRegion = s;
}

void Image::setDstRegion(SDL_Rect d)
{
	dstRegion = d;
}

/*new for blood and direction*/
void Image::setAlpha(int a)
{
	alpha = a;
}

int Image::getAlpha()
{
	return alpha;
}

//new for blood////////////////////////
void Image::draw(SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect src, SDL_Point center, double angle)
{
	setSrcRegion(src);
	setDstRegion(dst);
	setCenterAngle(center, angle);


	draw();
}
// New in this example
void Image::setCenterAngle(SDL_Point c, double a)
{
	center = c;
	angle = a;
}

// New in this example
void Image::setFlip(SDL_RendererFlip f)
{
	flip = f;
}

// New in this example
double Image::getAngle()
{
	return angle;
}