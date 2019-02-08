#pragma once
#include <vector>
#include "Tile.h"
struct my_move {
	int from = 0;
	int to = 0;
	int score = 0;
};
struct leaf {
	int master = 0;
	int from = 0;
	int to = 0;
	int score = 0;
};
struct move_score {
	my_move move;
	int score = 0;
};
class AI
{
	
public:
	bool black = true;
	my_move Get_move(std::vector<Tile*> tiles);
	my_move Min_Max(std::vector<Tile*> tiles, int Search_death);
	std::vector<leaf> Gen_tree(std::vector<Tile*> tiles, int Search_death);
	
	std::vector<leaf> get_ranked_moves(std::vector<Tile*> tiles, bool team, int master);
	bool make_move(std::vector<Tile*> temp, int to, int selected);
	int get_board_value(std::vector<Tile*>, bool color);


	AI();
	~AI();
};

