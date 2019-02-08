#pragma once
#include <string>
#include "include\SDL.h"
#include <map>
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;


class bitmaps
{
private:
	
	
    SDL_Rect Load_from_pos;
	bool has_load_pos = false;

protected:
	SDL_Surface* m_pbs;
	SDL_Texture* m_pbt;
	SDL_Renderer*  m_pr;
	struct positions {
		int m_x = 0;
		int m_y = 0;
		int m_w = 0;
		int m_h = 0;
	};
	positions pos;
public:
	bitmaps();
	bitmaps(std::string fileName, int xpos, int ypos,bool usesTrans);
	bitmaps(std::string filename, int xpos, int ypos, int width, int height, bool usingtrans);
	bitmaps(std::string filename, int xpos, int ypos, int width, int height, bool usingtrans,int numberofframes);
	bitmaps(std::string filename, int xpos, int ypos, int width, int height, bool usingtrans,int numberofframes,int numberoflayer);
	bitmaps(std::string filename, int xpos, int ypos, int width, int height);
	void setLoadRect(int start_x,int start_y,int end_x,int end_y);
	void clearLoadRect();
	int getx();
	int gety();
	void setx(int);
	void sety(int);
	SDL_Surface* getsurface();
	

	~bitmaps();
	void draw();
};

