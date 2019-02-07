#include <string>
#include "bitmaps.h"
#include "Game.h"
#include "include/SDL.h"
#include "include/SDL_render.h"
bool fixedSize = false;

bitmaps::bitmaps() {

}
bitmaps::bitmaps(std::string filename, int xpos, int ypos, bool usingtrans)
{
	m_pr = Game::m_Renderer;
	m_pbs = SDL_LoadBMP(filename.c_str());
	if (!m_pbs) {
		printf("oh well fuck a duck, sdl failed to load bmp surface");
	}
	else {
		if (usingtrans) {
			Uint32 colourKey = SDL_MapRGB(m_pbs->format, 255, 0, 255);
			SDL_SetColorKey(m_pbs, SDL_TRUE, colourKey);
		}
		m_pbt = SDL_CreateTextureFromSurface(m_pr, m_pbs);
		if (!m_pbt) {
			printf("oh well fuck a duck, sdl failed to load bmp texture");
		}
	}
	pos.m_x = xpos;
	pos.m_y = ypos;
	printf("bitmaps loaded");
}
bitmaps::bitmaps(std::string filename, int xpos, int ypos,int width,int height, bool usingtrans)
{
	
	m_pr = Game::m_Renderer;
	m_pbs = SDL_LoadBMP(filename.c_str());
	if (!m_pbs) {
		printf("oh well fuck a duck, sdl failed to load bmp surface");
	}
	else {
		if (usingtrans) {
			Uint32 colourKey = SDL_MapRGB(m_pbs->format, 255, 0, 255);
			SDL_SetColorKey(m_pbs, SDL_TRUE, colourKey);
		}
		m_pbt = SDL_CreateTextureFromSurface(m_pr, m_pbs);
		if (!m_pbt) {
			printf("oh well fuck a duck, sdl failed to load bmp texture");
		}
	}
	pos.m_x = xpos;
	pos.m_y = ypos;
	
	pos.m_h = height;
	pos.m_w = width;
	fixedSize = true;
}
bitmaps::bitmaps(std::string filename, int xpos, int ypos, int width, int height, bool usingtrans, int numberofframes)
{
	m_pr = Game::m_Renderer;
	m_pbs = SDL_LoadBMP(filename.c_str());
	if (!m_pbs) {
		printf("oh well fuck a duck, sdl failed to load bmp surface");
	}
	else {
		if (usingtrans) {
			Uint32 colourKey = SDL_MapRGB(m_pbs->format, 255, 0, 255);
			SDL_SetColorKey(m_pbs, SDL_TRUE, colourKey);
		}
		m_pbt = SDL_CreateTextureFromSurface(m_pr, m_pbs);
		if (!m_pbt) {
			printf("oh well fuck a duck, sdl failed to load bmp texture");
		}
	}
	pos.m_x = xpos;
	pos.m_y = ypos;

	pos.m_h = height;
	pos.m_w = width;
	fixedSize = true;
}
bitmaps::bitmaps(std::string filename, int xpos, int ypos, int width, int height, bool usingtrans, int numberofframes, int numberoflayer)
{
	m_pr = Game::m_Renderer;
	m_pbs = SDL_LoadBMP(filename.c_str());
	if (!m_pbs) {
		printf("oh well fuck a duck, sdl failed to load bmp surface");
	}
	else {
		if (usingtrans) {
			Uint32 colourKey = SDL_MapRGB(m_pbs->format, 255, 0, 255);
			SDL_SetColorKey(m_pbs, SDL_TRUE, colourKey);
		}
		m_pbt = SDL_CreateTextureFromSurface(m_pr, m_pbs);
		if (!m_pbt) {
			printf("oh well fuck a duck, sdl failed to load bmp texture");
		}
	}
	pos.m_x = xpos;
	pos.m_y = ypos;

	pos.m_h = height;
	pos.m_w = width;
	fixedSize = true;
}
bitmaps::bitmaps(std::string filename, int xpos, int ypos, int width, int height)
{
	m_pr = Game::m_Renderer;
	m_pbs = SDL_LoadBMP(filename.c_str());
	if (!m_pbs) {
		printf("oh well fuck a duck, sdl failed to load bmp surface");
	}
	else {
		m_pbt = SDL_CreateTextureFromSurface(m_pr, m_pbs);
		if (!m_pbt) {
			printf("oh well fuck a duck, sdl failed to load bmp texture");
		}
	}
	pos.m_x = xpos;
	pos.m_y = ypos;

	pos.m_h = height;
	pos.m_w = width;
	fixedSize = true;
}
void bitmaps::setLoadRect(int start_x, int start_y, int width, int height) {
	Load_from_pos.x = start_x;
	Load_from_pos.y = start_y;
	Load_from_pos.w = width;
	Load_from_pos.h = height;
	has_load_pos = true;
}
void bitmaps::clearLoadRect() {
	has_load_pos = false;
}

int bitmaps::getx()
{
	return 0;
}

int bitmaps::gety()
{
	return 0;
}

void bitmaps::draw() {
	if (m_pbt) {
		SDL_Rect destRect;
		if (fixedSize) {
			destRect = { pos.m_x,pos.m_y,pos.m_w,pos.m_h };
		}
		else {

			destRect = { pos.m_x,pos.m_y,m_pbs->w,m_pbs->h };
		}
		if (has_load_pos) {
			SDL_RenderCopy(m_pr, m_pbt, &Load_from_pos, &destRect);
		}
		else {
			SDL_RenderCopy(m_pr, m_pbt, NULL, &destRect);
		}
	}
}
void bitmaps::setx(int newposx) {
	pos.m_x = newposx;
}
void bitmaps::sety(int newposy) {
	pos.m_y = newposy;
}

SDL_Surface* bitmaps::getsurface()
{
	return m_pbs;
}



bitmaps::~bitmaps(){
	if (m_pbt) {
		SDL_DestroyTexture(m_pbt);
	}
	if (m_pbs) {
		SDL_FreeSurface(m_pbs);
	}
}
