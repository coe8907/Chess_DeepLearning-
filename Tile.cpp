#include "Tile.h"



Tile::Tile(int x, int y, int peice):Object("assets/chess.bmp",x*IMAGE_SCALE,y*IMAGE_SCALE, IMAGE_SCALE, IMAGE_SCALE,true)
{
	tile_x = x;
	tile_y = y;
	tile_peice = peice;
	has_moved = false;
}

void Tile::move(int x, int y)
{
	tile_x = x; tile_y = y;
	setx(x *IMAGE_SCALE);
	sety(y *IMAGE_SCALE);
	has_moved = true;
}


void Tile::Set_peice(int t_peice,bool t_color)
{
	tile_peice = t_peice;
	color = t_color;

	if (color) {
		setLoadRect(200 * tile_peice - 200, 0, 200, 200); 
	}
	else {
		setLoadRect(200 * tile_peice - 200, 200, 200, 200);
	}
}
std::vector <Tile::pos> Tile::get_moves(std::vector<Tile*>* tiles) {
	std::vector<pos> moves;
	pos temp;

	// pawn
	if (tile_peice == 1) { 
		if (BLACK_PEICE) { // color
			if (ON_BOARD(tile_x, tile_y +1)) {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y + 1))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x;
					temp.y = tile_y + 1;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}}
				}
			}
			if (ON_BOARD(tile_x, tile_y +2) && has_moved == false) {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y + 2))->tile_peice == 7 ) { // if the tile infront +1 is clear
					temp.x = tile_x;
					temp.y = tile_y + 2;
					
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					
				}
			}
			if (ON_BOARD(tile_x-1, tile_y +1)) {
				if (tile_x > 0) {
					if (!tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 1))->color && tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a color peice
						temp.x = tile_x - 1;
						temp.y = tile_y + 1;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					}
				}
			}
			if (ON_BOARD(tile_x+1, tile_y +1)) {
				if (tile_x < 7) {
					if (!tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 1))->color && tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a color peice
						temp.x = tile_x + 1;
						temp.y = tile_y + 1;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					}
				}
			}
		}
		else { // white pawn
			if (ON_BOARD(tile_x, tile_y - 1)) {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x;
					temp.y = tile_y - 1;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
				}
			}
			if (ON_BOARD(tile_x, tile_y - 2) && has_moved == false) {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - 2))->tile_peice == 7 && has_moved == false) { // if the tile infront -1 is clear
					temp.x = tile_x;
					temp.y = tile_y - 2;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
				}
			}
			if (tile_x > 0) {
				if (ON_BOARD(tile_x - 1, tile_y - 1)) {
					if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y - 1))->color && tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y - 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a color peice
						temp.x = tile_x - 1;
						temp.y = tile_y - 1;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					}
				}
			}
			if (tile_x < 7) {
				if (ON_BOARD(tile_x+1, tile_y -1)) {
					if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 1))->color && tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a color peice
						temp.x = tile_x + 1;
						temp.y = tile_y - 1;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					}
				}
			}
		}
	}

	//bisup 
	if (tile_peice == 2) {
		// up right 
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x + i, tile_y - i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y - i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y - i))->color != color) {
						temp.x = tile_x + i;
						temp.y = tile_y - i;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
						break;
					}
					break;
				}
			}
		}
		// down right
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x + i, tile_y + i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y + i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y + i))->color != color) {
						temp.x = tile_x + i;
						temp.y = tile_y + i;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
						break;
					}
					break;
				}
			}
		}
		// down left
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x - i, tile_y + i)) {
			if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x - i;
				temp.y = tile_y + i;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y + i))->color != color) {
					temp.x = tile_x - i;
					temp.y = tile_y + i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					break;
				}
				break;
			}
			}
		}
		// up left
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x - i, tile_y - i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y - i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y - i))->color != color) {
						temp.x = tile_x - i;
						temp.y = tile_y - i;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
						break;
					}
					break;
				}
			}
		}
	}
	
	//queen
	if (tile_peice == 3) {
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x + i, tile_y - i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y - i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y - i))->color != color) {
						temp.x = tile_x + i;
						temp.y = tile_y - i;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
						break;
					}
					break;
				}
			}
		}
		// down right
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x + i, tile_y + i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y + i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y + i))->color != color) {
						temp.x = tile_x + i;
						temp.y = tile_y + i;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
						break;
					}
					break;
				}
			}
		}
		// down left
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x - i, tile_y + i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y + i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y + i))->color != color) {
						temp.x = tile_x - i;
						temp.y = tile_y + i;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
						break;
					}
					break;
				}
			}
		}
		// up left
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x - i, tile_y - i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y - i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y - i))->color != color) {
						temp.x = tile_x - i;
						temp.y = tile_y - i;
						if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
						break;
					}
					break;
				}
			}
		}
		//up
		for (int i = tile_y + 1; i < 8; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x, i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = i;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x, i))->color != color) {
					temp.x = tile_x;
					temp.y = i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					break;
				}
				break;
			}
		}
		// down
		for (int i = 1; i < tile_y + 1; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = tile_y - i;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - i))->color != color) {
					temp.x = tile_x;
					temp.y = tile_y - i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					break;
				}
				break;
			}
		}
		// right
		for (int i = tile_x + 1; i < 8; i++) {
			if (tiles->at(CONVERT_TO_ID(i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = i;
				temp.y = tile_y;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
			else {
				if (tiles->at(CONVERT_TO_ID(i, tile_y))->color != color) {
					temp.x = i;
					temp.y = tile_y;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					break;
				}
				break;
			}
		}
		// left
		for (int i = 1; i < tile_x + 1; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x - i;
				temp.y = tile_y;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y))->color != color) {
					temp.x = tile_x - i;
					temp.y = tile_y;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					break;
				}
				break;
			}
		}
	}
	
	//king 
	if (tile_peice == 4) {
		if (tile_x > 0) {
			if (tiles->at(CONVERT_TO_ID(tile_x-1, tile_y))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x-1;
				temp.y = tile_y;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		if (tile_x < 7) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		if (tile_y > 0) {
			if (tiles->at(CONVERT_TO_ID(tile_x, tile_y-1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x;
				temp.y = tile_y-1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		if (tile_y < 7) {
			if (tiles->at(CONVERT_TO_ID(tile_x, tile_y+1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x;
				temp.y = tile_y+1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		if (tile_y < 7 && tile_x < 7) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y + 1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		if (tile_y > 0 && tile_x < 7) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y - 1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		if (tile_y < 7 && tile_x >0) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y + 1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		if (tile_y >0 && tile_x >0) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y -1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y - 1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		
	}
	
	//knight
	if (tile_peice == 5) {
		//TODO
		// +3 +1 
		if (ON_BOARD(tile_x + 2, tile_y + 1)) {
			if (tiles->at(CONVERT_TO_ID(tile_x +2, tile_y + 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x + 2, tile_y + 1))->tile_peice == 7) {
				temp.x = tile_x + 2;
				temp.y = tile_y + 1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		// +3 -1
		if (ON_BOARD(tile_x + 2, tile_y - 1)) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 2, tile_y - 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x + 2, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 2;
				temp.y = tile_y - 1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		// -3 +1
		if (ON_BOARD(tile_x - 2, tile_y + 1)) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 2, tile_y + 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x - 2, tile_y + 1))->tile_peice == 7) {
				temp.x = tile_x - 2;
				temp.y = tile_y + 1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		// -3 -1
		if (ON_BOARD(tile_x - 2, tile_y - 1)) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 2, tile_y - 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x - 2, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x - 2;
				temp.y = tile_y - 1;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		// +1 -3
		if (ON_BOARD(tile_x + 1, tile_y - 2)) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 2))->color != color || tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 2))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y - 2;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		// +1 +3
		if (ON_BOARD(tile_x + 1, tile_y + 2)) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 2))->color != color || tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 2))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y + 2;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		// -1 -3
		if (ON_BOARD(tile_x - 1, tile_y - 2)) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y - 2))->color != color || tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y - 2))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y - 2;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}
		// -1 +3
		if (ON_BOARD(tile_x - 1, tile_y + 2)) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 2))->color != color || tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 2))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y + 2;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
		}

	}

	// casle 
	if (tile_peice == 6) {
		//up
		for (int i = tile_y+1; i < 8; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x, i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = i;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x, i))->color != color) {
					temp.x = tile_x;
					temp.y = i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					break;
				}
				break;
			}
		}
		// down
		for (int i = 1; i < tile_y+1; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = tile_y - i;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - i))->color != color) {
					temp.x = tile_x;
					temp.y = tile_y - i;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					break;
				}
				break;
			}
		}
		// right
		for (int i = tile_x+1; i < 8; i++) {
			if (tiles->at(CONVERT_TO_ID(i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = i;
				temp.y = tile_y;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
			else {
				if (tiles->at(CONVERT_TO_ID(i, tile_y))->color != color) {
					temp.x = i;
					temp.y = tile_y;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					break;
				}
				break;
			}
		}
		// left
		for (int i = 1; i < tile_x+1; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x - i;
				temp.y = tile_y;
				if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y))->color != color) {
					temp.x = tile_x - i;
					temp.y = tile_y;
					if (can_king_be_taken(tiles, temp.x, temp.y)) {moves.push_back(temp);}
					break;
				}
				break;
			}
		}
	}

	return moves;
}

std::vector <Tile::pos> Tile::get_moves_no_checking(std::vector<Tile*>* tiles) {
	std::vector<pos> moves;
	pos temp;

	// pawn
	if (tile_peice == 1) {
		if (BLACK_PEICE) { // color
			if (ON_BOARD(tile_x, tile_y + 1)) {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y + 1))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x;
					temp.y = tile_y + 1;
					moves.push_back(temp);
				}
			}
			if (ON_BOARD(tile_x, tile_y + 2) && has_moved == false) {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y + 2))->tile_peice == 7) { // if the tile infront +1 is clear
					temp.x = tile_x;
					temp.y = tile_y + 2;

					moves.push_back(temp);

				}
			}
			if (ON_BOARD(tile_x - 1, tile_y + 1)) {
				if (tile_x > 0) {
					if (!tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 1))->color && tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a color peice
						temp.x = tile_x - 1;
						temp.y = tile_y + 1;
						moves.push_back(temp);
					}
				}
			}
			if (ON_BOARD(tile_x + 1, tile_y + 1)) {
				if (tile_x < 7) {
					if (!tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 1))->color && tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a color peice
						temp.x = tile_x + 1;
						temp.y = tile_y + 1;
						moves.push_back(temp);
					}
				}
			}
		}
		else { // white pawn
			if (ON_BOARD(tile_x, tile_y - 1)) {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x;
					temp.y = tile_y - 1;
					moves.push_back(temp);
				}
			}
			if (ON_BOARD(tile_x, tile_y - 2) && has_moved == false) {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - 2))->tile_peice == 7 && has_moved == false) { // if the tile infront -1 is clear
					temp.x = tile_x;
					temp.y = tile_y - 2;
					moves.push_back(temp);
				}
			}
			if (tile_x > 0) {
				if (ON_BOARD(tile_x - 1, tile_y - 1)) {
					if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y - 1))->color && tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y - 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a color peice
						temp.x = tile_x - 1;
						temp.y = tile_y - 1;
						moves.push_back(temp);
					}
				}
			}
			if (tile_x < 7) {
				if (ON_BOARD(tile_x + 1, tile_y - 1)) {
					if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 1))->color && tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a color peice
						temp.x = tile_x + 1;
						temp.y = tile_y - 1;
						moves.push_back(temp);
					}
				}
			}
		}
	}

	//bisup 
	if (tile_peice == 2) {
		// up right 
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x + i, tile_y - i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y - i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y - i))->color != color) {
						temp.x = tile_x + i;
						temp.y = tile_y - i;
						moves.push_back(temp);
						break;
					}
					break;
				}
			}
		}
		// down right
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x + i, tile_y + i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y + i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y + i))->color != color) {
						temp.x = tile_x + i;
						temp.y = tile_y + i;
						moves.push_back(temp);
						break;
					}
					break;
				}
			}
		}
		// down left
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x - i, tile_y + i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y + i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y + i))->color != color) {
						temp.x = tile_x - i;
						temp.y = tile_y + i;
						moves.push_back(temp);
						break;
					}
					break;
				}
			}
		}
		// up left
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x - i, tile_y - i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y - i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y - i))->color != color) {
						temp.x = tile_x - i;
						temp.y = tile_y - i;
						moves.push_back(temp);
						break;
					}
					break;
				}
			}
		}
	}

	//queen
	if (tile_peice == 3) {
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x + i, tile_y - i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y - i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y - i))->color != color) {
						temp.x = tile_x + i;
						temp.y = tile_y - i;
						moves.push_back(temp);
						break;
					}
					break;
				}
			}
		}
		// down right
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x + i, tile_y + i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y + i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x + i, tile_y + i))->color != color) {
						temp.x = tile_x + i;
						temp.y = tile_y + i;
						moves.push_back(temp);
						break;
					}
					break;
				}
			}
		}
		// down left
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x - i, tile_y + i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y + i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y + i))->color != color) {
						temp.x = tile_x - i;
						temp.y = tile_y + i;
						moves.push_back(temp);
						break;
					}
					break;
				}
			}
		}
		// up left
		for (int i = 1; i < 8; i++) {
			if (ON_BOARD(tile_x - i, tile_y - i)) {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y - i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y - i))->color != color) {
						temp.x = tile_x - i;
						temp.y = tile_y - i;
						moves.push_back(temp);
						break;
					}
					break;
				}
			}
		}
		//up
		for (int i = tile_y + 1; i < 8; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x, i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = i;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x, i))->color != color) {
					temp.x = tile_x;
					temp.y = i;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
		// down
		for (int i = 1; i < tile_y + 1; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = tile_y - i;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - i))->color != color) {
					temp.x = tile_x;
					temp.y = tile_y - i;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
		// right
		for (int i = tile_x + 1; i < 8; i++) {
			if (tiles->at(CONVERT_TO_ID(i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = i;
				temp.y = tile_y;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(CONVERT_TO_ID(i, tile_y))->color != color) {
					temp.x = i;
					temp.y = tile_y;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
		// left
		for (int i = 1; i < tile_x + 1; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x - i;
				temp.y = tile_y;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y))->color != color) {
					temp.x = tile_x - i;
					temp.y = tile_y;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
	}

	//king 
	if (tile_peice == 4) {
		if (tile_x > 0) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y;
				moves.push_back(temp);
			}
		}
		if (tile_x < 7) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y;
				moves.push_back(temp);
			}
		}
		if (tile_y > 0) {
			if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x;
				temp.y = tile_y - 1;
				moves.push_back(temp);
			}
		}
		if (tile_y < 7) {
			if (tiles->at(CONVERT_TO_ID(tile_x, tile_y + 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x;
				temp.y = tile_y + 1;
				moves.push_back(temp);
			}
		}
		if (tile_y < 7 && tile_x < 7) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y + 1;
				moves.push_back(temp);
			}
		}
		if (tile_y > 0 && tile_x < 7) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y - 1;
				moves.push_back(temp);
			}
		}
		if (tile_y < 7 && tile_x >0) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y + 1;
				moves.push_back(temp);
			}
		}
		if (tile_y > 0 && tile_x > 0) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y - 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y - 1;
				moves.push_back(temp);
			}
		}

	}

	//knight
	if (tile_peice == 5) {
		//TODO
		// +3 +1 
		if (ON_BOARD(tile_x + 2, tile_y + 1)) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 2, tile_y + 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x + 2, tile_y + 1))->tile_peice == 7) {
				temp.x = tile_x + 2;
				temp.y = tile_y + 1;
				moves.push_back(temp);
			}
		}
		// +3 -1
		if (ON_BOARD(tile_x + 2, tile_y - 1)) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 2, tile_y - 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x + 2, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 2;
				temp.y = tile_y - 1;
				moves.push_back(temp);
			}
		}
		// -3 +1
		if (ON_BOARD(tile_x - 2, tile_y + 1)) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 2, tile_y + 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x - 2, tile_y + 1))->tile_peice == 7) {
				temp.x = tile_x - 2;
				temp.y = tile_y + 1;
				moves.push_back(temp);
			}
		}
		// -3 -1
		if (ON_BOARD(tile_x - 2, tile_y - 1)) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 2, tile_y - 1))->color != color || tiles->at(CONVERT_TO_ID(tile_x - 2, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x - 2;
				temp.y = tile_y - 1;
				moves.push_back(temp);
			}
		}
		// +1 -3
		if (ON_BOARD(tile_x + 1, tile_y - 2)) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 2))->color != color || tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y - 2))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y - 2;
				moves.push_back(temp);
			}
		}
		// +1 +3
		if (ON_BOARD(tile_x + 1, tile_y + 2)) {
			if (tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 2))->color != color || tiles->at(CONVERT_TO_ID(tile_x + 1, tile_y + 2))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y + 2;
				moves.push_back(temp);
			}
		}
		// -1 -3
		if (ON_BOARD(tile_x - 1, tile_y - 2)) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y - 2))->color != color || tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y - 2))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y - 2;
				moves.push_back(temp);
			}
		}
		// -1 +3
		if (ON_BOARD(tile_x - 1, tile_y + 2)) {
			if (tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 2))->color != color || tiles->at(CONVERT_TO_ID(tile_x - 1, tile_y + 2))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y + 2;
				moves.push_back(temp);
			}
		}

	}

	// casle 
	if (tile_peice == 6) {
		//up
		for (int i = tile_y + 1; i < 8; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x, i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = i;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x, i))->color != color) {
					temp.x = tile_x;
					temp.y = i;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
		// down
		for (int i = 1; i < tile_y + 1; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = tile_y - i;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x, tile_y - i))->color != color) {
					temp.x = tile_x;
					temp.y = tile_y - i;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
		// right
		for (int i = tile_x + 1; i < 8; i++) {
			if (tiles->at(CONVERT_TO_ID(i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = i;
				temp.y = tile_y;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(CONVERT_TO_ID(i, tile_y))->color != color) {
					temp.x = i;
					temp.y = tile_y;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
		// left
		for (int i = 1; i < tile_x + 1; i++) {
			if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x - i;
				temp.y = tile_y;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(CONVERT_TO_ID(tile_x - i, tile_y))->color != color) {
					temp.x = tile_x - i;
					temp.y = tile_y;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
	}

	return moves;
}

// returns false if this peices king could betaken if the move was taken
bool Tile::can_king_be_taken(std::vector <Tile*>* tiles,int move_x,int move_y) {
	Tile * my_king = nullptr;
	
	Tile * old_moved_to = tiles->at(CONVERT_TO_ID(move_x,move_y));
	int old_x = tile_x;
	int old_y = tile_y;
	Tile * blank = new Tile(old_x, old_y,DEFALT_ID);
	tiles->at(CONVERT_TO_ID(move_x, move_y)) = tiles->at(CONVERT_TO_ID(tile_x, tile_y));
	tiles->at(CONVERT_TO_ID(old_x, old_y)) = blank;
	


	for (int i = 0; i < tiles->size(); i++) {
		if (tiles->at(i)->get_color() == color) { // if they are the same color
			if (tiles->at(i)->get_tile_peice() == KING_ID) {
				my_king = tiles->at(i);
				break;
			}
		}
	}
	if(my_king != nullptr){
		for (int i = 0; i < tiles->size(); i++) {
			if(tiles->at(i)->get_color() != color){
			std::vector<pos> moves = tiles->at(i)->get_moves_no_checking(tiles);
			for (int move = 0; move < moves.size(); move++) {
				if (moves.at(move).x == my_king->get_tile_x()) {
					if (moves.at(move).y == my_king->get_tile_y()) {
						tiles->at(CONVERT_TO_ID(old_x, old_y)) = tiles->at(CONVERT_TO_ID(move_x, move_y));
						tiles->at(CONVERT_TO_ID(move_x, move_y)) = old_moved_to;
						delete blank;
						return false;
					}
				}
				}
			}
		}
	}
	tiles->at(CONVERT_TO_ID(old_x, old_y)) = tiles->at(CONVERT_TO_ID(move_x, move_y));
	tiles->at(CONVERT_TO_ID(move_x, move_y)) = old_moved_to;
	delete blank;
	return true;
}

Tile::~Tile()
{
}
