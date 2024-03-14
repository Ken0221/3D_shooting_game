#pragma once
#include "points.h"
#include "james.h"
#include "object.h"
#include "RenderWindow.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>

class Bullet
{
protected:
	points point[2];
	points draw_point[2];
	SDL_FPoint screen_point[2];
	points dir;
	double speed;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param); // Timer callback 
	bool show;
	Uint32 flytime;
	int state;
	Uint32 color;

	SDL_FPoint setScreenpoints(points, james, double, double, double);
	points setProjpoints(points, james);
	void judge(points[], james, points&);
	void back_change(james, points[]);
	void draw_drawpoints(james, RenderWindow, int);
	double getHorizonDist(int, points);

	int IsZip;
	bool Ishitwall;
	bool Ishit;


public:
	Bullet();
	Bullet(james, Uint32);
	void draw(james, RenderWindow, int);
	void startTimer(Uint32 t);
	void stopTimer();
	bool timerExpired();
	void setShow(bool);
	bool getShow();
	void bullet_move();
	virtual void reset(james);

	bool IsHit(points);
	bool getIsHit();
	void setIsHit(bool);
	virtual bool IsHitWall(Object[], int);
};

