#include"plane.h"
#include"constants.h"
#include"james.h"
#include"RenderWindow.h"
#include<math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include<math.h>
#include<iostream>
using namespace std;

Obj_plane::Obj_plane() {
	point[0].x = 0; point[0].y = 0; point[0].z = 0; point[0].state = INSIDE;
	point[1].x = 0; point[1].y = 0; point[1].z = 0; point[1].state = INSIDE;
	point[2].x = 0; point[2].y = 0; point[2].z = 0; point[2].state = INSIDE;
	point[3].x = 0; point[3].y = 0; point[3].z = 0; point[3].state = INSIDE;

	x = 0; y = 0; z = 0;
	for (int i = 0; i < 4; i++) {
		x += point[i].x;
		y += point[i].y;
		z += point[i].z;
	}
	x /= 4; y /= 4; z /= 4;

	state = INSIDE;
	for (int i = 0; i < 4; i++) {
		draw_point[i].x = point[i].x;
		draw_point[i].y = point[i].y;
		draw_point[i].z = point[i].z;
	}
	draw_point[4].x = 0; draw_point[4].y = 0; draw_point[4].z = 0;
}

Obj_plane::Obj_plane(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4) {
	point[0].x = x1; point[0].y = y1; point[0].z = z1; point[0].state = INSIDE;
	point[1].x = x2; point[1].y = y2; point[1].z = z2; point[1].state = INSIDE;
	point[2].x = x3; point[2].y = y3; point[2].z = z3; point[2].state = INSIDE;
	point[3].x = x4; point[3].y = y4; point[3].z = z4; point[3].state = INSIDE;

	x = 0; y = 0; z = 0;
	for (int i = 0; i < 4; i++) {
		x += point[i].x;
		y += point[i].y;
		z += point[i].z;
	}
	x /= 4; y /= 4; z /= 4;

	state = INSIDE;
	for (int i = 0; i < 4; i++) {
		draw_point[i].x = point[i].x;
		draw_point[i].y = point[i].y;
		draw_point[i].z = point[i].z;
	}
	draw_point[4].x = 0; draw_point[4].y = 0; draw_point[4].z = 0;
}

void Obj_plane::setPoints(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4) {
	point[0].x = x1; point[0].y = y1; point[0].z = z1; point[0].state = INSIDE;
	point[1].x = x2; point[1].y = y2; point[1].z = z2; point[1].state = INSIDE;
	point[2].x = x3; point[2].y = y3; point[2].z = z3; point[2].state = INSIDE;
	point[3].x = x4; point[3].y = y4; point[3].z = z4; point[3].state = INSIDE;

	x = 0; y = 0; z = 0;
	for (int i = 0; i < 4; i++) {
		x += point[i].x;
		y += point[i].y;
		z += point[i].z;
	}
	x /= 4; y /= 4; z /= 4;

	state = INSIDE;
	for (int i = 0; i < 4; i++) {
		draw_point[i].x = point[i].x;
		draw_point[i].y= point[i].y;
		draw_point[i].z = point[i].z;
	}
	draw_point[4].x = 0; draw_point[4].y = 0; draw_point[4].z = 0;
}

points Obj_plane::setProjpoints(points p, james j) {
	points proj_point;
	double tson = DISTANCE_PROJPLANE_FROM_JAMES;
	double tmom = sqrt((p.x - j.getx()) * (p.x - j.getx()) + (p.y - j.gety()) * (p.y - j.gety()) + (p.z - j.getz()) * (p.z - j.getz()));
	double t = tson / tmom;
	proj_point.x = j.getx() + t * (p.x - j.getx());
	proj_point.y = j.gety() + t * (p.y - j.gety());
	proj_point.z = j.getz() + t * (p.z - j.getz());

	

	return proj_point;
}

SDL_FPoint Obj_plane::setScreenpoints(points p, james j, double d, double e, double f) {

	double t = (p.z - (j.getz() + j.getc())) / f; // since f == tt

	points temp;
	temp.x = p.x - t * d;
	temp.y = p.y - t * e;
	temp.z = p.z - t * f;

	SDL_FPoint scr_point;
	double cosson = j.geta() * (temp.x - j.getx()) + j.getb() * (temp.y - j.gety()) + j.getc() * (temp.z - j.getz());
	double cosmom = DISTANCE_PROJPLANE_FROM_JAMES * sqrt(((temp.x - j.getx()) * (temp.x - j.getx()) + (temp.y - j.gety()) * (temp.y - j.gety()) + (temp.z - j.getz()) * (temp.z - j.getz())));
	double fr = cosson / cosmom;
	if (fr >= 1)
		fr = 1;
	else if (fr <= -1)
		fr = -1;
	double theta = acos(fr);
	double dx = (WIDTH / 2.0) * (theta / VISIONANGLE_W);
	double cross_for_x = j.geta() * (p.y - j.gety()) - j.getb() * (p.x - j.getx());

	if (cross_for_x < 0)
		scr_point.x = (WIDTH / 2.0) + dx;
	else
		scr_point.x = (WIDTH / 2.0) - dx;

	

	points cross_with_temp;
	cross_with_temp.x = (p.y - j.gety()) * j.getc() - (p.z - j.getz()) * (temp.y - j.gety());
	cross_with_temp.y = (p.z - j.getz()) * (temp.x - j.getx()) - (p.x - j.getx()) * j.getc();
	cross_with_temp.z = (p.x - j.getx()) * (temp.y - j.gety()) - (p.y - j.gety()) * (temp.x - j.getx());
	cosson = sqrt((temp.x - j.getx()) * (temp.x - j.getx()) + (temp.y - j.gety()) * (temp.y - j.gety()) + (temp.z - j.getz()) * (temp.z - j.getz()));
	cosmom = sqrt((p.x - j.getx()) * (p.x - j.getx()) + (p.y - j.gety()) * (p.y - j.gety()) + (p.z - j.getz()) * (p.z - j.getz()));
	fr = cosson / cosmom;
	if (fr >= 1)
		fr = 1;
	else if (fr <= -1)
		fr = -1;
	double phi = acos(fr);
	double dy = (HEIGHT / 2.0) * (phi / VISIONANGLE_H);
	double cross_for_y = j.geta() * cross_with_temp.y - j.getb() * cross_with_temp.x ;

	if (cross_for_y > 0)
		scr_point.y = (HEIGHT / 2.0) - dy;
	else
		scr_point.y = (HEIGHT / 2.0) + dy;

	

	scr_point.x -= WIDTH / 4;

	return scr_point;
}

void Obj_plane::draw(james j, RenderWindow rw, bool drawstate, Uint32 color) {
	double tt = sqrt(j.geta() * j.geta() + j.getb() * j.getb());
	double d = -(j.getc() / tt) * j.geta();
	double e = -(j.getc() / tt) * j.getb();
	
	Sint16 xt[4], yt[4];
	for (int i = 0; i < 4; i++) {
		
		points pj_point;
		pj_point = setProjpoints(draw_point[i], j);//point->draw_point
		screen_point[i] = setScreenpoints(pj_point, j, d, e, /*f*/ tt);
		xt[i] = screen_point[i].x;
		yt[i] = screen_point[i].y;
	}

	if (drawstate) {
		filledPolygonRGBA(rw.getRenderer(), xt, yt, 4, (color / 0x10000) % 0x100, (color / 0x100) % 0x100, color % 0x100, color / 0x1000000);
		
	}

	for (int i = 0; i < 4; i++) {
		int k = (i != 3) ? i + 1 : 0;
		if (!(point[i].state == BACK && point[k].state == BACK)) {
			SDL_SetRenderDrawColor(rw.getRenderer(), 0, 0, 0, 255);
			SDL_RenderDrawLineF(rw.getRenderer(), screen_point[i].x, screen_point[i].y, screen_point[k].x, screen_point[k].y);
		}
	}
}

void Obj_plane::draw_onein_out(james j, RenderWindow rw, bool drawstate, int n, Uint32 color) {
	double tt = sqrt(j.geta() * j.geta() + j.getb() * j.getb());
	double d = -(j.getc() / tt) * j.geta();
	double e = -(j.getc() / tt) * j.getb();
	
	Sint16 xt[5], yt[5];
	for (int i = 0; i < n; i++) {
		
		points pj_point;
		pj_point = setProjpoints(draw_point[i], j);//point->draw_point
		screen_point[i] = setScreenpoints(pj_point, j, d, e, /*f*/ tt);
		xt[i] = screen_point[i].x;
		yt[i] = screen_point[i].y;
	}

	if (drawstate) {
		filledPolygonRGBA(rw.getRenderer(), xt, yt, n, (color / 0x10000) % 0x100, (color / 0x100) % 0x100, color % 0x100, color / 0x1000000);
		
		for (int i = 1; i < n; i++) {
			int k = (i + 1) % n;
			SDL_SetRenderDrawColor(rw.getRenderer(), 0, 0, 0, 255);
			SDL_RenderDrawLineF(rw.getRenderer(), screen_point[i].x, screen_point[i].y, screen_point[k].x, screen_point[k].y);
		}
	}
}

void Obj_plane::back_judge_draw(james j, RenderWindow rw, bool drawstate, Uint32 color) {//try
	state = OUTSIDE;//reset state
	for (int i = 0; i < 4; i++) {
		draw_point[i] = point[i];

		if (j.geta() * (point[i].x - j.getx()) + j.getb() * (point[i].y - j.gety()) + j.getc() * (point[i].z - j.getz()) <= 0) {//判斷是否在背面
			point[i].state = BACK;
		}
		else {
			point[i].state = FRONT;
			state++;
		}
		
	}

	if (state == THROUGH)
		back_change(j, point);
	
	else if (state == ONEOUT) {
		back_change_oneout(j, point);
		draw_onein_out(j, rw, drawstate, 5, color);
	}
	else if (state == ONEIN) {
		back_change_onein(j, point);
		draw_onein_out(j, rw, drawstate, 3, color);
	}
	if (state == INSIDE || state == THROUGH)
		draw(j, rw, drawstate, color);
}

void Obj_plane::back_change(james j, points p[4]) {//try
	for (int i = 0; i < 4; i++) {
		int k = (i + 1) % 4;
		if (point[i].state == BACK && point[k].state == BACK) {
			
			int jj = (i != 0) ? i - 1 : 3;//point[jj](內)對point[i](外)
			int tt = (k != 3) ? k + 1 : 0;//point[tt](內)對point[k](外)

			double tison = j.geta() * (point[i].x - j.getx()) + j.getb() * (point[i].y - j.gety()) + j.getc() * (point[i].z - j.getz());
			double timom = j.geta() * (point[i].x - point[jj].x) + j.getb() * (point[i].y - point[jj].y) + j.getc() * (point[i].z - point[jj].z);
			double ti = (timom != 0) ? tison / timom : 0;

			

			draw_point[i].x = point[i].x + (point[jj].x - point[i].x) * (ti + 0.01);//為了讓cross不要= 0
			draw_point[i].y = point[i].y + (point[jj].y - point[i].y) * (ti + 0.01);
			draw_point[i].z = point[i].z + (point[jj].z - point[i].z) * (ti + 0.01);

			

			double tkson = j.geta() * (point[k].x - j.getx()) + j.getb() * (point[k].y - j.gety()) + j.getc() * (point[k].z - j.getz());
			double tkmom = j.geta() * (point[k].x - point[tt].x) + j.getb() * (point[k].y - point[tt].y) + j.getc() * (point[k].z - point[tt].z);
			double tk = (tkmom != 0) ? tkson / tkmom : 0;

			

			draw_point[k].x = point[k].x + (point[tt].x - point[k].x) * (tk + 0.01);
			draw_point[k].y = point[k].y + (point[tt].y - point[k].y) * (tk + 0.01);
			draw_point[k].z = point[k].z + (point[tt].z - point[k].z) * (tk + 0.01);

			

			break;
		}
	}
}

void Obj_plane::back_change_oneout(james j, points p[4]) {
	for (int i = 0; i < 4; i++) {
		if (point[i].state == BACK) {
			int jj = (i != 0) ? i - 1 : 3;//point[jj](內)對point[i](外)
			int tt = (i != 3) ? i + 1 : 0;//point[tt](內)對point[k](外)

			double tison = j.geta() * (point[i].x - j.getx()) + j.getb() * (point[i].y - j.gety()) + j.getc() * (point[i].z - j.getz());
			double timom = j.geta() * (point[i].x - point[jj].x) + j.getb() * (point[i].y - point[jj].y) + j.getc() * (point[i].z - point[jj].z);
			double ti = (timom != 0) ? tison / timom : 0;

			draw_point[0].x = point[i].x + (point[jj].x - point[i].x) * (ti + 0.01);//為了讓cross不要= 0
			draw_point[0].y = point[i].y + (point[jj].y - point[i].y) * (ti + 0.01);
			draw_point[0].z = point[i].z + (point[jj].z - point[i].z) * (ti + 0.01);

			double tkson = j.geta() * (point[i].x - j.getx()) + j.getb() * (point[i].y - j.gety()) + j.getc() * (point[i].z - j.getz());
			double tkmom = j.geta() * (point[i].x - point[tt].x) + j.getb() * (point[i].y - point[tt].y) + j.getc() * (point[i].z - point[tt].z);
			double tk = (tkmom != 0) ? tkson / tkmom : 0;

			draw_point[1].x = point[i].x + (point[tt].x - point[i].x) * (tk + 0.01);
			draw_point[1].y = point[i].y + (point[tt].y - point[i].y) * (tk + 0.01);
			draw_point[1].z = point[i].z + (point[tt].z - point[i].z) * (tk + 0.01);

			draw_point[2] = point[(i + 1) % 4];
			draw_point[3] = point[(i + 2) % 4];
			draw_point[4] = point[(i + 3) % 4];

			break;
		}
	}
}

void Obj_plane::back_change_onein(james j, points p[4]) {
	for (int i = 0; i < 4; i++) {
		if (point[i].state == FRONT) {
			int jj = (i != 0) ? i - 1 : 3;
			int tt = (i + 1) % 4;

			double tison = j.geta() * (point[i].x - j.getx()) + j.getb() * (point[i].y - j.gety()) + j.getc() * (point[i].z - j.getz());
			double timom = j.geta() * (point[i].x - point[jj].x) + j.getb() * (point[i].y - point[jj].y) + j.getc() * (point[i].z - point[jj].z);
			double ti = (timom != 0) ? tison / timom : 0;

			draw_point[0].x = point[i].x + (point[jj].x - point[i].x) * (ti - 0.01);//為了讓cross不要= 0
			draw_point[0].y = point[i].y + (point[jj].y - point[i].y) * (ti - 0.01);
			draw_point[0].z = point[i].z + (point[jj].z - point[i].z) * (ti - 0.01);

			double tkson = j.geta() * (point[i].x - j.getx()) + j.getb() * (point[i].y - j.gety()) + j.getc() * (point[i].z - j.getz());
			double tkmom = j.geta() * (point[i].x - point[tt].x) + j.getb() * (point[i].y - point[tt].y) + j.getc() * (point[i].z - point[tt].z);
			double tk = (tkmom != 0) ? tkson / tkmom : 0;



			draw_point[1].x = point[i].x + (point[tt].x - point[i].x) * (tk - 0.01);
			draw_point[1].y = point[i].y + (point[tt].y - point[i].y) * (tk - 0.01);
			draw_point[1].z = point[i].z + (point[tt].z - point[i].z) * (tk - 0.01);

			draw_point[2] = point[i];

			break;
		}
	}
}

int Obj_plane::getState() {
	return state;
}

points Obj_plane::getPoint() {
	points a;
	a.x = x; a.y = y; a.z = z;
	return a;
}

bool IsSameSide(points a, points b, Obj_plane& plane) {
	points v1, v0, n, r1, r2;
	v1.x = plane.point[1].x - plane.x; 	v1.y = plane.point[1].y - plane.y; 	v1.z = plane.point[1].z - plane.z;
	v0.x = plane.point[0].x - plane.x; 	v0.y = plane.point[0].y - plane.y; 	v0.z = plane.point[0].z - plane.z;
	n.x = v1.y * v0.z - v1.z * v0.y; n.y = v1.z * v0.x - v1.x * v0.z; n.z = v1.x * v0.y - v1.y * v0.x;
	r1.x = a.x - plane.x; r1.y = a.y - plane.y; r1.z = a.z - plane.z;
	r2.x = b.x - plane.x; r2.y = b.y - plane.y; r2.z = b.z - plane.z;
	double ans = (r1.x * n.x + r1.y * n.y + r1.z * n.z) * (r2.x * n.x + r2.y * n.y + r2.z * n.z);
	
	if (ans > 0) 
		return true;
	else
		return false;
}
