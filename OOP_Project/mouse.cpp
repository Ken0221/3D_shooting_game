#include "mouse.h"
#include "RenderWindow.h"
#include <cmath>
#include <iostream>
using namespace std;

mouse::mouse() {
	x = WIDTH / 2;
	y = HEIGHT / 2;
	mousecenter = false;
	enable_mousemove = 1;
	show = false;

	timerID = 0;
	time = 0;
	theta_x = 0;
	theta_y = 0;
}

mouse::mouse(int x1, int y1, bool center, double thetax, double thetay, bool show1, int enable) {
	x = x1;
	y = y1;
	mousecenter = center;
	enable_mousemove = enable;
	show = show1;

	timerID = 0;
	time = 0;
	theta_x = thetax;
	theta_y = thetay;
}

bool mouse::getMouseCenter() {
	return mousecenter;
}

Uint32 mouse::changeData(Uint32 interval, void* param) { // Timer callback 
	mouse* p = (mouse*)param;

	if (p->time != 0)
	{
		p->enable_mousemove = (p->enable_mousemove + 1) % 2;  // image enable_mousemove	
		if (p->enable_mousemove == 0)
			p->mousecenter = true;
		else
			p->mousecenter = false;
		return interval;
	}
	else
	{
		return 0;
	}
}

void mouse::startTimer(Uint32 t) {
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void mouse::stopTimer() {
	time = 0;
	SDL_RemoveTimer(timerID);
}

int* mouse::getx_adr() {
	return &x;
}

int* mouse::gety_adr() {
	return &y;
}

void mouse::mouse_settheta() {
	double xr = x - WIDTH / 2;
	xr /= 4;
	
	theta_x = atan2(xr, DISTANCE_PROJPLANE_FROM_JAMES) / M_PI * 180;
	theta_x /= 2;

	double yr = y - HEIGHT / 2;
	yr /= 4;
	
	theta_y = atan2(yr, DISTANCE_PROJPLANE_FROM_JAMES) / M_PI * 180;
	theta_y /= 2;


	
}

double mouse::gettheta_x() {
	return theta_x;
}

double mouse::gettheta_y() {
	return theta_y;
}

void mouse::showCursor(bool t) {
	show = t;
}

bool mouse::getShow() {
	return show;
}

int mouse::getx() {
	return x;
}

int mouse::gety() {
	return y;
}