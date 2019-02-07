#pragma once
#include "Object.h"
#include <vector>
#define Size = 200;
#define black_y = 0;
#define white_y = 200;

#define Pawn_x = 0;
#define Biso_x = 200;
#define Queen_x = 400;
#define King_x = 600;
#define Knight_x = 800;
#define Rook_x = 1000;


class Tile :
	public Object
{
private:
	int tile_x = 0;
	int tile_y = 0;
	int tile_peice = 0;
	bool black = false;
	bool  has_moved = true;
public:	

	struct pos {
	int x;
	int y;
	};

	int Convert_xy_to_id(int x, int y);
	
	void Set_peice(int new_peice, bool back);
	void move(int x, int y);
	
	std::vector<pos> get_moves(std::vector<Tile*>* floor);
	
	bool Can_take_king(std::vector<Tile*>* tiles);
	bool On_Bored(int x, int y);
	
	int get_tile_peice() { return tile_peice; }
	int get_tile_x() { return tile_x; }
	int get_tile_y() { return tile_y; }
	bool get_color() { return black; }
	int Get_peice() { return tile_peice; }


	Tile(int x,int y,int peice);
	~Tile();
};

