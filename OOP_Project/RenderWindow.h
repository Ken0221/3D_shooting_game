#pragma once
#include <SDL.h> // Using SDL
#include <vector>//using two window

using namespace std;

class RenderWindow
{
public:
	RenderWindow(const char* caption, int winx, int winy, int width, int height);
	void close();
	void clear();
	void clear(Uint32 color);
	void display();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	void addVpregion(vector<SDL_Rect> r);
	void setVP(int n);
	int getVPnum();
	SDL_Rect* getRegion(int n);
	void clearVP();
	void clearVP(Uint32 color);
	void clearVP(Uint32 color, int n);
	

private:
	SDL_Window* window; // The window we'll be rendering to
	SDL_Renderer* renderer; // The renderer contained by the window
	vector<SDL_Rect> region;
};

