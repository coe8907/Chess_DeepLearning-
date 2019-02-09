#pragma once
#include "Object.h"
#include <vector>
#include "Consts.h"


class Tile :
	public Object
{
private:

	int tile_x = 0;
	int tile_y = 0;
	int tile_peice = 7;
	bool color = false;
	bool has_moved = true;
public:	

	struct pos {
	int x;
	int y;
	};

	void set_moved(bool moved) { has_moved = moved; }
	void Set_peice(int new_peice, bool color);
	void move(int x, int y);
	
	std::vector<pos> get_moves(std::vector<Tile*>* tiles);

	std::vector<Tile::pos> get_moves_no_checking(std::vector<Tile*>* tiles);

	bool can_king_be_taken(std::vector<Tile*>* tiles, int move_x, int move_y);

	
	int get_tile_peice() { return tile_peice; }
	int get_tile_x() { return tile_x; }
	int get_tile_y() { return tile_y; }
	bool get_color() { return color; }
	
	int get_value() { 
		if (tile_peice == 1)return 1;
		if (tile_peice == 2)return 3;
		if (tile_peice == 5)return 3;
		if (tile_peice == 3)return 9;
		if (tile_peice == 6)return 5;
		if (tile_peice == 4)return 3;
		return 0;
	}

	Tile(int x,int y,int peice);
	~Tile();
};

