#pragma once
#include "points.h"
#include "RenderWindow.h"
#include "constants.h"
#include <SDL2_gfxPrimitives.h>
using namespace std;

struct Body_plane {
	points point[4];
	points draw_point[6];
	points center;
	SDL_FPoint screen_point[5];
	int state;
};

struct Magazine {
	int bullet_num;
	bool can_use;
};

class james {
	points original_point;
	points original_view_vector;
	points point;
	double view_angle;
	double view_updown;
	points view_vector;

	points proj_center;

	//MOVE////////////////////////////////////////////////////////////

	int forward; // isforward  //as same as bool
	int back;  // isback
	int left;  // isleft
	int right;  // isright
	double view_angle_leftright_increment;  // can be negative
	double view_angle_updown_increment;  // can be negative
	points unit_view_vector;

	//JUMP ///////////////////////////////
	double drop_velocity;
	bool CAN_JUMPorNOT;
	SDL_TimerID timerID;
	Uint32 time;
	static Uint32 changeData(Uint32 interval, void* param);

	//CROUCH/////////////////////////////////////////
	int crouch_level;
	bool CROUCHorNOT;


	//draw james (變數都為對手的)//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	points body[8];
	points face[8];
	points hair[8];
	Body_plane body_plane[6];
	Body_plane face_plane[6];
	Body_plane hair_plane[6];
	points body_center;
	points face_center;
	points hair_center;
	Uint32 color;
	int state;

	void sethair_point(points);
	void setbody_point(points, bool);
	void setface_point(points);
	void rotate(points, points, bool);
	void sethair_plane();
	void setbody_plane();
	void setface_plane();
	SDL_FPoint setScreenpoints(points, double, double, double);
	points setProjpoints(points);
	void judge(points[], points pos, points dir, points&);

	//SETTING////////////////////////////////////////////////////////////////////////////////
	int blood;
	Magazine magazine;
	int bullet_remain;
	double reload_time;
	void change_magazine();

	int run_judge_time;
	int slide_time;

	int viewR_time;
	int viewL_time;

	int killnum;
	int dienum;

	//opponent direction/////////////////////////////
	double oppo_angle;
	void cal_oppo_angle(points);
	bool IsZip;
	double velocity;
	double view_speed;
	int max_viewupdown;
	int fullhp;
	double jumpvelocity;
	double current_floor;
	double getdist_from_other(points);


public:
	void set_velocity(double);
	double get_velocity();
	void set_view_speed(double v);
	double get_view_speed();
	void set_max_viewupdown(double v) { max_viewupdown = v; }
	double get_max_viewupdown() {return max_viewupdown; }
	void setfullhp(double v) { fullhp = v; }
	double getfullhp() { return fullhp; }
	void setjumpvelocity(double v) { jumpvelocity = v; }
	double getjumpvelocity() { return jumpvelocity; }
	void set_view_angle_leftright_increment(double);
	void set_view_angle_updown_increment(double);
	void set_forward(int);
	void set_back(int);
	void set_left(int);
	void set_right(int);
	double get_view_angle();
	double get_unitviewx();
	double get_unitviewy();
	double get_unitviewz();
	void collision(points, points, points);
	void boundary(points, points);
	void move(points**, int);  ////////  change  ///////
	//////////////////////////////////////////////////////////////
	james();
	james(double, double, double, double, double);
	void setPoint(double, double, double);
	points getPoint();
	void change_view_angle(double, double);	  //  change   //////////
	double getx();
	double gety();
	double getz();
	double geta();
	double getb();
	double getc();
	double getView_angle();
	double getView_up_down();
	points getView_direction();

	//JUMP////////////////////////////////////////////
	void setJampV();
	void startTimer(Uint32 t);
	void stopTimer();
	bool IsJump() { return !CAN_JUMPorNOT; }


	//CROUCH/////////////////////////////////////////////////
	bool IsCrouch() { return CROUCHorNOT; }

	//draw james //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void draw_body(RenderWindow, int);
	void draw_face(RenderWindow, int);
	void draw_hair(RenderWindow, int);
	void judge_draw_body(points pos, points dir, RenderWindow, int);
	void judge_draw_face(points pos, points dir, RenderWindow, int);
	void judge_draw_hair(points pos, points dir, RenderWindow, int);
	void draw_opponent(points pos, points dir, RenderWindow, bool);
	int getState();
	friend double operator-(points, james&);
	void set_oppo_Color(Uint32);


	//SETTING///////////////////////////////////////////////////
	void setBlood(int);
	void operator-=(int);
	int getBlood();
	void start_change_magazine();
	void lost_one_bullet();
	bool getCanShoot();
	bool Isreloading();
	bool punch(points);
	void reset_run_time();
	int get_run_time();
	void reset_viewR_time();
	int get_viewR_time();
	void reset_viewL_time();
	int get_viewL_time();
	void slide();
	double getrt();
	void reset() {
		blood = fullhp;
		magazine.bullet_num = MAGAZINE_BULLET_NUM;
		magazine.can_use = true;
		bullet_remain = BULLET_TOTAL;
		reload_time = 0;

		point.x = original_point.x;
		point.y = original_point.y;
		point.z = original_point.z;
		view_vector.x = original_view_vector.x;
		view_vector.y = original_view_vector.y;
		view_vector.z = original_view_vector.z;
	}

	void operator++(int){ killnum ++; }
	void set_killnum(int k) { killnum = k; };
	int get_killnum() { return killnum; };
	void operator--(int) { dienum ++; }
	void set_dienum(int k) { dienum = k; };
	int get_dienum() { return dienum; };


	//GETTING/////////////////////////
	int getmagazine() { return magazine.bullet_num; }
	int getbullet_remain() { return bullet_remain; }
	void crouch();
	void stand();
	double getOppoAngle(points);
	void Zip(points);
	void NotZip();
	bool IsZIP();
};

