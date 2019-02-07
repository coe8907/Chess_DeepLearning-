#pragma once
#include "include\SDL.h"
#include "Input.h"
#include "Object.h"
#include "Tile.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include "AI.h"
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
	AI temp_ai;
public:
	Game();
	~Game();
	void set_bored();
	void update();

	bool AI_move(AI * ai);

	bool make_move(int from, int to);

	bool make_move(int to);

	void make_move();
	
	void paint();
	static SDL_Renderer* m_Renderer;
};

