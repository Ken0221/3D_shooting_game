#include "System.h"
#include <stdio.h>
#include <SDL.h> // Using SDL
#include "SDL_image.h"  // Using SDL2 image extension library 
#include "SDL_ttf.h"

#include<SDL_mixer.h>

int System::init()
{
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return 0;
	}
	

	// Initialize PNG/JPG loading	
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;  // load support for the JPG and PNG image formats
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image failed: %s\n", IMG_GetError());
		return 0;
	}

	if (TTF_Init() == -1)
	{
		// https://www.libsdl.org/projects/old/SDL_ttf/docs/SDL_ttf_12.html#SEC12
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return 0;
	}

	//mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		// https://www.libsdl.org/projects/old/SDL_mixer/docs/SDL_mixer_14.html
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return 0;
	}

	return 1;
}

void System::close()
{
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


