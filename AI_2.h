#pragma once
#include <vector>
#include "Tile.h"
#include <algorithm>
#include <iostream>
struct my_move {
	int from = 0;
	int to = 0;
	int score = 0;
};
class AI_2
{
private:
	int Convert_xy_to_id3(int x, int y);
	bool On_Bored(int x, int y);
	int test_pre = 0;
public:
	bool black = true;
	
	my_move Get_move(std::vector<Tile*> tiles);
	int Min_Max(std::vector<Tile*> tiles, int depth, int max_depth, bool isMax);
	bool make_move(std::vector<Tile*> temp, int to, int selected);
	int get_board_value(std::vector<Tile*> tiles, bool color);
	AI_2();
	~AI_2();
};

