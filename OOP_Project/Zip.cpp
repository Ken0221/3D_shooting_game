#include "Zip.h"
#include "james.h"
#include "RenderWindow.h"
#include "constants.h"
#include <iostream>
using namespace std;

Zip::Zip() : Bullet() {
	fullziptimes = 5;// MAX_ZIPTIME;
	times = fullziptimes;

	speed = BULLET_SPEED;
	flytime = ZIP_FLYTIME;
	IsZip = 1;

}

Zip::Zip(james j, Uint32 c): Bullet(j, c) {
	fullziptimes = 5;// MAX_ZIPTIME;
	times = fullziptimes;
	
	speed = BULLET_SPEED;
	flytime = ZIP_FLYTIME;
	IsZip = 1;
	reset(j);
}

void Zip::reset(james j) {
	times--;
	point[0].x = j.getx() + j.geta() * 0.01 + j.getb() * 0.01;
	point[0].y = j.gety() + j.getb() * 0.01 - j.geta() * 0.01;
	point[0].z = j.getz() - 100;
	point[1].x = point[0].x;
	point[1].y = point[0].y;
	point[1].z = point[0].z;
	dir.x = j.getx() + j.geta() * 100 - point[0].x;
	dir.y = j.gety() + j.getb() * 100 - point[0].y;
	dir.z = (j.getz() - 50) + j.getc() * 100 - point[0].z;

	flytime = ZIP_FLYTIME;
}

bool Zip::IsHitWall(Object wall[], int n) {
	for (int i = 0; i < n; i++) {
		
		if (point[1].x <= wall[i].getPoint().x + CUBE_RADIUS && point[1].x >= wall[i].getPoint().x - CUBE_RADIUS &&
			point[1].y <= wall[i].getPoint().y + CUBE_RADIUS && point[1].y >= wall[i].getPoint().y - CUBE_RADIUS &&
			point[1].z <= wall[i].getPoint().z + CUBE_RADIUS && point[1].z >= wall[i].getPoint().z - CUBE_RADIUS) {
			
			Ishitwall = true;
			return true;
		}
	}
	Ishitwall = false;
	return false;
}

double Zip::getZipLength() {
	return sqrt((point[1].x - point[0].x) * (point[1].x - point[0].x) +
		(point[1].y - point[0].y) * (point[1].y - point[0].y) +
		(point[1].z - point[0].z) * (point[1].z - point[0].z));
}

points Zip::getpoint1() {
	return point[1];
}

int Zip::ZipCount() {
	return times;
}

void Zip::Lost_one_zip() {
	times--;
}