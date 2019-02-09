#pragma once
#include <vector>
#include "Tile.h"
#include <algorithm>
#include <iostream>
#include <thread>

struct my_move {
	int from = 0;
	int to = 0;
	int score = 0;
};
class AI_2
{
private:

	int test_pre = 0;
	int cut_peices = 0;
public:
	bool black = true;
	
	my_move Get_move(std::vector<Tile*> tiles);
	int Min_Max(std::vector<Tile*> tiles, int depth, int max_depth, bool isMax, int alpha, int beta);
	bool make_move(std::vector<Tile*> temp, int to, int selected);
	void sort_moves(std::vector<Tile*> temp, std::vector<Tile::pos>* moves);
	
	int get_move_aprox_value(std::vector<Tile*> temp, int to, int selected);
	int get_board_value(std::vector<Tile*> tiles, bool color);
	AI_2();
	~AI_2();
};

