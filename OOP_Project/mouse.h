#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include "RenderWindow.h"
#include "System.h"
#include "constants.h"
#include "james.h"
#include "plane.h"
#include "points.h"
#include <iostream>
using namespace std;

class mouse
{
	int x;
	int y;
	bool mousecenter;
	double theta_x;
	double theta_y;
	bool show;
	int enable_mousemove;

	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param); // Timer callback 

public:
	mouse();
	mouse(int x1, int y1, bool center, double thetax, double thetay, bool show1, int enable);
	void startTimer(Uint32 t);
	void stopTimer();
	int* getx_adr();
	int* gety_adr();
	bool getMouseCenter();
	double gettheta_x();
	double gettheta_y();
	void mouse_settheta();
	void showCursor(bool);
	bool getShow();

	int getx();
	int gety();

};