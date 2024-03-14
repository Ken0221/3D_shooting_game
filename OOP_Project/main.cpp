#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include "RenderWindow.h"
#include "System.h"
#include "constants.h"
#include "james.h"
#include "plane.h"
#include "points.h"
#include "object.h"
#include "mouse.h"
#include "Bullet.h"
#include "Zip.h"
#include "Image.h"
#include "Text.h"
#include "SDL_ttf.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// Using SDL2_mixer
#include <SDL_mixer.h>
#include "Mixer.h"

int GOAL_KILLNUM = 3;
int top = 140; //setting
int ptop = 200; //prepare
int bottomnum = 7;
int pbottomnum = 4;
const int max_num_of_cube = 87;
int num_of_cube = 20;

int MouseCenter = 1;
bool prepare = true;
bool setting = false;
bool regresh = false;
bool exitgame = false;
bool pbottom[4] = { false,false,false,false };
bool p2mode = false;
bool gamepause = false;
bool count_down = false;
bool endgame = false;

int w_num = 1;
int w2_num = 1;
int v_num = 1;
int c_num = 1;
int v2_num = 1;
int c2_num = 1;


/// setting bottom ///
bool badd[7] = { false,false,false,false,false,false,false };
bool bsub[7] = { false,false,false,false,false,false,false };
char number[10] [2] = { "0","1","2","3","4","5","6","7","8","9"};
char datanum[10] = "\0";
int datatmp = 0;

void handleEvent(SDL_Event& e, james& j, james& v, mouse& m, Bullet& b, Bullet& b2, Zip& z, Zip& z2, Mixer& m1, Mixer& effect1, Mixer& effect2, Image& fist, Image& fist2)
{
	


	// If a key was pressed
	// repeat: non-zero if this is a key repeat
	// https://wiki.libsdl.org/SDL_KeyboardEvent
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_0:
			if (endgame) {
				endgame = false;
				prepare = true;
			}
		case SDLK_w: 
			if (!j.IsZIP()) {
				if (j.get_run_time() > 0 && !j.IsCrouch())
					w_num = 3;
				else
					w_num = 1;
				j.reset_run_time();
				//cout << w_num << endl;
				j.set_velocity(RUN_SPEED * w_num);
				j.set_forward(1);
			}
			break; 
		case SDLK_a: 
			if (!j.IsZIP()) {
				j.set_left(1);
			} break; //go left
		case SDLK_s:
			if (!j.IsZIP()) {
				j.set_back(1);
			} break; //go back
		case SDLK_d: 
			if (!j.IsZIP()) {
				j.set_right(1);
			} break; //go right
		case SDLK_f: 
			if (j.get_viewL_time() > 0)
				c_num = 3;
			else
				c_num = 1;
			j.reset_viewL_time();
			j.set_view_angle_leftright_increment(TURN_SPEED * c_num); break; //turn left
		case SDLK_h: 
			if (j.get_viewR_time() > 0)
				v_num = 3;
			else
				v_num = 1;
			j.reset_viewR_time(); 
			j.set_view_angle_leftright_increment(-TURN_SPEED * v_num); break; //turn right
		case SDLK_t: j.set_view_angle_updown_increment(UPDOWN_SPEED); break; //view up
		case SDLK_g: j.set_view_angle_updown_increment(-UPDOWN_SPEED); break; //view down
		case SDLK_v: //shoot
			if (j.getCanShoot() && !j.Isreloading() && !b.getShow()) {
				b.reset(j);
				b.setShow(true);
				j.lost_one_bullet();
				effect1.playEffect(ONE, 0);
			} break;
		case SDLK_e: //punch
			fist.setAlpha(255);
			if (j.geta() * (v.getx() - j.getx()) + j.getb() * (v.gety() - j.gety()) + j.getc() * (v.getz() - j.getz()) > 0
				&& j.punch(v.getPoint())) {
				int damage = PUNCH_DAMAGE + (rand() % (2 * PUNCH_DEVIATION + 1) - PUNCH_DEVIATION);;
				int bonus;
				if (j.IsJump())
					bonus = 2;
				else
					bonus = 1;
				v -= damage * bonus;
				effect2.playEffect(ONE, 1);

			} break;
		case SDLK_q://zip
			if (!z.getShow() && z.ZipCount() >= 0) {
				z.reset(j);
				z.setShow(true);
			} break;
		case SDLK_r: j.start_change_magazine(); break; //換彈
		case SDLK_SPACE: j.setJampV(); break; //jump
		case SDLK_LCTRL: //crouch
			j.crouch(); 
			if (j.get_velocity() > RUN_SPEED) {
				j.set_velocity(RUN_SPEED * 5);
				j.slide();
			} break;




		case SDLK_UP:
			if (!v.IsZIP()) {
				if (v.get_run_time() > 0 && !v.IsCrouch())
					w2_num = 3;
				else
					w2_num = 1;
				v.reset_run_time();
				v.set_velocity(RUN_SPEED * w2_num);
				v.set_forward(1);
			}
			break;// go forward
		case SDLK_LEFT: 
			if (!v.IsZIP()) {
				v.set_left(1);
			} break; //go left
		case SDLK_DOWN:
			if (!v.IsZIP()) {
				v.set_back(1);
			} break; //go back
		case SDLK_RIGHT:
			if (!v.IsZIP()) {
				v.set_right(1);
			} break; //go right

		case SDLK_KP_1:
			if (v.get_viewL_time() > 0)
				c2_num = 3;
			else
				c2_num = 1;
			v.reset_viewL_time();
			v.set_view_angle_leftright_increment(TURN_SPEED * c2_num); break; //turn left
		case SDLK_j: 
			if (v.get_viewL_time() > 0)
				c2_num = 3;
			else
				c2_num = 1;
			v.reset_viewL_time();
			v.set_view_angle_leftright_increment(TURN_SPEED * c2_num); break; //turn left
		case SDLK_KP_2:
			if (v.get_viewR_time() > 0)
				v2_num = 3;
			else
				v2_num = 1;
			v.reset_viewR_time();
			v.set_view_angle_leftright_increment(-TURN_SPEED * v2_num); break; //turn right
		case SDLK_l:
			if (v.get_viewR_time() > 0)
				v2_num = 3;
			else
				v2_num = 1;
			v.reset_viewR_time();
			v.set_view_angle_leftright_increment(-TURN_SPEED * v2_num); break; //turn right
		case SDLK_KP_4: v.set_view_angle_updown_increment(UPDOWN_SPEED); break; //view up
		case SDLK_i: v.set_view_angle_updown_increment(UPDOWN_SPEED); break; //view up
		case SDLK_KP_0: v.set_view_angle_updown_increment(-UPDOWN_SPEED); break; //view down
		case SDLK_k: v.set_view_angle_updown_increment(-UPDOWN_SPEED); break; //view down
		

		case SDLK_KP_ENTER:  //shoot
			if (v.getCanShoot() && !v.Isreloading() && !b2.getShow()) {
				b2.reset(v);
				b2.setShow(true);
				v.lost_one_bullet();
				effect1.playEffect(ONE, 1);
			} break;
		case SDLK_SLASH: //shoot
			if (v.getCanShoot() && !v.Isreloading() && !b2.getShow()) {
				b2.reset(v);
				b2.setShow(true);
				v.lost_one_bullet();
				effect1.playEffect(ONE, 1);
			} break;
		case SDLK_KP_6://punch
			fist2.setAlpha(255);
			if (v.geta() * (j.getx() - v.getx()) + v.getb() * (j.gety() - v.gety()) + v.getc() * (j.getz() - v.getz()) > 0
				&& v.punch(j.getPoint())) {
				int damage = PUNCH_DAMAGE + (rand() % (2 * PUNCH_DEVIATION + 1) - PUNCH_DEVIATION);;
				j -= damage;
				effect2.playEffect(ONE, 1);
			} break;
		case SDLK_o: //punch
			fist2.setAlpha(255);
			if (v.geta() * (j.getx() - v.getx()) + v.getb() * (j.gety() - v.gety()) + v.getc() * (j.getz() - v.getz()) > 0
				&& v.punch(j.getPoint())) {
				int damage = PUNCH_DAMAGE + (rand() % (2 * PUNCH_DEVIATION + 1) - PUNCH_DEVIATION);;
				j -= damage;
				effect2.playEffect(ONE, 1);
			} break;

		case SDLK_KP_5:v.start_change_magazine(); break; //換彈
		case SDLK_p:v.start_change_magazine(); break; //換彈
		case SDLK_KP_3:v.setJampV(); break; //jump
		case SDLK_RALT: v.setJampV(); break; //jump
		case SDLK_RCTRL: //crouch
			v.crouch();
			if (v.get_velocity() > RUN_SPEED) {
				v.set_velocity(RUN_SPEED * 5);
				v.slide();
			} break;
		case SDLK_n: //crouch
			v.crouch();
			if (v.get_velocity() > RUN_SPEED) {
				v.set_velocity(RUN_SPEED * 5);
				v.slide();
			} break;
		case SDLK_u://zip
			if (!z2.getShow() && z2.ZipCount() >= 0) {
				z2.reset(v);
				z2.setShow(true);
			} break;
		case SDLK_KP_7://zip
			if (!z2.getShow() && z2.ZipCount() >= 0) {
				z2.reset(v);
				z2.setShow(true);
			} break;


		case SDLK_8:v.start_change_magazine(); break;
		case SDLK_y:v.setJampV(); break;
		case SDLK_ESCAPE: 
			m.showCursor(true); 
			if (endgame) {
				endgame = false;
				prepare = true;
			}
			break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
			case SDLK_w:
				if (w_num >= 3) {
					w_num = 0;
				}
				j.set_velocity(RUN_SPEED);
				j.set_forward(0); 
				break;// go forward
			case SDLK_a: j.set_left(0); break; //go left
			case SDLK_s: j.set_back(0); break; //go back
			case SDLK_d: j.set_right(0); break; //go right
			case SDLK_f: 
				if (c_num >= 3) {
					c_num = 0;
				}
				j.set_view_angle_leftright_increment(0);
				break; //turn left
			case SDLK_h: 
				if (v_num >= 3) {
					v_num = 0;
				}
				j.set_view_angle_leftright_increment(0);
				break; //turn right
			case SDLK_t: j.set_view_angle_updown_increment(0); break; //view up
			case SDLK_g:  j.set_view_angle_updown_increment(0); break; //view down
			case SDLK_LCTRL: //crouch
				j.stand(); j.set_velocity(RUN_SPEED); break;


			case SDLK_UP:
				if (w2_num >= 3) {
					w2_num = 0;
				}
				v.set_velocity(RUN_SPEED);
				v.set_forward(0);
				break;// go forward
			case SDLK_LEFT: v.set_left(0); break; //go left
			case SDLK_DOWN: v.set_back(0); break; //go back
			case SDLK_RIGHT: v.set_right(0); break; //go right
			case SDLK_KP_1:
				if (c2_num >= 3) {
					c2_num = 0;
				}
				v.set_view_angle_leftright_increment(0);
				break; //turn left
			case SDLK_KP_2:
				if (v2_num >= 3) {
					v2_num = 0;
				} 
				v.set_view_angle_leftright_increment(0);
				break; //turn right
			case SDLK_KP_4: v.set_view_angle_updown_increment(0); break; //view up
			case SDLK_KP_0: v.set_view_angle_updown_increment(0); break; //view down
			case SDLK_RCTRL: v.stand(); v.set_velocity(RUN_SPEED); break; //crouch
			case SDLK_n: v.stand(); v.set_velocity(RUN_SPEED); break; //crouch


			
			case SDLK_j: 
				if (c2_num >= 3) {
					c2_num = 0;
				}
				v.set_view_angle_leftright_increment(0);
				break; //turn left
			case SDLK_l:
				if (v2_num >= 3) {
					v2_num = 0;
				} 
				v.set_view_angle_leftright_increment(0);
				break; //turn right
			case SDLK_i: v.set_view_angle_updown_increment(0); break; //view up
			case SDLK_k: v.set_view_angle_updown_increment(0); break; //view down
			


			case SDLK_ESCAPE:
				if (p2mode) {
					gamepause = true;
				}
				
				break;
		}
	}
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP || e.type == SDL_MOUSEWHEEL)
	{
		// Get mouse position
		// https://wiki.libsdl.org/SDL_GetMouseState		
		SDL_GetMouseState(m.getx_adr(), m.gety_adr());

		for (int i = 0; i < pbottomnum; i++) {
			if (m.getx() > 400 && m.getx() < 800 && m.gety() > ptop + i * 100 && m.gety() < ptop+50 + i * 100) {
				pbottom[i] = true;
			}
			else {
				pbottom[i] = false;
			}
		}

		for (int i = 0; i < bottomnum; i++) {
			if (m.getx() > 550 && m.getx() < 600 && m.gety() > top + i * 50 && m.gety() < top+50 + i * 50) {
				bsub[i] = true;
			}
			else {
				bsub[i] = false;
			}
		}

		for (int i = 0; i < bottomnum; i++) {
			if (m.getx() > 950 && m.getx() < 1000 && m.gety() > top + i * 50 && m.gety() < top+50 + i * 50) {
				badd[i] = true;
			}
			else {
				badd[i] = false;
			}
		}

		m.mouse_settheta();
		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (e.button.button == SDL_BUTTON_LEFT)//&& e.button.clicks == 1)
			{
				if (j.getCanShoot() && !j.Isreloading() && !b.getShow() && !gamepause && !prepare) {
					b.reset(j);
					b.setShow(true);
					j.lost_one_bullet();
					effect1.playEffect(ONE, 0);
				}

				for (int i = 0; i < bottomnum; i++) {
					if (badd[i] && setting) {
						if (i == 0) {
							if (j.get_velocity() >= 14)
								continue;
							j.set_velocity(j.get_velocity() + 2);
							v.set_velocity(v.get_velocity() + 2);
						}
						if (i == 1) {
							if (j.getjumpvelocity() >= 6000)
								continue;
							j.setjumpvelocity(j.getjumpvelocity() + 1000);
							v.setjumpvelocity(v.getjumpvelocity() + 1000);
						}
						if (i == 2) {
							if (GOAL_KILLNUM >= 7)
								continue;
							GOAL_KILLNUM++;
						}
						if (i == 3) {
							if (j.get_max_viewupdown() >= 6)
								continue;
							j.set_max_viewupdown(j.get_max_viewupdown() + 1);
							v.set_max_viewupdown(v.get_max_viewupdown() + 1);
						}
						if (i == 4) {
							if (j.getfullhp() >= 100)
								continue;
							j.setfullhp(j.getfullhp() + 15);
							v.setfullhp(v.getfullhp() + 15);

						}
						if (i == 5) {
							if (z.get_fullziptimes() >= 5)
								continue;
							z.set_fullziptimes(z.get_fullziptimes() + 1);
							z2.set_fullziptimes(z2.get_fullziptimes() + 1);
						}
						if (i == 6) {
							if (num_of_cube >= 87)
								continue;
							num_of_cube++;
						}
					}
					if (bsub[i] && setting) {
						if (i == 0) {
							if (j.get_velocity() <= 2)
								continue;
							j.set_velocity(j.get_velocity() - 2);
							v.set_velocity(v.get_velocity() - 2);
						}
						if (i == 1) {
							if (j.getjumpvelocity() <= 0)
								continue;
							j.setjumpvelocity(j.getjumpvelocity() - 1000);
							v.setjumpvelocity(v.getjumpvelocity() - 1000);
						}
						if (i == 2) {
							if (GOAL_KILLNUM <= 1)
								continue;
							GOAL_KILLNUM--;
						}
						if (i == 3) {
							if (j.get_max_viewupdown() <= 0)
								continue;
							j.set_max_viewupdown(j.get_max_viewupdown() - 1);
							v.set_max_viewupdown(v.get_max_viewupdown() - 1);
						}
						if (i == 4) {
							if (j.getfullhp() <= 10)
								continue;
							j.setfullhp(j.getfullhp() - 15);
							v.setfullhp(v.getfullhp() - 15);
						}
						if (i == 5) {
							if (z.get_fullziptimes() <= -1)
								continue;
							z.set_fullziptimes(z.get_fullziptimes() - 1);
							z2.set_fullziptimes(z2.get_fullziptimes() - 1);
						}
						if (i == 6) {
							if (num_of_cube <= 0)
								continue;
							num_of_cube--;
						}
					}
				}

				if (pbottom[0]) {
					if (prepare && !setting) {
						prepare = false;
						p2mode = true;
					}
					if (gamepause && !setting) {
						gamepause = false;
					}
				}
				if (pbottom[1]) {

					if (prepare) {
						setting = true;
					}
					if (gamepause) {
						setting = true;
					}

				}
				if (pbottom[2]) {
					if (prepare && !setting && !gamepause) {
						exitgame = true;
					}
					if (gamepause && !setting) {
						gamepause = false;
						prepare = true;
					}

				}
				if (pbottom[3]) {

					if (prepare && !setting) {

					}
					if (setting) {
						setting = false;
						prepare = true;
					}

				}

			}
			break;

		case SDL_MOUSEBUTTONUP:
			break;

		case SDL_MOUSEWHEEL:
			//cout << "wheel" << endl;
			if (setting) {
				if (e.wheel.y > 0) // scroll up
				{
					if (num_of_cube < 87)
						num_of_cube++;
					//cout << num_of_cube << endl;
				}
				else if (e.wheel.y < 0) // scroll down
				{
					if (num_of_cube > 0)
						num_of_cube--;
					//cout << num_of_cube << endl;

				}
			}
			break;


		case SDL_MOUSEMOTION:
			break;

		default:
			break;
		}
	}
}

void drawmap(RenderWindow rw,james j,points** allp) {
	int time = 25;
	points mappoint[100][8];
	for (int i = 0; i < num_of_cube + 1; i++) {
		mappoint[i][3].x = allp[i][3].x / time;
		mappoint[i][3].y = allp[i][3].y / time;
		mappoint[i][6].x = allp[i][6].x / time;
		mappoint[i][6].y = allp[i][6].y / time;
	}

	boxRGBA(rw.getRenderer(), mappoint[0][3].y, mappoint[0][3].x, mappoint[0][6].y, mappoint[0][6].x, 50, 50, 50, 150);
	for (int i = 1; i <= num_of_cube; i++) {
		boxRGBA(rw.getRenderer(), mappoint[i][3].y, mappoint[i][3].x, mappoint[i][6].y, mappoint[i][6].x, 30, 106, 173, 150);
	}

	filledCircleRGBA(rw.getRenderer(), j.gety() / time + j.get_unitviewy()*5 , j.getx() / time + j.get_unitviewx()*5 , 3, 255, 255, 0, 255);
	filledCircleRGBA(rw.getRenderer(), j.gety()/time, j.getx()/time, 5, 255, 0, 0, 255);

}


/*new for blood and direction*/
Uint32 changeDataImage(Uint32 interval, void* param)
{
	Image* p = (Image*)param;

	if (p->getAlpha() <= 0)
	{
		p->setAlpha(0);
		return 0;
	}
	else
	{
		p->setAlpha(p->getAlpha() - 17);
	}

	return interval;
}



void setCube(points **cube, points s, points l, int n) {
	cube[n][0].x = s.x;	cube[n][0].y = s.y;	cube[n][0].z = s.z;
	cube[n][1].x = s.x;	cube[n][1].y = l.y;	cube[n][1].z = s.z;
	cube[n][2].x = s.x;	cube[n][2].y = l.y;	cube[n][2].z = l.z;
	cube[n][3].x = s.x;	cube[n][3].y = s.y;	cube[n][3].z = l.z;
	cube[n][4].x = l.x;	cube[n][4].y = s.y;	cube[n][4].z = s.z;
	cube[n][5].x = l.x;	cube[n][5].y = l.y;	cube[n][5].z = s.z;
	cube[n][6].x = l.x;	cube[n][6].y = l.y;	cube[n][6].z = l.z;
	cube[n][7].x = l.x;	cube[n][7].y = s.y;	cube[n][7].z = l.z;
}

int main(int argc, char* args[])
{
	System sdl;

	// Start up SDL and create window
	if (!sdl.init())
	{
		printf("Failed to initialize SDL system!\n");
		return -1;
	}

	srand(time(NULL));

	RenderWindow window("OOP_3D_GAME", 20, 20, WIDTH, HEIGHT);
	
	Image background("../image/background.png", window.getRenderer());
	Image blood("../image/blood.png", window.getRenderer());
	Image blood2("../image/blood2.png", window.getRenderer());
	Image arrow("../image/arrow3.png", window.getRenderer());
	Image arrow2("../image/arrow3.png", window.getRenderer());
	Image fist("../image/fist.png", window.getRenderer());
	Image fist2("../image/fist2.png", window.getRenderer());
	Mixer m1("../audio/m01_out.mp3", MUSIC);
	Mixer e1("../audio/e01.wav", EFFECT);
	Mixer e2("../audio/e02.wav", EFFECT);
	
	
	window.addVpregion({ {0, 0, WIDTH / 2, HEIGHT}, {WIDTH / 2, 0, WIDTH / 2, HEIGHT} });
	window.addVpregion({ { 0, 0, WIDTH , HEIGHT } });
	

	char txt[33][50];
	char font[2][50];
	FILE* fpt = fopen("txtpath.txt", "r");
	rewind(fpt);
	fscanf(fpt, "%s", &font[0]);
	fscanf(fpt, "%s", &font[1]);
	for (int i = 0; i < 33; i++) {
		fscanf(fpt, "%s", &txt[i]);
		
	}
	fclose(fpt);


	FILE* fm = fopen("map.dat", "rb");
	if (!fm)
	{
		cout << "error" << endl;
		exit(1);
	}
	points **all_p = new points * [max_num_of_cube + 1];
	for (int i = 0; i < max_num_of_cube + 1; i++) {
		all_p[i] = new points[8];
	}
	points *s = new points[max_num_of_cube + 1];
	points *l = new points[max_num_of_cube + 1];
	rewind(fm);
	fread(&(s[0].x), sizeof(double), 1, fm);		fread(&(s[0].y), sizeof(double), 1, fm);		fread(&(s[0].z), sizeof(double), 1, fm);
	fread(&(l[0].x), sizeof(double), 1, fm);		fread(&(l[0].y), sizeof(double), 1, fm);		fread(&(l[0].z), sizeof(double), 1, fm);
	int valid_i[max_num_of_cube + 1] = { 0 };
	valid_i[0] = 1;
	int count_i = 0;
	while (count_i < max_num_of_cube)
	{
		int fm_i = rand() % (max_num_of_cube) + 1;
		if (valid_i[fm_i] == 0) {
			fread(&(s[fm_i].x), sizeof(double), 1, fm);		fread(&(s[fm_i].y), sizeof(double), 1, fm);		fread(&(s[fm_i].z), sizeof(double), 1, fm);
			fread(&(l[fm_i].x), sizeof(double), 1, fm);		fread(&(l[fm_i].y), sizeof(double), 1, fm);		fread(&(l[fm_i].z), sizeof(double), 1, fm);
			
			valid_i[fm_i] = 1;
			count_i++;
		}
	}
	fclose(fm);



	for (int i = 0; i < max_num_of_cube + 1; i++)
	{
		setCube(all_p, s[i], l[i], i);
	}

	delete []s;
	delete []l;

	

	Object *cube_const = new Object[max_num_of_cube];
	Object cube_room(all_p[0]);

	for (int i = 0; i < max_num_of_cube; i++)
	{
		cube_const[i].setPlane(all_p[i + 1]);
	}

	for (int i = 0; i < max_num_of_cube; i++)
	{
		cube_const[i].setcolor(0xFFD2B48C);
	}


	
	Image gun("../image/g.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	Image gun2("../image/gcut.png", window.getRenderer(), 0xFF, 0xFF, 0xFF);
	
	james ken(300, 300, JAMES_HEIGHT, 0, 0);
	james evan(3850, 3850, JAMES_HEIGHT, 180, 0);

	Bullet bullet(ken, 0xFFFF0000);
	Bullet bullet2(evan, 0xFFFF0000);
	Zip zip1(ken, 0xFF8B4513);
	Zip zip2(evan, 0xFF8B4513);
	mouse ms;
	ms.startTimer(20);
	bullet.startTimer(10);
	bullet2.startTimer(10);
	zip1.startTimer(10);
	zip2.startTimer(10);
	ken.startTimer(10);
	evan.startTimer(10);


	// Flip type	
	SDL_RendererFlip no = SDL_FLIP_NONE;
	SDL_RendererFlip ho = SDL_FLIP_HORIZONTAL;
	SDL_RendererFlip ve = SDL_FLIP_VERTICAL;
	SDL_RendererFlip hove = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);

	// The working directory is where the vcxproj file is located.			
	Text b3word(txt[0], font[0], 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, {0, 255, 255}, BLENDED, {100, 100, 100}, window.getRenderer(), {480, 400}, {NULL, NULL}, NULL, no, 150);
	Text b1word(txt[1], font[0], 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 255, 251, 14 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 420, 200 }, { NULL, NULL }, NULL, no, 150);
	Text b2word(txt[2], font[0], 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 255, 251, 14 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 420, 300 }, { NULL, NULL }, NULL, no, 150);
	Text b4word(txt[3], font[0], 60, TTF_STYLE_UNDERLINE | TTF_STYLE_BOLD, { 0, 255, 255 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 530, 500 }, { NULL, NULL }, NULL, no, 150);
	Text runspeed(txt[4], font[1], 40, TTF_STYLE_NORMAL, { 255, 255, 104 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 350, top }, { NULL, NULL }, NULL, no, 255);
	Text jumpspeed(txt[5], font[1], 40, TTF_STYLE_NORMAL, { 255, 255, 104 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 280, top+50 }, { NULL, NULL }, NULL, no, 255);
	Text numofkill(txt[6], font[1], 40, TTF_STYLE_NORMAL, { 255, 255, 104 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 263, top+100 }, { NULL, NULL }, NULL, no, 255);
	Text maxviewupdown(txt[7], font[1], 40, TTF_STYLE_NORMAL, { 255, 255, 104 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 37, top+150 }, { NULL, NULL }, NULL, no, 255);
	Text hpnum(txt[8], font[1], 40, TTF_STYLE_NORMAL, { 255, 255, 104 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 410, top+200 }, { NULL, NULL }, NULL, no, 255);
	Text zipfullnum(txt[9], font[1], 40, TTF_STYLE_NORMAL, { 255, 255, 104 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 163, top + 250 }, { NULL, NULL }, NULL, no, 255);
	Text numcube(txt[10], font[1], 40, TTF_STYLE_NORMAL, { 255, 255, 104 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 230, top + 300 }, { NULL, NULL }, NULL, no, 255);

	Text setnum(txt[11], font[1], 40, TTF_STYLE_NORMAL, { 100, 0, 0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 225, 400 }, { NULL, NULL }, NULL, no, 255);
	Text cubenum1(txt[12], font[1], 40, TTF_STYLE_NORMAL, { 250, 250, 0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 225, 400 }, { NULL, NULL }, NULL, no, 255);
	Text cubenum2(txt[13], font[1], 40, TTF_STYLE_NORMAL, { 250, 250, 0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 225, 400 }, { NULL, NULL }, NULL, no, 255);

	Text up1num(txt[14], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 350, HEIGHT - 100 }, { NULL, NULL }, NULL, no, 255);
	Text up2num(txt[15], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 380, HEIGHT - 100 }, { NULL, NULL }, NULL, no, 255);
	Text up3num(txt[16], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 410, HEIGHT - 100 }, { NULL, NULL }, NULL, no, 255);
	Text down1num(txt[17], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 350, HEIGHT - 60 }, { NULL, NULL }, NULL, no, 255);
	Text down2num(txt[18], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 380, HEIGHT - 60 }, { NULL, NULL }, NULL, no, 255);
	Text down3num(txt[19], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 410, HEIGHT - 60 }, { NULL, NULL }, NULL, no, 255);

	Text hp1num(txt[20], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 30, HEIGHT - 60 }, { NULL, NULL }, NULL, no, 255);
	Text hp2num(txt[21], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 60, HEIGHT - 60 }, { NULL, NULL }, NULL, no, 255);
	Text hp3num(txt[22], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 90, HEIGHT - 60 }, { NULL, NULL }, NULL, no, 255);


	Text reloadtime1(txt[23], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 520, HEIGHT - 50 }, { NULL, NULL }, NULL, no, 255);
	Text reloadtime2(txt[24], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 550, HEIGHT - 50 }, { NULL, NULL }, NULL, no, 255);
	Text reloadtime3(txt[25], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 560, HEIGHT - 50 }, { NULL, NULL }, NULL, no, 255);
	Text reloadtime4(txt[26], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 590, HEIGHT - 50 }, { NULL, NULL }, NULL, no, 255);

	b3word.setString("setting");
	b3word.generateTexture();

	//new for blood and direction//////
	background.setAlpha(255);
	gun.setAlpha(255);
	gun2.setAlpha(255);
	blood.setAlpha(0);
	blood2.setAlpha(0);
	arrow.setAlpha(0);
	arrow2.setAlpha(0);
	fist.setAlpha(0);
	fist2.setAlpha(0);

	Text winlose(txt[27], font[1], 100, TTF_STYLE_NORMAL, { 255,255,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 150, 200 }, { NULL, NULL }, NULL, no, 255);

	Text killdie(txt[28], font[0], 50, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 170, 10 }, { NULL, NULL }, NULL, no, 255);
	Text killnumber(txt[29], font[0], 50, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 300, 10 }, { NULL, NULL }, NULL, no, 255);
	Text dienumber(txt[30], font[0], 50, TTF_STYLE_NORMAL | TTF_STYLE_BOLD, { 0, 0, 0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 500, 10 }, { NULL, NULL }, NULL, no, 255);

	Text hint1(txt[31], font[0], 50, TTF_STYLE_NORMAL, { 255, 251, 14 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { 365, 400 }, { NULL, NULL }, NULL, no, 255);
	Text hint2(txt[32], font[0], 50, TTF_STYLE_NORMAL, { 255, 251, 14 }, BLENDED, { 100, 100, 100 }, window.getRenderer(), { -10, 400 }, { NULL, NULL }, NULL, no, 255);

	Text zipnum(txt[32], font[1], 40, TTF_STYLE_NORMAL, { 0,0,0 }, SOLID, { NULL, NULL, NULL }, window.getRenderer(), { 30, HEIGHT - 100 }, { NULL, NULL }, NULL, no, 255);

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while (!quit)
	{
		
		changeDataImage(70, &blood);
		changeDataImage(70, &blood2);
		changeDataImage(70, &arrow);
		changeDataImage(70, &arrow2);
		changeDataImage(70, &fist);
		changeDataImage(70, &fist2);
		


		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			handleEvent(e, ken, evan, ms, bullet, bullet2, zip1, zip2, m1, e1, e2, fist, fist2);
		}

		if (exitgame) {
			break;
		}

		if (setting) {                     
			SDL_ShowCursor(true);
			window.setVP(ALLREGION);
			window.clear(0x000000FF);
			background.draw(window.getRenderer(), { ALLREGION }, { ALLREGION });
			runspeed.draw();
			jumpspeed.draw();
			numofkill.draw();
			maxviewupdown.draw();
			hpnum.draw();
			zipfullnum.draw();
			numcube.draw();

			for (int i = 0; i < bottomnum; i++) {
				boxRGBA(window.getRenderer(), 600, top + i * 50, 950, top+50 + i * 50, 100, 0, 0, 255);
				
				if (badd[i]) {
					boxRGBA(window.getRenderer(), 950, top + i * 50, 1000, top+50 + i * 50, 250, 250, 0, 150);
				}
				if (bsub[i]) {
					boxRGBA(window.getRenderer(), 550, top + i * 50, 600, top+50 + i * 50, 250, 250, 0, 150);
				}
				thickLineColor(window.getRenderer(), 975, top+5 + i * 50, 975, top+45 + i * 50, 10, 0xFF99FF00);
				thickLineColor(window.getRenderer(), 955, top+25 + i * 50, 995, top+25 + i * 50, 10, 0xFF99FF00);
				thickLineColor(window.getRenderer(), 555, top+25 + i * 50, 595, top+25 + i * 50, 10, 0xFF99FF00);
			}

			boxRGBA(window.getRenderer(), 550 + 50 * ken.get_velocity()/2, top, 600 + 50 * ken.get_velocity()/2, top+50, 250, 250, 0, 255);
			setnum.setString(" 1  2  3  4  5  6  7");
			setnum.setPos({ 600, top + 0 * 50 });
			setnum.generateTexture();
			setnum.draw();
			boxRGBA(window.getRenderer(), 550 + 50 * ken.getjumpvelocity()/1000 +50, top+50, 600 + 50 * ken.getjumpvelocity()/1000 +50, top+100, 250, 250, 0, 255);
			setnum.setString(" 0  1  2  3  4  5  6");
			setnum.setPos({ 600, top + 1 * 50 });
			setnum.generateTexture();
			setnum.draw();
			boxRGBA(window.getRenderer(), 550 + 50 * GOAL_KILLNUM, top+100, 600 + 50 * GOAL_KILLNUM, top+150, 250, 250, 0, 255);
			setnum.setString(" 1  2  3  4  5  6  7");
			setnum.setPos({ 600, top + 2 * 50 });
			setnum.generateTexture();
			setnum.draw();
			boxRGBA(window.getRenderer(), 550 + 50 * ken.get_max_viewupdown()+50, top+150, 600 + 50 * ken.get_max_viewupdown()+50, top+200, 250, 250, 0, 255);
			setnum.setString(" 0  1  2  3  4  5  6");
			setnum.setPos({ 600, top + 3 * 50 });
			setnum.generateTexture();
			setnum.draw();
			boxRGBA(window.getRenderer(), 550 + 50 * ((ken.getfullhp() - 10) / 15 + 1), top+200, 600 + 50 * ((ken.getfullhp() - 10) / 15 + 1), top+250, 250, 250, 0, 255);
			setnum.setString(" 1  2  3  4  5  6  7"); 
			setnum.setPos({ 600, top + 4 * 50 });
			setnum.generateTexture();
			setnum.draw();
			boxRGBA(window.getRenderer(), 550 + 50 * zip1.get_fullziptimes()+100, top+250, 600 + 50 * zip1.get_fullziptimes()+100, top + 300, 250, 250, 0, 255);
			setnum.setString(" 0  1  2  3  4  5  6");
			setnum.setPos({ 600, top + 5 * 50 });
			setnum.generateTexture();
			setnum.draw();

			datatmp = num_of_cube;
			cubenum2.setString(number[datatmp % 10]);
			cubenum2.setPos({ 1035, top + 305 });
			cubenum2.generateTexture();
			datatmp /= 10;
			cubenum1.setString(number[datatmp % 10]);
			cubenum1.setPos({ 1005, top + 305 });
			cubenum1.generateTexture();
			datatmp /= 10;
			boxRGBA(window.getRenderer(), 600 + 3.45 * num_of_cube, top + 300, 650 + 3.45 * num_of_cube, top + 350, 250, 250, 0, 255);
			cubenum1.draw();
			cubenum2.draw();

			thickLineColor(window.getRenderer(), 600, top , 950, top  , 1, 0xFFFFFFFF);
			for (int i = 0; i < bottomnum; i++) {
				thickLineColor(window.getRenderer(), 600, top+50 + i * 50, 950, top+50 + i * 50, 1, 0xFFFFFFFF);
			}

			if (pbottom[3]) {
				boxRGBA(window.getRenderer(), 400, 500, 800, 550, 250, 250, 0, 150);
			}
			
			b4word.setString("back");
			b4word.generateTexture();
			b4word.draw();

			window.display();
			continue;
		}


		if (gamepause) {
			SDL_ShowCursor(true);
			window.setVP(ALLREGION);
			boxRGBA(window.getRenderer(), 0, 0, WIDTH, HEIGHT, 0, 0, 0, 250);
			background.draw(window.getRenderer(), { ALLREGION }, { ALLREGION });


			for (int i = 0; i < 3; i++) {
				if (pbottom[i]) {
					boxRGBA(window.getRenderer(), 400, 200 + i * 100, 800, 250 + i * 100, 250, 250, 0, 150);
				}
			}
			b1word.setString("  continue  ");
			b1word.generateTexture();
			b2word.setString("  setting   ");
			b2word.generateTexture();
			
			b1word.draw();
			b3word.setFgColor({255,255,0,255});
			b3word.setString("  home  ");
			b3word.generateTexture();
			b2word.draw();
			b3word.draw();
			window.display();
			continue;
		}

		if (endgame) {
			SDL_ShowCursor(true);
			window.setVP(ALLREGION);

			ken.set_dienum(0);
			evan.set_dienum(0);
			ken.set_killnum(0);
			evan.set_killnum(0);

			prepare = false;

			continue;
		}

		if (prepare) {                 
			p2mode = false;
			SDL_ShowCursor(true);
			window.setVP(ALLREGION);
			window.clear(0x000000FF);
			background.draw(window.getRenderer(), { ALLREGION }, { ALLREGION });
			ken.reset();
			evan.reset();
			ken.set_killnum(0);
			evan.set_dienum(0);
			
			zip1.set_fullziptimes(zip1.get_fullziptimes());
			zip2.set_fullziptimes(zip2.get_fullziptimes());

			for (int i = 0; i < 3; i++) {
				if (pbottom[i]) {
					boxRGBA(window.getRenderer(), 400, 200 + i * 100, 800, 250 + i * 100, 250, 250, 0, 150);
				}
			}

			b1word.setString("   start    ");
			b1word.generateTexture();
			b2word.setString("  setting   ");
			b2word.generateTexture();
			b3word.setFgColor({ 0, 255, 255 });
			b3word.setString(" exit  ");
			b3word.generateTexture();
			
			b3word.draw();
			b1word.draw();
			b2word.draw();

			window.display();
			continue;
		}


		if (MouseCenter > 0 && ms.getMouseCenter()) {
			SDL_WarpMouseInWindow(window.getWindow(), WIDTH / 2, HEIGHT / 2);
			SDL_ShowCursor(false);
		}

		
		window.clear();

		ken.move(all_p, num_of_cube);
		evan.move(all_p, num_of_cube);

		if (ms.getMouseCenter() && MouseCenter > 0) {
			ken.change_view_angle(-1 * ms.gettheta_x(), -1 * ms.gettheta_y());
			evan.change_view_angle(0 * ms.gettheta_x(), 0 * ms.gettheta_y());
		}

		if (p2mode) {
			window.setVP(0);
			window.clearVP();
		}
		else {
			window.clear(0x000000FF);
			window.setVP(2);
			window.clearVP();
		}

		Object *cube = new Object[num_of_cube];
		for (int i = 0; i < num_of_cube; i++) {
			cube[i] = cube_const[i];
		}

		cube_room.draw(ken, window);

		for (int i = 0; i < num_of_cube - 1; i++) {
			for (int j = i + 1; j < num_of_cube; j++) {
				if (cube[i].getPoint() - ken < cube[j].getPoint() - ken) { // dist大者i小
					Object temp = cube[i];
					cube[i] = cube[j];
					cube[j] = temp;
				}
			}
		}

		int draw_order = -2;
		for (int i = 0; i < num_of_cube; i++) {
			double dist_other_from_other = ken.getPoint() - evan; 
			
			if (dist_other_from_other > cube[i].getPoint() - ken) {
				draw_order = i - 1;
				break;
			}
		}
		for (int i = 0; i < num_of_cube; i++) {
			if (draw_order == i || (draw_order == -2 && i == num_of_cube - 1) || (draw_order == -1 && i == 0))
				cube[i].draw_and_james(ken, window, evan, ken.getPoint() - evan, evan.IsCrouch());
			else
				cube[i].draw(ken, window);
		}
		if(num_of_cube == 0)
			ken.draw_opponent(evan.getPoint(), evan.getView_direction(), window, evan.IsCrouch());


		

		if (bullet.getShow()) {
			if (bullet.timerExpired()) {
				bullet.setShow(false);
			}
			else {
				
				if(p2mode)
					bullet.draw(ken, window, 2);
				else
					bullet.draw(ken, window, 1);

				if (bullet.IsHit(evan.getPoint())) {
					int damage = BULLET_DAMAGE + (rand() % (2 * BULLET_DEVIATION + 1) - BULLET_DEVIATION);
					ken.set_oppo_Color(0xFFFF0000);
					
					evan -= damage;

					bullet.setShow(false);
				}
				else if (bullet.IsHitWall(cube, num_of_cube)) {
					bullet.setShow(false);
				}
			}
		}
		else {
			ken.set_oppo_Color(0xFFFF9632);
		}

		if (bullet2.getShow()) {
			if (p2mode)
				bullet2.draw(ken, window, 2);
			else
				bullet2.draw(ken, window, 1);
			
		}


		if (bullet2.getIsHit())
		{
			blood.setAlpha(255);
			arrow.setAlpha(255);

			arrow.setDstRegion({ ALLREGION });
			arrow.setSrcRegion({ ALLREGION });
			arrow.setCenterAngle({ arrow2.getHeight() / 2, arrow2.getWidth() / 2 }, ken.getOppoAngle(evan.getPoint()));
			bullet2.setIsHit(false);

		}
		blood.draw(window.getRenderer(), { ALLREGION }, { ALLREGION });
		arrow.draw();

		if (zip1.getShow()) {
			if (zip1.getZipLength() > ZIP_LENGTH ||
				(ken.IsZIP() && zip1.getpoint1() - ken < CUBE_RADIUS * 1.5) || zip1.timerExpired()) {
				zip1.setShow(false);
				ken.NotZip();
			}
			else {
				
				if (p2mode)
					zip1.draw(ken, window, 2);
				else
					zip1.draw(ken, window, 1);
				
				if (zip1.IsHitWall(cube, num_of_cube)) {
					
					ken.Zip(zip1.getpoint1());
				}
				
			}
		}

		if (zip2.getShow()) {
			if (p2mode)
				zip2.draw(ken, window, 2);
			else
				zip2.draw(ken, window, 1);
			
		}
			
		gun2.setDstRegion({ ALLREGION });
		gun2.setSrcRegion({ ALLREGION });
		gun2.draw();
		
		fist.draw(window.getRenderer(), { ALLREGION }, { ALLREGION });

		drawmap(window, ken, all_p);
		if (ken.getBlood() > 0) {
			boxRGBA(window.getRenderer(), 30, HEIGHT - 60, ken.getBlood() * 3 + 30, HEIGHT - 20, 250, 0, 0, 250);
		}

		

		int km = ken.getmagazine();
		up3num.setString(number[km % 10]);
		up3num.generateTexture();
		km /= 10;
		up2num.setString(number[km % 10]);
		up2num.generateTexture();
		km /= 10;
		up1num.setString(number[km % 10]);
		up1num.generateTexture();
		km /= 10;

		int kbr = ken.getbullet_remain();
		down3num.setString(number[kbr % 10]);
		down3num.generateTexture();
		kbr /= 10;
		down2num.setString(number[kbr % 10]);
		down2num.generateTexture();
		kbr /= 10;
		down1num.setString(number[kbr % 10]);
		down1num.generateTexture();
		kbr /= 10;

		up1num.draw();
		up2num.draw();
		up3num.draw();
		down1num.draw();
		down2num.draw();
		down3num.draw();

		int hp = ken.getBlood();
		hp3num.setString(number[hp % 10]);
		hp3num.generateTexture();
		hp /= 10;
		hp2num.setString(number[hp % 10]);
		hp2num.generateTexture();
		hp /= 10;
		hp1num.setString(number[hp % 10]);
		hp1num.generateTexture();
		hp /= 10;

		hp1num.draw();
		hp2num.draw();
		hp3num.draw();


		hp = ken.getrt();
		if (hp < 0)
			hp = 0;
		
		if (hp != 0) {
			boxRGBA(window.getRenderer(), 510, HEIGHT - ken.getrt() * 5, 590, HEIGHT, 250, 250, 250, 205);
			reloadtime3.setString(number[hp % 10]);
			reloadtime3.generateTexture();
			hp /= 10;
			reloadtime2.setString(".");
			reloadtime2.generateTexture();
			
			reloadtime1.setString(number[hp % 10]);
			reloadtime1.generateTexture();
			hp /= 10;

			reloadtime1.draw();
			reloadtime2.draw();
			reloadtime3.draw();
		}

		int zct = zip1.ZipCount();
		if (zct >= 0)
			boxRGBA(window.getRenderer(), 30, HEIGHT - 100, 30 + (zct + 1) * 40, HEIGHT - 60, 0, 155, 255, 255);
		zipnum.setString(number[zct + 1]);
		zipnum.generateTexture();
		zipnum.draw();

		if (evan.getBlood() == 0 || ken.getBlood() == 0) {

			
			if (ken.getBlood() <= 0) {
				evan++; 
				ken--;
			}
			else {
				ken++;
				evan--;
			}
			evan.reset();
			ken.reset();
		}

		killdie.draw();
		killnumber.setString(number[ken.get_killnum()]);
		killnumber.generateTexture();
		dienumber.setString(number[ken.get_dienum()]);
		dienumber.generateTexture();
		killnumber.draw();
		dienumber.draw();

		if (evan.get_killnum() == GOAL_KILLNUM || ken.get_killnum() == GOAL_KILLNUM) {

			
			boxRGBA(window.getRenderer(), 0, 0, 600, HEIGHT, 50, 50, 50, 150);
			if (ken.get_killnum() == GOAL_KILLNUM) {
				winlose.setString("WIN");
			}
			else {
				winlose.setString("LOSE");
			}

			winlose.generateTexture();
			winlose.draw();

			hint1.draw();

			endgame = true;

		}


		if (p2mode) {
			
			window.setVP(1);
			window.clearVP();

			cube_room.draw(evan, window);

			for (int i = 0; i < num_of_cube - 1; i++) {
				for (int j = i + 1; j < num_of_cube; j++) {
					if (cube[i].getPoint() - evan < cube[j].getPoint() - evan) { // dist大者i小
						Object temp = cube[i];
						cube[i] = cube[j];
						cube[j] = temp;
					}
				}
			}

			draw_order = -2;
			for (int i = 0; i < num_of_cube; i++) {
				double dist_other_from_other = evan.getPoint() - ken;
				if (dist_other_from_other > cube[i].getPoint() - evan) {
					draw_order = i - 1;
					break;
				}
			}
			for (int i = 0; i < num_of_cube; i++) {
				if (draw_order == i || (draw_order == -2 && i == num_of_cube - 1) || (draw_order == -1 && i == 0))
					cube[i].draw_and_james(evan, window, ken, evan.getPoint() - ken, ken.IsCrouch());
				else
					cube[i].draw(evan, window);
			}
			if (num_of_cube == 0)
				evan.draw_opponent(ken.getPoint(), ken.getView_direction(), window, ken.IsCrouch());

			if (bullet.getShow()) {//ken的子彈 evan看
				bullet.draw(evan, window, 2);
			}

		
			if (bullet2.getShow()) {
				if (bullet2.timerExpired()) {
					bullet2.setShow(false);
				}
				else {
					
					bullet2.draw(evan, window, 2);
					if (bullet2.IsHit(ken.getPoint())) {
						int damage = BULLET_DAMAGE + (rand() % (2 * BULLET_DEVIATION + 1) - BULLET_DEVIATION);
						ken -= damage;
						evan.set_oppo_Color(0xFFFF0000);
						bullet2.setShow(false);
					}
					else if (bullet2.IsHitWall(cube, num_of_cube)) {
						
						bullet2.setShow(false);
					}
				}
			}
			else {
				evan.set_oppo_Color(0xFFFF9632);
			}


			if (bullet.getIsHit())
			{
				
				blood2.setAlpha(255);
				arrow2.setAlpha(255);
				arrow2.setDstRegion({ ALLREGION });
				arrow2.setSrcRegion({ ALLREGION });
				arrow2.setCenterAngle({ arrow2.getHeight() / 2, arrow2.getWidth() / 2 }, evan.getOppoAngle(ken.getPoint()));
				bullet.setIsHit(false);
			}
			blood2.draw(window.getRenderer(), { ALLREGION }, { ALLREGION });
			arrow2.draw();

			if (zip2.getShow()) {
				if (zip2.getZipLength() > ZIP_LENGTH ||
					(evan.IsZIP() && zip2.getpoint1() - evan < CUBE_RADIUS * 1.5) || zip2.timerExpired()) {
					zip2.setShow(false);
					evan.NotZip();
				}
				else {
					
					if (p2mode)
						zip2.draw(evan, window, 2);
					else
						zip2.draw(evan, window, 1);
					if (zip2.IsHitWall(cube, num_of_cube)) {
						
						evan.Zip(zip2.getpoint1());
					}

				}
			}

			delete[]cube;

			if (zip1.getShow()) {
				if(p2mode)
					zip1.draw(evan, window, 2);
				else
					zip1.draw(evan, window, 1);
			}

			gun2.setDstRegion({ ALLREGION });
			gun2.setSrcRegion({ ALLREGION });
			gun2.draw();
			fist2.draw(window.getRenderer(), { ALLREGION }, { ALLREGION });

			//map
			drawmap(window, evan, all_p);
			if (evan.getBlood()>0) {
				boxRGBA(window.getRenderer(), 30, HEIGHT - 60, evan.getBlood() * 3 + 30, HEIGHT - 20, 250, 0, 0, 250);
			}

			int em = evan.getmagazine();
			up3num.setString(number[em % 10]);
			up3num.generateTexture();
			em /= 10;
			up2num.setString(number[em % 10]);
			up2num.generateTexture();
			em /= 10;
			up1num.setString(number[em % 10]);
			up1num.generateTexture();
			em /= 10;

			int ebr = evan.getbullet_remain();
			down3num.setString(number[ebr % 10]);
			down3num.generateTexture();
			ebr /= 10;
			down2num.setString(number[ebr % 10]);
			down2num.generateTexture();
			ebr /= 10;
			down1num.setString(number[ebr % 10]);
			down1num.generateTexture();
			ebr /= 10;

			up1num.draw();
			up2num.draw();
			up3num.draw();
			down1num.draw();
			down2num.draw();
			down3num.draw();

			hp = evan.getBlood();
			hp3num.setString(number[hp % 10]);
			hp3num.generateTexture();
			hp /= 10;
			hp2num.setString(number[hp % 10]);
			hp2num.generateTexture();
			hp /= 10;
			hp1num.setString(number[hp % 10]);
			hp1num.generateTexture();
			hp /= 10;

			hp1num.draw();
			hp2num.draw();
			hp3num.draw();

			hp = evan.getrt();
			if (hp < 0)
				hp = 0;
			if (hp != 0) {
				boxRGBA(window.getRenderer(), 510, HEIGHT - evan.getrt() * 5, 590, HEIGHT, 250, 250, 250, 205);
				reloadtime3.setString(number[hp % 10]);
				reloadtime3.generateTexture();
				hp /= 10;
				reloadtime2.setString(".");// number[hp % 10]);
				reloadtime2.generateTexture();

				reloadtime1.setString(number[hp % 10]);
				reloadtime1.generateTexture();
				hp /= 10;

				reloadtime1.draw();
				reloadtime2.draw();
				reloadtime3.draw();
			}

			zct = zip2.ZipCount();
			if (zct >= 0)
				boxRGBA(window.getRenderer(), 30, HEIGHT - 100, 30 + (zct + 1) * 40, HEIGHT - 60, 0, 155, 255, 255);
			zipnum.setString(number[zct + 1]);
			zipnum.generateTexture();
			zipnum.draw();

			killdie.draw();
			killnumber.setString(number[evan.get_killnum()]);
			killnumber.generateTexture();
			dienumber.setString(number[evan.get_dienum()]);
			dienumber.generateTexture();
			killnumber.draw();
			dienumber.draw();

			thickLineColor(window.getRenderer(), 0, 0, 0, HEIGHT, 2, 0xFF000000);

			if (evan.get_killnum() == GOAL_KILLNUM || ken.get_killnum() == GOAL_KILLNUM) {

				
				boxRGBA(window.getRenderer(), 0, 0, 600, HEIGHT, 50, 50, 50, 150);
				if (evan.get_killnum() == GOAL_KILLNUM) {
					winlose.setString("WIN");
				}
				else {
					winlose.setString("LOSE");
				}

				winlose.generateTexture();
				winlose.draw();

				hint2.draw();

				endgame = true;

			}
		}

		// Update screen
		window.display();
	}


	for (int i = 0; i < max_num_of_cube + 1; i++) {
		delete[]all_p[i];
	}
	delete[]all_p;
	delete[]cube_const;

	//Free resources and close SDL
	ms.stopTimer();
	bullet.stopTimer();
	bullet2.stopTimer();
	ken.stopTimer();
	evan.stopTimer();

	background.close();
	blood.close();
	blood2.close();
	fist.close();
	fist2.close();
	arrow.close();
	arrow2.close();
	gun.close();
	gun2.close();


	//title.close();
	b3word.close();
	b1word.close();
	b2word.close();
	b4word.close();
	runspeed.close();
	jumpspeed.close();
	numofkill.close();
	maxviewupdown.close();
	hpnum.close();
	zipfullnum.close();
	numcube.close();

	setnum.close();
	cubenum1.close();
	cubenum2.close();

	up1num.close();
	up2num.close();
	up3num.close();
	down1num.close();
	down2num.close();
	down3num.close();

	hp1num.close();
	hp2num.close();
	hp3num.close();


	reloadtime1.close();
	reloadtime2.close();
	reloadtime3.close();
	reloadtime4.close();

	winlose.close();

	killdie.close();
	killnumber.close();
	dienumber.close();

	hint1.close();
	hint2.close();

	zipnum.close();

	window.close();
	sdl.close();

	return 0;
}


