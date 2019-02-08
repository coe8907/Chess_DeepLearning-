#pragma once
#include "include\SDL.h"
#include <map>
#include "Input.h"
#include "Object.h"
#include "Tile.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "AI_2.h"
class Game
{
private:
	SDL_Window* m_Window;
	std::vector<Tile*> tiles;
	std::vector<Tile*> floor;
	Input input;
	int move = 0;
	bool black_in_check = false;
	bool white_in_check = false;
	AI_2 temp_ai;
public:
	Game();
	~Game();
	void set_bored();
	void update();

	bool AI_move(AI_2 * ai);

	bool make_move(int from, int to);

	bool make_move(int to);

	void make_move();
	
	void paint();
	static SDL_Renderer* m_Renderer;
	static std::map<std::string, SDL_Texture*>  textures;
};

