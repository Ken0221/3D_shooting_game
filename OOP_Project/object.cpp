#include "object.h"
#include "points.h"
#include "plane.h"
#include "constants.h"
#include <stdlib.h>
#include <iostream>

Object::Object() { state = INSIDE; drawState = false; }

Object::Object(const points points[8]) {
	state = INSIDE;
	drawState = false;
	plane[0].setPoints(points[0].x, points[0].y, points[0].z, points[1].x, points[1].y, points[1].z, points[2].x, points[2].y, points[2].z, points[3].x, points[3].y, points[3].z);
	plane[1].setPoints(points[2].x, points[2].y, points[2].z, points[3].x, points[3].y, points[3].z, points[7].x, points[7].y, points[7].z, points[6].x, points[6].y, points[6].z);
	plane[2].setPoints(points[4].x, points[4].y, points[4].z, points[5].x, points[5].y, points[5].z, points[6].x, points[6].y, points[6].z, points[7].x, points[7].y, points[7].z);
	plane[3].setPoints(points[0].x, points[0].y, points[0].z, points[1].x, points[1].y, points[1].z, points[5].x, points[5].y, points[5].z, points[4].x, points[4].y, points[4].z);
	plane[4].setPoints(points[0].x, points[0].y, points[0].z, points[3].x, points[3].y, points[3].z, points[7].x, points[7].y, points[7].z, points[4].x, points[4].y, points[4].z);
	plane[5].setPoints(points[1].x, points[1].y, points[1].z, points[2].x, points[2].y, points[2].z, points[6].x, points[6].y, points[6].z, points[5].x, points[5].y, points[5].z);
	x = (points[0].x + points[4].x) / 2;
	y = (points[0].y + points[1].y) / 2;
	z = (points[0].z + points[3].z) / 2;

	
	color = 0x00000000;
}

Object::Object(const points points[8], Uint32 colorin ) {
	state = INSIDE;
	drawState = true;
	plane[0].setPoints(points[0].x, points[0].y, points[0].z, points[1].x, points[1].y, points[1].z, points[2].x, points[2].y, points[2].z, points[3].x, points[3].y, points[3].z);
	plane[1].setPoints(points[2].x, points[2].y, points[2].z, points[3].x, points[3].y, points[3].z, points[7].x, points[7].y, points[7].z, points[6].x, points[6].y, points[6].z);
	plane[2].setPoints(points[4].x, points[4].y, points[4].z, points[5].x, points[5].y, points[5].z, points[6].x, points[6].y, points[6].z, points[7].x, points[7].y, points[7].z);
	plane[3].setPoints(points[0].x, points[0].y, points[0].z, points[1].x, points[1].y, points[1].z, points[5].x, points[5].y, points[5].z, points[4].x, points[4].y, points[4].z);
	plane[4].setPoints(points[0].x, points[0].y, points[0].z, points[3].x, points[3].y, points[3].z, points[7].x, points[7].y, points[7].z, points[4].x, points[4].y, points[4].z);
	plane[5].setPoints(points[1].x, points[1].y, points[1].z, points[2].x, points[2].y, points[2].z, points[6].x, points[6].y, points[6].z, points[5].x, points[5].y, points[5].z);
	x = (points[0].x + points[4].x) / 2;
	y = (points[0].y + points[1].y) / 2;
	z = (points[0].z + points[3].z) / 2;
	state = INSIDE;
	drawState = true;
	color = colorin;
}

Object::Object(Uint32 colorin) {
	state = INSIDE;
	drawState = true;
	color = colorin;
}

void Object::setPlane(const points points[8]) {
	state = INSIDE;
	plane[0].setPoints(points[0].x, points[0].y, points[0].z, points[1].x, points[1].y, points[1].z, points[2].x, points[2].y, points[2].z, points[3].x, points[3].y, points[3].z);
	plane[1].setPoints(points[2].x, points[2].y, points[2].z, points[3].x, points[3].y, points[3].z, points[7].x, points[7].y, points[7].z, points[6].x, points[6].y, points[6].z);
	plane[2].setPoints(points[4].x, points[4].y, points[4].z, points[5].x, points[5].y, points[5].z, points[6].x, points[6].y, points[6].z, points[7].x, points[7].y, points[7].z);
	plane[3].setPoints(points[0].x, points[0].y, points[0].z, points[1].x, points[1].y, points[1].z, points[5].x, points[5].y, points[5].z, points[4].x, points[4].y, points[4].z);
	plane[4].setPoints(points[0].x, points[0].y, points[0].z, points[3].x, points[3].y, points[3].z, points[7].x, points[7].y, points[7].z, points[4].x, points[4].y, points[4].z);
	plane[5].setPoints(points[1].x, points[1].y, points[1].z, points[2].x, points[2].y, points[2].z, points[6].x, points[6].y, points[6].z, points[5].x, points[5].y, points[5].z);
	x = (points[0].x + points[4].x) / 2;
	y = (points[0].y + points[1].y) / 2;
	z = (points[0].z + points[3].z) / 2;
}

void Object::setcolor(Uint32 colorin) {
	state = INSIDE;
	drawState = true;
	color = colorin;
}

void Object::draw(james ken, RenderWindow rw) {//還沒設priority
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 6; j++) {
			if (plane[i].getPoint() - ken < plane[j].getPoint() - ken) { // dist大者i小
				Obj_plane temp = plane[i];
				plane[i] = plane[j];
				plane[j] = temp;
			}
		}
	}

	for (int i = 0; i < 6; i++) {
		plane[i].back_judge_draw(ken, rw, drawState, color);
		
	}
}

void Object::draw_and_james(james ken, RenderWindow rw, james evan, double dist_from_other, bool other_Crouch) {//include draw james
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 6; j++) {
			if (plane[i].getPoint() - ken < plane[j].getPoint() - ken) { // dist大者i小
				Obj_plane temp = plane[i];
				plane[i] = plane[j];
				plane[j] = temp;
			}
		}
	}

	for (int i = 0; i < 6; i++) {
		int issameside = 0;
		points center; center.x = x; center.y = y; center.z = z;
		
		if (plane[i].getPoint() - ken < center - ken) {
			if (!IsSameSide(ken.getPoint(), evan.getPoint(), plane[i])) {
				
				ken.draw_opponent(evan.getPoint(), evan.getView_direction(), rw, other_Crouch);
			} 
			else {
				
				issameside = 1;
			}
		}

		plane[i].back_judge_draw(ken, rw, drawState, color);
		

		if (issameside == 1) {
			ken.draw_opponent(evan.getPoint(), evan.getView_direction(), rw, other_Crouch);
		}
	}
}

int Object::getState() {
	return state;
}

points Object::getPoint() {
	points p;
	p.x = x; p.y = y; p.z = z; p.state = INSIDE;
	return p;
}

double Object::getHighest() {
	return z + CUBE_RADIUS;
}