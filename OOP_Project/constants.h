#pragma once
#include <SDL2_gfxPrimitives.h>

const int DISTANCE_PROJPLANE_FROM_JAMES = 100;

const int CUBE_RADIUS = 125;

const int WIDTH = 1200;
const int HEIGHT = 600;

const double RUN_SPEED = 6;
const double TURN_SPEED = 0.5;
const double UPDOWN_SPEED = 1;
const double BULLET_SPEED = 1;
const Uint32 BULLET_FLYTIME = 300;
const int BULLET_DAMAGE = 20;
const int BULLET_DEVIATION = 5;//+-5

const double ZIP_SPEED = 0.5;
const Uint32 ZIP_FLYTIME = 500;
const double ZIP_LENGTH = 10000;
const double JAMES_ZIPSPEED = 5;

const int PUNCH_DAMAGE = 10;
const int PUNCH_DEVIATION = 3;//+-3

const double VISIONANGLE_W = 60 * (M_PI / 180);
const double VISIONANGLE_H = 40 * (M_PI / 180);



const int INSIDE = 4;
const int OUTSIDE = 0;
const int THROUGH = 2;
const int ONEOUT = 3;
const int ONEIN = 1;
const int BACK = -1;
const int FRONT = -2;


#define ALLREGION -1
#define NO_TRANSPARENT_BG {0, 0, 0, 0}

#define SOLID 100
#define SHADED 101
#define BLENDED 102

const int JAMES_WIDTH = 60;
const int JAMES_HEIGHT = JAMES_WIDTH * 5;

const double GRAVITY = -980 * 6;
const double JUMPVELOCITY = 2000;

const int CROUCH_LEVEL = 100;

const int BLOOD = 100;
const int BULLET_TOTAL = 100;
const int MAGAZINE_BULLET_NUM = 20;

const int PUNCH_AREA = 7;

const double RELOAD_TIME = 3000;
const int CANNOT_CHANGE_MAGAZINE = -123;

const int DOUBLE_TAB_JUDGE_TIME = 500;
const int SLIDE_TIME = 500;
const double SLIDE_ACCELERATION = 0.5;

const int MAX_VIEWUPDOWN = 0;

//mixer
#define MUSIC 10
#define EFFECT 11
#define FOREVER -1
#define ONE 0
#define ALLCHANNEL -1