#pragma once
#include "Bullet.h"
#include "james.h"
#include "object.h"
#include "RenderWindow.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>

class Zip :
    public Bullet
{
	int times;
	int fullziptimes;
public:
	Zip();
	Zip(james, Uint32);
	void reset(james);
	bool IsHitWall(Object[], int);
	void setpoint0();
	double getZipLength();
	points getpoint1();
	int ZipCount();
	void Lost_one_zip();

	void set_fullziptimes(double v) { 
		fullziptimes = v;
		times = v;
	}
	double get_fullziptimes() { return fullziptimes; }
};

