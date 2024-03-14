#pragma once
#include "james.h"
#include "points.h"
#include "RenderWindow.h"
using namespace std;

class Obj_plane {
	points point[4];
	points draw_point[5];
	double x;
	double y;
	double z;
	SDL_FPoint screen_point[5];
	SDL_FPoint setScreenpoints(points, james, double, double, double);
	points setProjpoints(points, james);
	void judge(points[], james, points&);
	void back_change(james, points[]);
	void onein_back_change(james, points[]);
	void oneout_back_change(james, points[]);
	void back_change_oneout(james, points[]);
	void back_change_onein(james, points[]);
	void draw_onein_out(james, RenderWindow, bool, int, Uint32);

	void draw(james, RenderWindow, bool, Uint32);
	int state;

public:
	Obj_plane();
	Obj_plane(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4);
	void setPoints(double, double, double, double, double, double, double, double, double, double, double, double);
	void back_judge_draw(james, RenderWindow, bool, Uint32);
	int getState();
	points getPoint();
	friend bool IsSameSide(points, points, Obj_plane&);
};