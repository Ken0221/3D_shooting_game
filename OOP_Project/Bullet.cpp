#include "Bullet.h"
#include "james.h"
#include "RenderWindow.h"
#include "points.h"
#include "constants.h"
#include <iostream>
using namespace std;

Bullet::Bullet()
{
	speed = BULLET_SPEED;
	time = 0;
	flytime = BULLET_FLYTIME;
	show = false;
	IsZip = 0;
	Ishitwall = false;
	Ishit = false;
	color = 0X00000000;
}

Bullet::Bullet(james j, Uint32 c) {
	speed = BULLET_SPEED;
	time = 0;
	flytime = BULLET_FLYTIME;
	show = false;
	IsZip = 0;
	Ishitwall = false;
	Ishit = false;
	color = c;
	reset(j);
}

void Bullet::draw(james j, RenderWindow rw, int m) {
	state = OUTSIDE;//reset state
	for (int i = 0; i < 2; i++) {
		draw_point[i] = point[i];

		if (j.geta() * (point[i].x - j.getx()) + j.getb() * (point[i].y - j.gety()) + j.getc() * (point[i].z - j.getz()) <= 0) {//判斷是否在背面
			point[i].state = BACK;
		}
		else {
			point[i].state = FRONT;
			state++;
		}
		
	}

	if (state == ONEIN)
		back_change(j, point);
	if (state == 2 || state == ONEIN)
		draw_drawpoints(j, rw, m);
}

void Bullet::back_change(james j, points p[2]) {
	for (int i = 0; i < 2; i++) {
		int k = (i + 1) % 2;
		if (point[i].state == BACK) {
			
			int jj = (i != 0) ? i - 1 : 1;//point[jj](內)對point[i](外)

			double tison = j.geta() * (point[i].x - j.getx()) + j.getb() * (point[i].y - j.gety()) + j.getc() * (point[i].z - j.getz());
			double timom = j.geta() * (point[i].x - point[jj].x) + j.getb() * (point[i].y - point[jj].y) + j.getc() * (point[i].z - point[jj].z);
			double ti = (timom != 0) ? tison / timom : 0;

			

			draw_point[i].x = point[i].x + (point[jj].x - point[i].x) * (ti + 0.01);//為了讓cross不要= 0
			draw_point[i].y = point[i].y + (point[jj].y - point[i].y) * (ti + 0.01);
			draw_point[i].z = point[i].z + (point[jj].z - point[i].z) * (ti + 0.01);

			draw_point[k] = point[k];

			break;
		}
	}

}

void Bullet::draw_drawpoints(james j, RenderWindow rw, int m) {
	double tt = sqrt(j.geta() * j.geta() + j.getb() * j.getb());
	double d = -(j.getc() / tt) * j.geta();
	double e = -(j.getc() / tt) * j.getb();
	
	for (int i = 0; i < 2; i++) {
		
		points pj_point;
		pj_point = setProjpoints(draw_point[i], j);//point->draw_point

		

		screen_point[i] = setScreenpoints(pj_point, j, d, e, /*f*/ tt);
		if (m == 2) {
			screen_point[i].x -= WIDTH / 4;
		}
	}

	
	thickLineRGBA(rw.getRenderer(), screen_point[0].x, screen_point[0].y, screen_point[1].x, screen_point[1].y, 2, (color / 0x10000) % 0x100, (color / 0x100) % 0x100, color % 0x100, color / 0x1000000);
}

points Bullet::setProjpoints(points p, james j) {
	points proj_point;
	double tson = DISTANCE_PROJPLANE_FROM_JAMES;
	double tmom = sqrt((p.x - j.getx()) * (p.x - j.getx()) + (p.y - j.gety()) * (p.y - j.gety()) + (p.z - j.getz()) * (p.z - j.getz()));
	double t = tson / tmom;
	proj_point.x = j.getx() + t * (p.x - j.getx());
	proj_point.y = j.gety() + t * (p.y - j.gety());
	proj_point.z = j.getz() + t * (p.z - j.getz());



	return proj_point;
}

SDL_FPoint Bullet::setScreenpoints(points p, james j, double d, double e, double f) {
	

	double t = (p.z - (j.getz() + j.getc())) / f; // since f == tt

	points temp;
	temp.x = p.x - t * d;
	temp.y = p.y - t * e;
	temp.z = p.z - t * f;

	SDL_FPoint scr_point;
	double cosson = j.geta() * (temp.x - j.getx()) + j.getb() * (temp.y - j.gety()) + j.getc() * (temp.z - j.getz());
	double cosmom = DISTANCE_PROJPLANE_FROM_JAMES * sqrt(((temp.x - j.getx()) * (temp.x - j.getx()) + (temp.y - j.gety()) * (temp.y - j.gety()) + (temp.z - j.getz()) * (temp.z - j.getz())));
	double theta = acos(cosson / cosmom);
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
	double phi = acos(cosson / cosmom);
	double dy = (HEIGHT / 2.0) * (phi / VISIONANGLE_H);
	double cross_for_y = j.geta() * cross_with_temp.y - j.getb() * cross_with_temp.x;

	if (cross_for_y > 0)
		scr_point.y = (HEIGHT / 2.0) - dy;
	else
		scr_point.y = (HEIGHT / 2.0) + dy;

	

	return scr_point;
}

Uint32 Bullet::changeData(Uint32 interval, void* param) { // Timer callback 
	Bullet* p = (Bullet*)param;
	if (p->show == true && !p->Ishitwall) {
		int n = p->IsZip;
		for (int i = 1; i >= n; i--) {
			p->point[i].x += p->speed * p->dir.x * 0.01;
			p->point[i].y += p->speed * p->dir.y * 0.01;
			p->point[i].z += p->speed * p->dir.z * 0.01;
		}
	}
	
	return interval;
}

void Bullet::startTimer(Uint32 t) {
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void Bullet::stopTimer() {
	time = 0;
	SDL_RemoveTimer(timerID);
}

bool Bullet::timerExpired() {
	if (flytime <= 0) {
		flytime = BULLET_FLYTIME;
		return true;
	}
	else {
		flytime -= time; // time是每個循環步的時間，可以根據需要調整
		return false;
	}
}

void Bullet::bullet_move() {
	for (int i = 0; i < 2; i++) {
		point[i].x += speed * dir.x * 0.01;
		point[i].y += speed * dir.y * 0.01;
		point[i].z += speed * dir.z * 0.01;
	}
}

void Bullet::setShow(bool b) {
	show = b;
}

bool Bullet::getShow() {
	return show;
}

void Bullet::reset(james j) {
	point[0].x = j.getx() + j.geta() * 0.01 + j.getb() * 0.1;
	point[0].y = j.gety() + j.getb() * 0.01 - j.geta() * 0.1;
	point[0].z = j.getz() - 50;
	dir.x = j.getx() + j.geta() * 100 - point[0].x;
	dir.y = j.gety() + j.getb() * 100 - point[0].y;
	dir.z = (j.getz() - 50) + j.getc() * 100 - point[0].z;
	point[1].x = point[0].x + dir.x / 50;
	point[1].y = point[0].y + dir.y / 50;
	point[1].z = point[0].z + dir.z / 50;

	flytime = BULLET_FLYTIME;
}

bool Bullet::IsHit(points pos) {
	for (int i = 0; i < 2; i++) {
		if (getHorizonDist(i, pos) <= JAMES_WIDTH * 1.5 && point[i].z <= pos.z *1.1&& point[i].z >= pos.z - JAMES_HEIGHT) {
			
			Ishit = true;
			return true;
		}
	}
	Ishit = false;
	return false;
}

bool Bullet::IsHitWall(Object wall[], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2; j++) {
			if (point[j].x <= wall[i].getPoint().x + CUBE_RADIUS && point[j].x >= wall[i].getPoint().x - CUBE_RADIUS &&
				point[j].y <= wall[i].getPoint().y + CUBE_RADIUS && point[j].y >= wall[i].getPoint().y - CUBE_RADIUS &&
				point[j].z <= wall[i].getPoint().z + CUBE_RADIUS && point[j].z >= wall[i].getPoint().z - CUBE_RADIUS) {
				
				return true;
			}
		}
	}
	return false;
}

bool Bullet::getIsHit() {
	return Ishit;
}

void Bullet::setIsHit(bool b) {
	Ishit = b;
}

double Bullet::getHorizonDist(int i, points pos) {
	return sqrt((point[i].x - pos.x) * (point[i].x - pos.x) + (point[i].y - pos.y) * (point[i].y - pos.y));
}
