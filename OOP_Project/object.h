#pragma once
#include"plane.h"
#include"james.h"

class Object {
	Obj_plane plane[6];
	double x;
	double y;
	double z;
	Uint32 color;
	int state;
	bool drawState;
	
public:
	Object();
	Object(Uint32);
	Object(const points[]);
	Object(const points[], Uint32);
	void setPlane(const points[]);
	void setcolor(Uint32);
	void draw(james, RenderWindow);
	void draw_and_james(james, RenderWindow, james, double, bool);
	int getState();
	points getPoint();
	double getHighest();
};