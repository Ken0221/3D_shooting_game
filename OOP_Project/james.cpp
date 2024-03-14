#include "james.h"
#include "constants.h"
#include <math.h>
#include <iostream>
using namespace std;

james::james() {
	point.x = 0;
	point.y = 0;
	point.z = 0;
	original_point.x = 0;
	original_point.y = 0;
	original_point.z = 0;

	view_angle = 0;
	view_updown = 0;

	view_vector.x = 100;
	view_vector.y = 0;
	view_vector.z = 0;
	original_view_vector.x = view_vector.x;
	original_view_vector.y = view_vector.y;
	original_view_vector.z = view_vector.z;

	proj_center.x = point.x + view_vector.x;
	proj_center.y = point.y + view_vector.y;
	proj_center.z = point.z + view_vector.z;

	unit_view_vector.x = view_vector.x / DISTANCE_PROJPLANE_FROM_JAMES;
	unit_view_vector.y = view_vector.y / DISTANCE_PROJPLANE_FROM_JAMES;
	unit_view_vector.z = view_vector.z / DISTANCE_PROJPLANE_FROM_JAMES;

	velocity = RUN_SPEED;
	view_speed = TURN_SPEED;
	max_viewupdown = MAX_VIEWUPDOWN;
	fullhp = BLOOD;
	jumpvelocity = JUMPVELOCITY;

	drop_velocity = 0;
	CAN_JUMPorNOT = true;

	forward = 0; // isforward  //as same as bool
	back = 0;  // isback
	left = 0;  // isleft
	right = 0;  // isright
	view_angle_leftright_increment = 0;  // can be negative
	view_angle_updown_increment = 0;  // can be negative

	state = INSIDE;
	for (int i = 0; i < 8; i++) {
		face[i].state = INSIDE;
		hair[i].state = INSIDE;
		body[i].state = INSIDE;
	}
	color = 0xFFFF9632;
	blood = BLOOD;
	magazine.bullet_num = MAGAZINE_BULLET_NUM;
	magazine.can_use = true;
	bullet_remain = BULLET_TOTAL;
	reload_time = 0;

	crouch_level = 0;
	CROUCHorNOT = false;

	run_judge_time = 0;
	slide_time = 0;

	viewL_time = 0;
	viewR_time = 0;

	killnum = 0;
	dienum = 0;

	oppo_angle = 0;
	IsZip = false;

	current_floor = 0;
}

james::james(double x, double y, double z, double theta, double f) {
	point.x = x;
	point.y = y;
	point.z = z;
	original_point.x = x;
	original_point.y = y;
	original_point.z = z;

	view_angle = theta;
	view_updown = f;

	view_vector.x = DISTANCE_PROJPLANE_FROM_JAMES * cos(view_angle * M_PI / 180.0) * cos(view_updown * M_PI / 180.0);
	view_vector.y = DISTANCE_PROJPLANE_FROM_JAMES * sin(view_angle * M_PI / 180.0) * cos(view_updown * M_PI / 180.0);
	view_vector.z = DISTANCE_PROJPLANE_FROM_JAMES * sin(view_updown * M_PI / 180.0);
	original_view_vector.x = view_vector.x;
	original_view_vector.y = view_vector.y;
	original_view_vector.z = view_vector.z;

	proj_center.x = point.x + view_vector.x;
	proj_center.y = point.y + view_vector.y;
	proj_center.z = point.z + view_vector.z;

	unit_view_vector.x = view_vector.x / DISTANCE_PROJPLANE_FROM_JAMES;
	unit_view_vector.y = view_vector.y / DISTANCE_PROJPLANE_FROM_JAMES;
	unit_view_vector.z = view_vector.z / DISTANCE_PROJPLANE_FROM_JAMES;

	velocity = RUN_SPEED;
	view_speed = TURN_SPEED;
	max_viewupdown = MAX_VIEWUPDOWN;
	fullhp = BLOOD;
	jumpvelocity = JUMPVELOCITY;

	drop_velocity = 0;
	CAN_JUMPorNOT = true;

	forward = 0; // isforward  //as same as bool
	back = 0;  // isback
	left = 0;  // isleft
	right = 0;  // isright
	view_angle_leftright_increment = 0;  // can be negative
	view_angle_updown_increment = 0;  // can be negative

	state = INSIDE;
	for (int i = 0; i < 8; i++) {
		face[i].state = INSIDE;
		hair[i].state = INSIDE;
		body[i].state = INSIDE;
	}
	color = 0xFFFF9632;

	blood = BLOOD;
	magazine.bullet_num = MAGAZINE_BULLET_NUM;
	magazine.can_use = true;
	bullet_remain = BULLET_TOTAL;
	reload_time = 0;

	crouch_level = 0;
	CROUCHorNOT = false;

	run_judge_time = 0;
	slide_time = 0;

	viewL_time = 0;
	viewR_time = 0;

	killnum = 0;
	dienum = 0;

	oppo_angle = 0;
	IsZip = false;

	current_floor = 0;
}

void james::setPoint(double x, double y, double z) { 
	point.x = x;
	point.y = y;
	point.z = z;
}

points james::getPoint() {
	return point;
}

void james::change_view_angle(double thetaX, double thetaY) {
	view_angle += thetaX;// theta;
	view_angle += view_angle_leftright_increment;
	if (view_angle >= 360)
		view_angle -= 360;

	view_updown += thetaY;
	view_updown += view_angle_updown_increment;
	if (view_updown >= max_viewupdown)
		view_updown = max_viewupdown;
	else if(view_updown <= -max_viewupdown)
		view_updown = -max_viewupdown;

	view_vector.x = DISTANCE_PROJPLANE_FROM_JAMES * cos(view_angle * M_PI / 180.0) * cos(view_updown * M_PI / 180.0);
	view_vector.y = DISTANCE_PROJPLANE_FROM_JAMES * sin(view_angle * M_PI / 180.0) * cos(view_updown * M_PI / 180.0);
	view_vector.z = DISTANCE_PROJPLANE_FROM_JAMES * sin(view_updown * M_PI / 180.0);

	unit_view_vector.x = view_vector.x / DISTANCE_PROJPLANE_FROM_JAMES;
	unit_view_vector.y = view_vector.y / DISTANCE_PROJPLANE_FROM_JAMES;
	unit_view_vector.z = view_vector.z / DISTANCE_PROJPLANE_FROM_JAMES;
}

double james::getx() {
	return point.x;
}

double james::gety() {
	return point.y;
}

double james::getz() {
	return point.z;
}

double james::geta() {
	return view_vector.x;
}

double james::getb() {
	return view_vector.y;
}

double james::getc() {
	return view_vector.z;
}

double james::getView_angle() {
	return view_angle;
}

double james::getView_up_down() {
	return view_updown;
}

points james::getView_direction() {
	return view_vector;
}

void james::set_velocity(double v) {
	velocity = v;
}

double james::get_velocity() {
	return velocity;
}

void james::set_view_angle_leftright_increment(double a) {
	view_angle_leftright_increment = a;
}

void james::set_view_angle_updown_increment(double a) {
	view_angle_updown_increment = a;
}

void james::set_forward(int f) {
	forward = f;
}
void james::set_back(int b) {
	back = b;
}
void james::set_left(int l) {
	left = l;
}
void james::set_right(int r) {
	right = r;
}

double james::get_unitviewx() {
	return unit_view_vector.x;
}

double james::get_unitviewy() {
	return unit_view_vector.y;
}

double james::get_unitviewz() {
	return unit_view_vector.z;
}

void james::move(points **all_p, int num_of_cube) {

	//forward
	point.x += unit_view_vector.x * velocity * forward;
	point.y += unit_view_vector.y * velocity * forward;

	//back
	point.x -= unit_view_vector.x * velocity * back;
	point.y -= unit_view_vector.y * velocity * back;

	//left
	point.x += -1 * unit_view_vector.y * velocity * left;
	point.y += unit_view_vector.x * velocity * left;

	//right
	point.x += unit_view_vector.y * velocity * right;
	point.y += -1 * unit_view_vector.x * velocity * right;


	current_floor = 0; 
	for (int i = 1; i < num_of_cube + 1; i++) {
		if (point.x > all_p[i][3].x - JAMES_WIDTH && point.y > all_p[i][3].y - JAMES_WIDTH && point.x < all_p[i][6].x + JAMES_WIDTH && point.y < all_p[i][6].y + JAMES_WIDTH)
			collision(all_p[i][3], all_p[i][6], all_p[i][0]);
	}

	if ((point.x > all_p[0][6].x - JAMES_WIDTH || point.x < all_p[0][3].x + JAMES_WIDTH) || (point.y > all_p[0][6].y - JAMES_WIDTH || point.y < all_p[0][3].y + JAMES_WIDTH))
		boundary(all_p[0][3], all_p[0][6]);

	return;
}

double james::get_view_angle() {
	return view_angle;
}

void james::boundary(points min, points max) {

	int d = JAMES_WIDTH;

	//deal x
	if (point.x > max.x - d) {
		point.x = max.x - d;
	}
	else if (point.x < min.x + d) {
		point.x = min.x + d;
	}
	//deal y
	if (point.y > max.y - d) {
		point.y = max.y - d;
	}
	else if (point.y < min.y + d) {
		point.y = min.y + d;
	}

}

void james::collision(points min, points max, points gz) {
	points center = { (max.x + min.x) / 2 , (max.y + min.y) / 2 ,0 };

	double maxz = gz.z;
	double minz = min.z;

	if (point.z - JAMES_HEIGHT +crouch_level>= maxz && point.z >= maxz) {
		if(maxz > current_floor)
			current_floor = maxz;
		
		return;
	}
	else if (point.z - JAMES_HEIGHT+crouch_level < minz && point.z < minz) {
		
		return;
	}

	double dx = 0;
	double dy = 0;
	double cx = point.x;
	double cy = point.y;
	int d = JAMES_WIDTH;

	if (point.x < center.x) {
		dx = point.x - (min.x - d);
		cx = min.x - d;
	}
	else {
		dx = max.x + d - point.x;
		cx = max.x + d;
	}

	if (point.y < center.y) {
		dy = point.y - (min.y - d);
		cy = min.y - d;
	}
	else {
		dy = max.y + d - point.y;
		cy = max.y + d;
	}

	if (dx < dy)
		point.x = cx;
	else if (dy < dx)
		point.y = cy;

	return;
}

void james::setJampV() {
	if (CAN_JUMPorNOT) {
		drop_velocity = jumpvelocity;
		CAN_JUMPorNOT = false;
	}
}


Uint32 james::changeData(Uint32 interval, void* param) { // Timer callback 
	james* p = (james*)param;
	double interval_second = interval / 1000.0;
	if (!p->IsZIP()) {
		p->point.z += p->drop_velocity * interval_second + (GRAVITY * interval_second * interval_second) / 2;
		p->drop_velocity += GRAVITY * interval_second;
	}

	if (p->point.z <= p->current_floor + JAMES_HEIGHT - p->crouch_level) {
		p->point.z = p->current_floor + JAMES_HEIGHT - p->crouch_level;
		p->drop_velocity = 0;
		p->CAN_JUMPorNOT = true;
	}
	//reload
	if (p->reload_time > 0) {
		p->reload_time -= interval;
		
	}
	else if (p->reload_time <= 0 && p->reload_time != CANNOT_CHANGE_MAGAZINE) {
		p->reload_time = CANNOT_CHANGE_MAGAZINE;
		p->change_magazine();
	}
	//run timer
	if (p->run_judge_time > 0) {
		p->run_judge_time -= interval;
	}
	//slide timer
	if (p->slide_time > 0) {
		p->slide_time -= interval;
		p->velocity -= SLIDE_ACCELERATION;
		if (p->velocity < RUN_SPEED)
			p->velocity = RUN_SPEED;
	}
	//view timer
	if (p->viewR_time > 0) {
		p->viewR_time -= interval;
	}
	if (p->viewL_time > 0) {
		p->viewL_time -= interval;
	}
	return interval;
}

void james::startTimer(Uint32 t) {
	time = t;
	timerID = SDL_AddTimer(time, changeData, this); // Set Timer callback
}

void james::stopTimer() {
	time = 0;
	SDL_RemoveTimer(timerID);
}

//人物座標 face hair body
SDL_FPoint james::setScreenpoints(points p, double d, double e, double f) {
	

	double t = (p.z - (point.z + view_vector.z)) / f; // since f == tt

	points temp;
	temp.x = p.x - t * d;
	temp.y = p.y - t * e;
	temp.z = p.z - t * f;

	SDL_FPoint scr_point;
	double cosson = view_vector.x * (temp.x - point.x) + view_vector.y * (temp.y - point.y) + view_vector.z * (temp.z - point.z);
	double cosmom = DISTANCE_PROJPLANE_FROM_JAMES * sqrt(((temp.x - point.x) * (temp.x - point.x) + (temp.y - point.y) * (temp.y - point.y) + (temp.z - point.z) * (temp.z - point.z)));
	double fr = cosson / cosmom;
	if (fr >= 1)
		fr = 1;
	else if (fr <= -1)
		fr = -1;
	double theta = acos(fr);
	double dx = (WIDTH / 2.0) * (theta / VISIONANGLE_W);
	double cross_for_x = view_vector.x * (p.y - point.y) - view_vector.y * (p.x - point.x);

	if (cross_for_x < 0)
		scr_point.x = (WIDTH / 2.0) + dx;
	else
		scr_point.x = (WIDTH / 2.0) - dx;

	

	points cross_with_temp;
	cross_with_temp.x = (p.y - point.y) * view_vector.z - (p.z - point.z) * (temp.y - point.y);
	cross_with_temp.y = (p.z - point.z) * (temp.x - point.x) - (p.x - point.x) * view_vector.z;
	cross_with_temp.z = (p.x - point.x) * (temp.y - point.y) - (p.y - point.y) * (temp.x - point.x);
	cosson = sqrt((temp.x - point.x) * (temp.x - point.x) + (temp.y - point.y) * (temp.y - point.y) + (temp.z - point.z) * (temp.z - point.z));
	cosmom = sqrt((p.x - point.x) * (p.x - point.x) + (p.y - point.y) * (p.y - point.y) + (p.z - point.z) * (p.z - point.z));
	fr = cosson / cosmom;
	if (fr >= 1)
		fr = 1;
	else if (fr <= -1)
		fr = -1;
	double phi = acos(fr);
	double dy = (HEIGHT / 2.0) * (phi / VISIONANGLE_H);
	double cross_for_y = view_vector.x * cross_with_temp.y - view_vector.y * cross_with_temp.x;

	if (cross_for_y > 0)
		scr_point.y = (HEIGHT / 2.0) - dy;
	else
		scr_point.y = (HEIGHT / 2.0) + dy;

	

	scr_point.x -= WIDTH / 4;

	return scr_point;
}

points james::setProjpoints(points p) {
	points proj_point;
	double tson = DISTANCE_PROJPLANE_FROM_JAMES;
	double tmom = sqrt((p.x - point.x) * (p.x - point.x) + (p.y - point.y) * (p.y - point.y) + (p.z - point.z) * (p.z - point.z));
	double t = tson / tmom;
	proj_point.x = point.x + t * (p.x - point.x);
	proj_point.y = point.y + t * (p.y - point.y);
	proj_point.z = point.z + t * (p.z - point.z);

	

	return proj_point;
}

void james::draw_opponent(points pos, points dir, RenderWindow rw, bool other_Crouch) {
	rotate(pos, dir, other_Crouch);

	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 6; j++) {
			if (getdist_from_other(body_plane[i].center) < getdist_from_other(body_plane[j].center)) { // dist大者i小
				Body_plane temp = body_plane[i];
				body_plane[i] = body_plane[j];
				body_plane[j] = temp;
			}
			if (getdist_from_other(face_plane[i].center) < getdist_from_other(face_plane[j].center)) { // dist大者i小
				Body_plane temp = face_plane[i];
				face_plane[i] = face_plane[j];
				face_plane[j] = temp;
			}
			if (getdist_from_other(hair_plane[i].center) < getdist_from_other(hair_plane[j].center)) { // dist大者i小
				Body_plane temp = hair_plane[i];
				hair_plane[i] = hair_plane[j];
				hair_plane[j] = temp;
			}
		}
	}
	
	points head;
	head.x = (face_center.x + hair_center.x) / 2.0;
	head.y = (face_center.y + hair_center.y) / 2.0;
	head.z = (face_center.z + hair_center.z) / 2.0;
	double dist_b = getdist_from_other(body_center);
	double dist_head = getdist_from_other(head);
	int b = 1;
	if (dist_b > dist_head) {
		for (int i = 0; i < 6; i++)
			judge_draw_body(pos, dir, rw, i);
	}

	if (dir.x * (point.x - pos.x) + dir.y * (point.y - pos.y) + dir.z * (point.z - pos.z) < 0) {//判斷是否在背面
		for (int i = 0; i < 6; i++)
			judge_draw_face(pos, dir, rw, i);
		for (int i = 0; i < 6; i++)
			judge_draw_hair(pos, dir, rw, i);
	}
	else {
		for (int i = 0; i < 6; i++)
			judge_draw_hair(pos, dir, rw, i);
		for (int i = 0; i < 6; i++)
			judge_draw_face(pos, dir, rw, i);
	}

	if (dist_b < dist_head) {
		for (int i = 0; i < 6; i++)
			judge_draw_body(pos, dir, rw, i);
	}
}

void james::draw_body(RenderWindow rw, int n) {
	//cout << "draw" << endl;
	double tt = sqrt(view_vector.x * view_vector.x + view_vector.y * view_vector.y);
	double d = -(view_vector.z / tt) * view_vector.x;
	double e = -(view_vector.z / tt) * view_vector.y;
	double f = tt;
	
	Sint16 xt[4], yt[4];
	for (int i = 0; i < 4; i++) {
		
		points pj_point[4];
		pj_point[i] = setProjpoints(body_plane[n].draw_point[i]);//point->draw_point
		body_plane[n].screen_point[i] = setScreenpoints(pj_point[i], d, e, f);
		xt[i] = body_plane[n].screen_point[i].x;
		yt[i] = body_plane[n].screen_point[i].y;
	}

	filledPolygonRGBA(rw.getRenderer(), xt, yt, 4, (color / 0x10000) % 0x100, (color / 0x100) % 0x100, color % 0x100, color / 0x1000000);
	

	for (int i = 0; i < 4; i++) {
		int k = (i != 3) ? i + 1 : 0;
		if (!(body_plane[n].point[i].state == BACK && body_plane[n].point[k].state == BACK)) {
			SDL_SetRenderDrawColor(rw.getRenderer(), 0, 0, 0, 255);
			SDL_RenderDrawLineF(rw.getRenderer(), body_plane[n].screen_point[i].x, body_plane[n].screen_point[i].y, body_plane[n].screen_point[k].x, body_plane[n].screen_point[k].y);
		}
	}
}

void james::draw_face(RenderWindow rw, int n) {
	double tt = sqrt(view_vector.x * view_vector.x + view_vector.y * view_vector.y);
	double d = -(view_vector.z / tt) * view_vector.x;
	double e = -(view_vector.z / tt) * view_vector.y;
	double f = tt;
	
	Sint16 xt[4], yt[4];
	for (int i = 0; i < 4; i++) {
		
		points pj_point[4];
		pj_point[i] = setProjpoints(face_plane[n].draw_point[i]);//point->draw_point
		face_plane[n].screen_point[i] = setScreenpoints(pj_point[i], d, e, f);
		xt[i] = face_plane[n].screen_point[i].x;
		yt[i] = face_plane[n].screen_point[i].y;
	}


	filledPolygonRGBA(rw.getRenderer(), xt, yt, 4, 240, 200, 150, 255);
	

	for (int i = 0; i < 4; i++) {
		int k = (i != 3) ? i + 1 : 0;
		if (!(face_plane[n].point[i].state == BACK && face_plane[n].point[k].state == BACK)) {
			SDL_SetRenderDrawColor(rw.getRenderer(), 0, 0, 0, 255);
			SDL_RenderDrawLineF(rw.getRenderer(), face_plane[n].screen_point[i].x, face_plane[n].screen_point[i].y, face_plane[n].screen_point[k].x, face_plane[n].screen_point[k].y);
		}
	}
}

void james::draw_hair(RenderWindow rw, int n) {
	double tt = sqrt(view_vector.x * view_vector.x + view_vector.y * view_vector.y);
	double d = -(view_vector.z / tt) * view_vector.x;
	double e = -(view_vector.z / tt) * view_vector.y;
	double f = tt;
	
	Sint16 xt[4], yt[4];
	for (int i = 0; i < 4; i++) {
		
		points pj_point[4];
		pj_point[i] = setProjpoints(hair_plane[n].draw_point[i]);//point->draw_point
		hair_plane[n].screen_point[i] = setScreenpoints(pj_point[i],d, e, f);
		xt[i] = hair_plane[n].screen_point[i].x;
		yt[i] = hair_plane[n].screen_point[i].y;
	}


	filledPolygonRGBA(rw.getRenderer(), xt, yt, 4, 0, 0, 0, 255);
	

	for (int i = 0; i < 4; i++) {
		int k = (i != 3) ? i + 1 : 0;
		if (!(hair_plane[n].point[i].state == BACK && hair_plane[n].point[k].state == BACK)) {
			SDL_SetRenderDrawColor(rw.getRenderer(), 0, 0, 0, 255);
			SDL_RenderDrawLineF(rw.getRenderer(), hair_plane[n].screen_point[i].x, hair_plane[n].screen_point[i].y, hair_plane[n].screen_point[k].x, hair_plane[n].screen_point[k].y);
		}
	}
}

void james::judge_draw_body(points pos, points dir, RenderWindow rw, int n) {
	state = OUTSIDE;//reset state
	for (int i = 0; i < 4; i++) {
		body_plane[n].draw_point[i] = body_plane[n].point[i];

		if (view_vector.x * (body_plane[n].point[i].x - point.x) + view_vector.y * (body_plane[n].point[i].y - point.y) + view_vector.z * (body_plane[n].point[i].z - point.z) <= 0) {//判斷是否在背面
			body_plane[n].point[i].state = BACK;
		}
		else {
			body_plane[n].point[i].state = FRONT;
			state++;
		}
		
	}

	
	if (state == INSIDE) {
		
		draw_body(rw, n);
	}
}

void james::judge_draw_face(points pos, points dir, RenderWindow rw, int n) {
	state = OUTSIDE;//reset state
	for (int i = 0; i < 4; i++) {
		face_plane[n].draw_point[i] = face_plane[n].point[i];

		if (view_vector.x * (face_plane[n].point[i].x - point.x) + view_vector.y * (face_plane[n].point[i].y - point.y) + view_vector.z * (face_plane[n].point[i].z - point.z) <= 0) {//判斷是否在背面
			face_plane[n].point[i].state = BACK;
		}
		else {
			face_plane[n].point[i].state = FRONT;
			state++;
		}
		
	}

	
	if (state == INSIDE) {
		
		draw_face(rw, n);
	}
}

void james::judge_draw_hair(points pos, points dir, RenderWindow rw, int n) {
	state = OUTSIDE;//reset state
	for (int i = 0; i < 4; i++) {
		hair_plane[n].draw_point[i] = hair_plane[n].point[i];

		if (view_vector.x * (hair_plane[n].point[i].x - point.x) + view_vector.y * (hair_plane[n].point[i].y - point.y) + view_vector.z * (hair_plane[n].point[i].z - point.z) <= 0) {//判斷是否在背面
			hair_plane[n].point[i].state = BACK;
		}
		else {
			hair_plane[n].point[i].state = FRONT;
			state++;
		}
		
	}

	
	if (state == INSIDE) {
		
		draw_hair(rw, n);
	}
}

int james::getState() {
	return state;
}

void james::set_oppo_Color(Uint32 c) {
	color = c;
}

double james::getdist_from_other(points plane_pos) {
	return sqrt((point.x - plane_pos.x) * (point.x - plane_pos.x) + (point.y - plane_pos.y) * (point.y - plane_pos.y) + (point.z - plane_pos.z) * (point.z - plane_pos.z));
}

double operator-(points pos, james& j) {
	return sqrt((j.point.x - pos.x) * (j.point.x - pos.x) + (j.point.y - pos.y) * (j.point.y - pos.y) + (j.point.z - pos.z) * (j.point.z - pos.z));
}

void james::rotate(points other_pos, points other_dir, bool other_Crouch)
{

	setface_point(other_pos);
	sethair_point(other_pos);
	setbody_point(other_pos, other_Crouch);
	
	for (int i = 0; i < 8; i++)
	{
		double x, y;
		x = body_center.x + (body[i].x - body_center.x) * cos(atan2(other_dir.y, other_dir.x)) - (body[i].y - body_center.y) * sin(atan2(other_dir.y, other_dir.x));
		y = body_center.y + (body[i].x - body_center.x) * sin(atan2(other_dir.y, other_dir.x)) + (body[i].y - body_center.y) * cos(atan2(other_dir.y, other_dir.x));

		body[i].x = x;
		body[i].y = y;

		
	}

	hair[0].x = body[0].x;
	hair[0].y = body[0].y;
	hair[1].x = (body[0].x + body[1].x) / 2;
	hair[1].y = (body[0].y + body[1].y) / 2;
	hair[2].x = (body[2].x + body[3].x) / 2;
	hair[2].y = (body[2].y + body[3].y) / 2;
	hair[3].x = body[3].x;
	hair[3].y = body[3].y;
	hair[4].x = body[4].x;
	hair[4].y = body[4].y;
	hair[5].x = (body[4].x + body[5].x) / 2;
	hair[5].y = (body[4].y + body[5].y) / 2;
	hair[6].x = (body[6].x + body[7].x) / 2;
	hair[6].y = (body[6].y + body[7].y) / 2;
	hair[7].x = body[7].x;
	hair[7].y = body[7].y;

	face[1].x = body[1].x;
	face[1].y = body[1].y;
	face[0].x = (body[0].x + body[1].x) / 2;
	face[0].y = (body[0].y + body[1].y) / 2;
	face[3].x = (body[2].x + body[3].x) / 2;
	face[3].y = (body[2].y + body[3].y) / 2;
	face[2].x = body[2].x;
	face[2].y = body[2].y;
	face[5].x = body[5].x;
	face[5].y = body[5].y;
	face[4].x = (body[4].x + body[5].x) / 2;
	face[4].y = (body[4].y + body[5].y) / 2;
	face[7].x = (body[6].x + body[7].x) / 2;
	face[7].y = (body[6].y + body[7].y) / 2;
	face[6].x = body[6].x;
	face[6].y = body[6].y;

	
	setbody_plane();
	setface_plane();
	sethair_plane();
}

void james::sethair_point(points other)
{
	hair[0].x = other.x - JAMES_WIDTH / 2;
	hair[0].y = other.y - JAMES_WIDTH / 2;
	hair[0].z = other.z;

	hair[1].x = other.x;
	hair[1].y = other.y - JAMES_WIDTH / 2;
	hair[1].z = other.z;

	hair[3].x = other.x - JAMES_WIDTH / 2;
	hair[3].y = other.y - JAMES_WIDTH / 2;
	hair[3].z = other.z - JAMES_HEIGHT / 3;

	hair[2].x = other.x;
	hair[2].y = other.y - JAMES_WIDTH / 2;
	hair[2].z = other.z - JAMES_HEIGHT / 3;

	hair[4].x = other.x - JAMES_WIDTH / 2;
	hair[4].y = other.y + JAMES_WIDTH / 2;
	hair[4].z = other.z;

	hair[5].x = other.x;	
	hair[5].y = other.y + JAMES_WIDTH / 2;
	hair[5].z = other.z;

	hair[7].x = other.x - JAMES_WIDTH / 2;
	hair[7].y = other.y + JAMES_WIDTH / 2;
	hair[7].z = other.z - JAMES_HEIGHT / 3;

	hair[6].x = other.x;
	hair[6].y = other.y + JAMES_WIDTH / 2;
	hair[6].z = other.z - JAMES_HEIGHT / 3;

	hair_center.x = 0; hair_center.y = 0; hair_center.z = 0;
	for (int i = 0; i < 8; i++) {
		hair_center.x += hair[i].x;
		hair_center.y += hair[i].y;
		hair_center.z += hair[i].z;
	}
	hair_center.x /= 8.0; hair_center.y /= 8.0; hair_center.z /= 8.0;
}

void james::setface_point(points other)
{
	face[0].x = other.x;
	face[0].y = other.y - JAMES_WIDTH / 2;
	face[0].z = other.z;

	face[1].x = other.x + JAMES_WIDTH / 2;
	face[1].y = other.y - JAMES_WIDTH / 2;
	face[1].z = other.z;

	face[3].x = other.x;
	face[3].y = other.y - JAMES_WIDTH / 2;
	face[3].z = other.z - JAMES_HEIGHT / 3;

	face[2].x = other.x + JAMES_WIDTH / 2;
	face[2].y = other.y - JAMES_WIDTH / 2;
	face[2].z = other.z - JAMES_HEIGHT / 3;

	face[4].x = other.x;
	face[4].y = other.y + JAMES_WIDTH / 2;
	face[4].z = other.z;

	face[5].x = other.x + JAMES_WIDTH / 2;
	face[5].y = other.y + JAMES_WIDTH / 2;
	face[5].z = other.z;

	face[7].x = other.x;
	face[7].y = other.y + JAMES_WIDTH / 2;
	face[7].z = other.z - JAMES_HEIGHT / 3;

	face[6].x = other.x + JAMES_WIDTH / 2;
	face[6].y = other.y + JAMES_WIDTH / 2;
	face[6].z = other.z - JAMES_HEIGHT / 3;

	face_center.x = 0; face_center.y = 0; face_center.z = 0;
	for (int i = 0; i < 8; i++) {
		face_center.x += face[i].x;
		face_center.y += face[i].y;
		face_center.z += face[i].z;
	}
	face_center.x /= 8.0; face_center.y /= 8.0; face_center.z /= 8.0;
}

void james::setbody_point(points other, bool other_Crouch)
{
	body[0].x = other.x - JAMES_WIDTH / 2;
	body[0].y = other.y - JAMES_WIDTH / 2;
	body[0].z = other.z - JAMES_HEIGHT / 3;

	body[1].x = other.x + JAMES_WIDTH / 2;
	body[1].y = other.y - JAMES_WIDTH / 2;
	body[1].z = other.z - JAMES_HEIGHT / 3;

	body[3].x = other.x - JAMES_WIDTH / 2;
	body[3].y = other.y - JAMES_WIDTH / 2;
	body[3].z = other.z - JAMES_HEIGHT;
	body[3].z += (other_Crouch) ? CROUCH_LEVEL : 0;

	body[2].x = other.x + JAMES_WIDTH / 2;
	body[2].y = other.y - JAMES_WIDTH / 2;
	body[2].z = other.z - JAMES_HEIGHT;
	body[2].z += (other_Crouch) ? CROUCH_LEVEL : 0;

	body[4].x = other.x - JAMES_WIDTH / 2;
	body[4].y = other.y + JAMES_WIDTH / 2;
	body[4].z = other.z - JAMES_HEIGHT / 3;

	body[5].x = other.x + JAMES_WIDTH / 2;
	body[5].y = other.y + JAMES_WIDTH / 2;
	body[5].z = other.z - JAMES_HEIGHT / 3;

	body[7].x = other.x - JAMES_WIDTH / 2;
	body[7].y = other.y + JAMES_WIDTH / 2;
	body[7].z = other.z - JAMES_HEIGHT; 
	body[7].z += (other_Crouch) ? CROUCH_LEVEL : 0;

	body[6].x = other.x + JAMES_WIDTH / 2;
	body[6].y = other.y + JAMES_WIDTH / 2;
	body[6].z = other.z - JAMES_HEIGHT;
	body[6].z += (other_Crouch) ? CROUCH_LEVEL : 0;

	body_center.x = 0; body_center.y = 0; body_center.z = 0;
	for (int i = 0; i < 8; i++) {
		body_center.x += body[i].x;
		body_center.y += body[i].y;
		body_center.z += body[i].z;
	}
	body_center.x /= 8.0; body_center.y /= 8.0; body_center.z /= 8.0;
}

void james::sethair_plane() {
	for (int i = 0; i < 4; i++) {//plane0, point0-3
		hair_plane[0].point[i].x = hair[i].x;
		hair_plane[0].point[i].y = hair[i].y;
		hair_plane[0].point[i].z = hair[i].z;

		hair_plane[1].point[i].x = hair[i + 4].x;//plane1, point4-7
		hair_plane[1].point[i].y = hair[i + 4].y;
		hair_plane[1].point[i].z = hair[i + 4].z;

		if (i < 2) {
			hair_plane[2].point[i].x = hair[i].x;
			hair_plane[2].point[i].y = hair[i].y;
			hair_plane[2].point[i].z = hair[i].z;

			hair_plane[3].point[i].x = hair[i + 1].x;
			hair_plane[3].point[i].y = hair[i + 1].y;
			hair_plane[3].point[i].z = hair[i + 1].z;

			hair_plane[4].point[i].x = hair[i + 2].x;
			hair_plane[4].point[i].y = hair[i + 2].y;
			hair_plane[4].point[i].z = hair[i + 2].z;

			int j = (i + 3) % 4;
			hair_plane[5].point[i].x = hair[j].x;
			hair_plane[5].point[i].y = hair[j].y;
			hair_plane[5].point[i].z = hair[j].z;
		}
		else if (i == 2) {
			hair_plane[2].point[i].x = hair[5].x;
			hair_plane[2].point[i].y = hair[5].y;
			hair_plane[2].point[i].z = hair[5].z;

			hair_plane[3].point[i].x = hair[6].x;
			hair_plane[3].point[i].y = hair[6].y;
			hair_plane[3].point[i].z = hair[6].z;

			hair_plane[4].point[i].x = hair[7].x;
			hair_plane[4].point[i].y = hair[7].y;
			hair_plane[4].point[i].z = hair[7].z;

			hair_plane[5].point[i].x = hair[4].x;
			hair_plane[5].point[i].y = hair[4].y;
			hair_plane[5].point[i].z = hair[4].z;
		}
		else if (i == 3) {
			hair_plane[2].point[i].x = hair[4].x;
			hair_plane[2].point[i].y = hair[4].y;
			hair_plane[2].point[i].z = hair[4].z;

			hair_plane[3].point[i].x = hair[5].x;
			hair_plane[3].point[i].y = hair[5].y;
			hair_plane[3].point[i].z = hair[5].z;

			hair_plane[4].point[i].x = hair[6].x;
			hair_plane[4].point[i].y = hair[6].y;
			hair_plane[4].point[i].z = hair[6].z;

			hair_plane[5].point[i].x = hair[7].x;
			hair_plane[5].point[i].y = hair[7].y;
			hair_plane[5].point[i].z = hair[7].z;
		}
	}
	
	for (int i = 0; i < 6; i++) {
		hair_plane[i].center.x = 0;
		hair_plane[i].center.y = 0;
		hair_plane[i].center.z = 0;
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			hair_plane[i].center.x += hair_plane[i].point[j].x;
			hair_plane[i].center.y += hair_plane[i].point[j].y;
			hair_plane[i].center.z += hair_plane[i].point[j].z;
		}
	}
	for (int i = 0; i < 6; i++) {
		hair_plane[i].center.x /= 4.0;
		hair_plane[i].center.y /= 4.0;
		hair_plane[i].center.z /= 4.0;
	}
}

void james::setface_plane() {
	for (int i = 0; i < 4; i++) {//plane0, point0-3
		face_plane[0].point[i].x = face[i].x;
		face_plane[0].point[i].y = face[i].y;
		face_plane[0].point[i].z = face[i].z;

		face_plane[1].point[i].x = face[i + 4].x;//plane1, point4-7
		face_plane[1].point[i].y = face[i + 4].y;
		face_plane[1].point[i].z = face[i + 4].z;

		if (i < 2) {
			face_plane[2].point[i].x = face[i].x;
			face_plane[2].point[i].y = face[i].y;
			face_plane[2].point[i].z = face[i].z;

			face_plane[3].point[i].x = face[i + 1].x;
			face_plane[3].point[i].y = face[i + 1].y;
			face_plane[3].point[i].z = face[i + 1].z;

			face_plane[4].point[i].x = face[i + 2].x;
			face_plane[4].point[i].y = face[i + 2].y;
			face_plane[4].point[i].z = face[i + 2].z;

			int j = (i + 3) % 4;
			face_plane[5].point[i].x = face[j].x;
			face_plane[5].point[i].y = face[j].y;
			face_plane[5].point[i].z = face[j].z;
		}
		else if (i == 2) {
			face_plane[2].point[i].x = face[5].x;
			face_plane[2].point[i].y = face[5].y;
			face_plane[2].point[i].z = face[5].z;

			face_plane[3].point[i].x = face[6].x;
			face_plane[3].point[i].y = face[6].y;
			face_plane[3].point[i].z = face[6].z;

			face_plane[4].point[i].x = face[7].x;
			face_plane[4].point[i].y = face[7].y;
			face_plane[4].point[i].z = face[7].z;

			face_plane[5].point[i].x = face[4].x;
			face_plane[5].point[i].y = face[4].y;
			face_plane[5].point[i].z = face[4].z;
		}
		else if (i == 3) {
			face_plane[2].point[i].x = face[4].x;
			face_plane[2].point[i].y = face[4].y;
			face_plane[2].point[i].z = face[4].z;

			face_plane[3].point[i].x = face[5].x;
			face_plane[3].point[i].y = face[5].y;
			face_plane[3].point[i].z = face[5].z;

			face_plane[4].point[i].x = face[6].x;
			face_plane[4].point[i].y = face[6].y;
			face_plane[4].point[i].z = face[6].z;

			face_plane[5].point[i].x = face[7].x;
			face_plane[5].point[i].y = face[7].y;
			face_plane[5].point[i].z = face[7].z;
		}
	}

	for (int i = 0; i < 6; i++) {
		face_plane[i].center.x = 0;
		face_plane[i].center.y = 0;
		face_plane[i].center.z = 0;
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			face_plane[i].center.x += face_plane[i].point[j].x;
			face_plane[i].center.y += face_plane[i].point[j].y;
			face_plane[i].center.z += face_plane[i].point[j].z;
		}
	}
	for (int i = 0; i < 6; i++) {
		face_plane[i].center.x /= 4.0;
		face_plane[i].center.y /= 4.0;
		face_plane[i].center.z /= 4.0;
	}
}

void james::setbody_plane() {
	for (int i = 0; i < 4; i++) {//plane0, point0-3
		body_plane[0].point[i].x = body[i].x;
		body_plane[0].point[i].y = body[i].y;
		body_plane[0].point[i].z = body[i].z;

		body_plane[1].point[i].x = body[i + 4].x;//plane1, point4-7
		body_plane[1].point[i].y = body[i + 4].y;
		body_plane[1].point[i].z = body[i + 4].z;

		if (i < 2) {
			body_plane[2].point[i].x = body[i].x;
			body_plane[2].point[i].y = body[i].y;
			body_plane[2].point[i].z = body[i].z;

			body_plane[3].point[i].x = body[i + 1].x;
			body_plane[3].point[i].y = body[i + 1].y;
			body_plane[3].point[i].z = body[i + 1].z;

			body_plane[4].point[i].x = body[i + 2].x;
			body_plane[4].point[i].y = body[i + 2].y;
			body_plane[4].point[i].z = body[i + 2].z;

			int j = (i + 3) % 4;
			body_plane[5].point[i].x = body[j].x;
			body_plane[5].point[i].y = body[j].y;
			body_plane[5].point[i].z = body[j].z;
		}
		else if (i == 2) {
			body_plane[2].point[i].x = body[5].x;
			body_plane[2].point[i].y = body[5].y;
			body_plane[2].point[i].z = body[5].z;

			body_plane[3].point[i].x = body[6].x;
			body_plane[3].point[i].y = body[6].y;
			body_plane[3].point[i].z = body[6].z;

			body_plane[4].point[i].x = body[7].x;
			body_plane[4].point[i].y = body[7].y;
			body_plane[4].point[i].z = body[7].z;

			body_plane[5].point[i].x = body[4].x;
			body_plane[5].point[i].y = body[4].y;
			body_plane[5].point[i].z = body[4].z;
		}
		else if (i == 3) {
			body_plane[2].point[i].x = body[4].x;
			body_plane[2].point[i].y = body[4].y;
			body_plane[2].point[i].z = body[4].z;

			body_plane[3].point[i].x = body[5].x;
			body_plane[3].point[i].y = body[5].y;
			body_plane[3].point[i].z = body[5].z;

			body_plane[4].point[i].x = body[6].x;
			body_plane[4].point[i].y = body[6].y;
			body_plane[4].point[i].z = body[6].z;

			body_plane[5].point[i].x = body[7].x;
			body_plane[5].point[i].y = body[7].y;
			body_plane[5].point[i].z = body[7].z;
		}
	}
	

	for (int i = 0; i < 6; i++) {
		body_plane[i].center.x = 0;
		body_plane[i].center.y = 0;
		body_plane[i].center.z = 0;
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			body_plane[i].center.x += body_plane[i].point[j].x;
			body_plane[i].center.y += body_plane[i].point[j].y;
			body_plane[i].center.z += body_plane[i].point[j].z;
		}
	}
	for (int i = 0; i < 6; i++) {
		body_plane[i].center.x /= 4.0;
		body_plane[i].center.y /= 4.0;
		body_plane[i].center.z /= 4.0;
	}
}

void james::setBlood(int b) {
	blood = b;
}

void james::operator-=(int d) {
	blood -= d;
	if (blood < 0)
		blood = 0;
}

int james::getBlood() {
	return blood;
}

void james::lost_one_bullet() {
	magazine.bullet_num--;
	if (magazine.bullet_num <= 0)
		magazine.can_use = false;
}

void james::change_magazine() {
	if (bullet_remain + magazine.bullet_num >= 20) {
		bullet_remain -= (MAGAZINE_BULLET_NUM - magazine.bullet_num);
		magazine.bullet_num = MAGAZINE_BULLET_NUM;
		magazine.can_use = true;
	}
	else {
		magazine.bullet_num += bullet_remain;
		bullet_remain = 0;
		magazine.can_use = (magazine.bullet_num > 0) ? true : false;
	}
}

bool james::getCanShoot() {
	return magazine.can_use;
}

void james::set_view_speed(double v) {
	view_speed = v;
}

double james::get_view_speed() {
	return view_speed;
}

void james::reset_run_time() {
	run_judge_time = DOUBLE_TAB_JUDGE_TIME;
}

int james::get_run_time() {
	return run_judge_time;
}

void james::reset_viewR_time() {
	viewR_time = DOUBLE_TAB_JUDGE_TIME;
}

int james::get_viewR_time() {
	return viewR_time;
}

void james::reset_viewL_time() {
	viewL_time = DOUBLE_TAB_JUDGE_TIME;
}

int james::get_viewL_time() {
	return viewL_time;
}

double james::getrt() {
	return (reload_time * (3 / RELOAD_TIME)*10);
}

void james::start_change_magazine() {
	reload_time = RELOAD_TIME;
}



bool james::Isreloading() {
	if (reload_time > 0)
		return true;
	else {
		return false;
	}
}

bool james::punch(points p) {
	if (getdist_from_other(p) <= JAMES_WIDTH * PUNCH_AREA) {
		return true;
	}
	return false;
}

void james::crouch() {
	CROUCHorNOT = true;
	crouch_level = CROUCH_LEVEL;
	point.z = JAMES_HEIGHT - CROUCH_LEVEL+current_floor;
}

void james::stand() {
	CROUCHorNOT = false;
	crouch_level = 0;
	point.z = JAMES_HEIGHT+current_floor;
}

void james::slide() {
	slide_time = SLIDE_TIME;
}

void james::cal_oppo_angle(points pos) {
	points v;
	v.x = pos.x - point.x; v.y = pos.y - point.y; v.z = pos.z - point.z;
	double fr = (view_vector.x * v.x + view_vector.y * v.y + view_vector.z * v.z) / 
		sqrt((view_vector.x * view_vector.x + view_vector.y * view_vector.y + view_vector.z * view_vector.z) * (v.x * v.x + v.y * v.y + v.z * v.z));
	if (fr >= 1)
		fr = 1;
	else if (fr <= -1)
		fr = -1;
	oppo_angle = acos(fr);
	oppo_angle *= 180.0 / M_PI;
}

double james::getOppoAngle(points pos) {
	cal_oppo_angle(pos);
	if ((pos.x - point.x) * view_vector.y - (pos.y - point.y) * view_vector.x < 0) //left
		oppo_angle *= -1;
	return oppo_angle;
}

void james::Zip(points zip) {
	IsZip = true;
	points dir;
	dir.x = zip.x - point.x; dir.y = zip.y - point.y; dir.z = zip.z - point.z;
	point.x += JAMES_ZIPSPEED * dir.x * 0.01;
	point.y += JAMES_ZIPSPEED * dir.y * 0.01;
	point.z += JAMES_ZIPSPEED * dir.z * 0.01;
}

bool james::IsZIP() {
	return IsZip;
}

void james::NotZip() {
	IsZip = false;
}