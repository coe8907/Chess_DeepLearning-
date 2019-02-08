#include "Tile.h"



Tile::Tile(int x, int y, int peice):Object("assets/chess.bmp",x*40,y*40,40,40,true)
{
	tile_x = x;
	tile_y = y;
	tile_peice = peice;
	has_moved = true;
}

void Tile::move(int x, int y)
{
	tile_x = x; tile_y = y;
	setx(x * 40);
	sety(y * 40);
}

int Tile::Convert_xy_to_id(int x, int y) {
	if (On_Bored(x, y)) {
		return x * 8 + y;
	}
	else {
		return 0;
	}
}

void Tile::Set_peice(int new_peice,bool new_black)
{
	has_moved = false;
	tile_peice = new_peice;
	black = new_black;

	if (black) {
		setLoadRect(200 * new_peice - 200, 0, 200, 200); // pawn
	}
	else {
		setLoadRect(200 * new_peice - 200, 200, 200, 200);
	}
}
std::vector <Tile::pos> Tile::get_moves(std::vector<Tile*>* tiles) {
	std::vector<pos> moves;
	pos temp;

	// pawn
	if (tile_peice == 1) { 
		if (black) { // black
			if (On_Bored(tile_x, tile_y +1)) {
				if (tiles->at(Convert_xy_to_id(tile_x, tile_y + 1))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x;
					temp.y = tile_y + 1;
					moves.push_back(temp);
				}
			}
			if (On_Bored(tile_x, tile_y +2)) {
				if (tiles->at(Convert_xy_to_id(tile_x, tile_y + 2))->tile_peice == 7 && !has_moved) { // if the tile infront +1 is clear
					temp.x = tile_x;
					temp.y = tile_y + 2;
					moves.push_back(temp);
				}
			}
			if (On_Bored(tile_x-1, tile_y +1)) {
				if (tile_x > 0) {
					if (!tiles->at(Convert_xy_to_id(tile_x - 1, tile_y + 1))->black && tiles->at(Convert_xy_to_id(tile_x - 1, tile_y + 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a black peice
						temp.x = tile_x - 1;
						temp.y = tile_y + 1;
						moves.push_back(temp);
					}
				}
			}
			if (On_Bored(tile_x+1, tile_y +1)) {
				if (tile_x < 7) {
					if (!tiles->at(Convert_xy_to_id(tile_x + 1, tile_y + 1))->black && tiles->at(Convert_xy_to_id(tile_x + 1, tile_y + 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a black peice
						temp.x = tile_x + 1;
						temp.y = tile_y + 1;
						moves.push_back(temp);
					}
				}
			}
		}
		else { // white pawn
			if (On_Bored(tile_x, tile_y - 1)) {
				if (tiles->at(Convert_xy_to_id(tile_x, tile_y - 1))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x;
					temp.y = tile_y - 1;
					moves.push_back(temp);
				}
			}
			if (On_Bored(tile_x, tile_y - 2)) {
				if (tiles->at(Convert_xy_to_id(tile_x, tile_y - 2))->tile_peice == 7 && !has_moved) { // if the tile infront -1 is clear
					temp.x = tile_x;
					temp.y = tile_y - 2;
					moves.push_back(temp);
				}
			}
			if (tile_x > 0) {
				if (On_Bored(tile_x - 1, tile_y - 1)) {
					if (tiles->at(Convert_xy_to_id(tile_x - 1, tile_y - 1))->black && tiles->at(Convert_xy_to_id(tile_x - 1, tile_y - 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a black peice
						temp.x = tile_x - 1;
						temp.y = tile_y - 1;
						moves.push_back(temp);
					}
				}
			}
			if (tile_x < 7) {
				if (On_Bored(tile_x+1, tile_y -1)) {
					if (tiles->at(Convert_xy_to_id(tile_x + 1, tile_y - 1))->black && tiles->at(Convert_xy_to_id(tile_x + 1, tile_y - 1))->tile_peice != 7) { // if the tile infront and left is not clear && is not a black peice
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
			if (On_Bored(tile_x + i, tile_y - i)) {
				if (tiles->at(Convert_xy_to_id(tile_x + i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y - i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(Convert_xy_to_id(tile_x + i, tile_y - i))->black != black) {
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
			if (On_Bored(tile_x + i, tile_y + i)) {
				if (tiles->at(Convert_xy_to_id(tile_x + i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y + i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(Convert_xy_to_id(tile_x + i, tile_y + i))->black != black) {
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
			if (On_Bored(tile_x - i, tile_y + i)) {
			if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x - i;
				temp.y = tile_y + i;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y + i))->black != black) {
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
			if (On_Bored(tile_x - i, tile_y - i)) {
				if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y - i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y - i))->black != black) {
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
			if (On_Bored(tile_x + i, tile_y - i)) {
				if (tiles->at(Convert_xy_to_id(tile_x + i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y - i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(Convert_xy_to_id(tile_x + i, tile_y - i))->black != black) {
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
			if (On_Bored(tile_x + i, tile_y + i)) {
				if (tiles->at(Convert_xy_to_id(tile_x + i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x + i;
					temp.y = tile_y + i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(Convert_xy_to_id(tile_x + i, tile_y + i))->black != black) {
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
			if (On_Bored(tile_x - i, tile_y + i)) {
				if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y + i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y + i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y + i))->black != black) {
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
			if (On_Bored(tile_x - i, tile_y - i)) {
				if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
					temp.x = tile_x - i;
					temp.y = tile_y - i;
					moves.push_back(temp);
				}
				else {
					if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y - i))->black != black) {
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
			if (tiles->at(Convert_xy_to_id(tile_x, i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = i;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(Convert_xy_to_id(tile_x, i))->black != black) {
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
			if (tiles->at(Convert_xy_to_id(tile_x, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = tile_y - i;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(Convert_xy_to_id(tile_x, tile_y - i))->black != black) {
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
			if (tiles->at(Convert_xy_to_id(i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = i;
				temp.y = tile_y;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(Convert_xy_to_id(i, tile_y))->black != black) {
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
			if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x - i;
				temp.y = tile_y;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y))->black != black) {
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
			if (tiles->at(Convert_xy_to_id(tile_x-1, tile_y))->black != black || tiles->at(Convert_xy_to_id(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x-1;
				temp.y = tile_y;
				moves.push_back(temp);
			}
		}
		if (tile_x < 7) {
			if (tiles->at(Convert_xy_to_id(tile_x + 1, tile_y))->black != black || tiles->at(Convert_xy_to_id(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y;
				moves.push_back(temp);
			}
		}
		if (tile_y > 0) {
			if (tiles->at(Convert_xy_to_id(tile_x, tile_y-1))->black != black || tiles->at(Convert_xy_to_id(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x;
				temp.y = tile_y-1;
				moves.push_back(temp);
			}
		}
		if (tile_y < 7) {
			if (tiles->at(Convert_xy_to_id(tile_x, tile_y+1))->black != black || tiles->at(Convert_xy_to_id(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x;
				temp.y = tile_y+1;
				moves.push_back(temp);
			}
		}
		if (tile_y < 7 && tile_x < 7) {
			if (tiles->at(Convert_xy_to_id(tile_x + 1, tile_y + 1))->black != black || tiles->at(Convert_xy_to_id(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y + 1;
				moves.push_back(temp);
			}
		}
		if (tile_y > 0 && tile_x < 7) {
			if (tiles->at(Convert_xy_to_id(tile_x + 1, tile_y - 1))->black != black || tiles->at(Convert_xy_to_id(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y - 1;
				moves.push_back(temp);
			}
		}
		if (tile_y < 7 && tile_x >0) {
			if (tiles->at(Convert_xy_to_id(tile_x - 1, tile_y + 1))->black != black || tiles->at(Convert_xy_to_id(tile_x, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y + 1;
				moves.push_back(temp);
			}
		}
		if (tile_y >0 && tile_x >0) {
			if (tiles->at(Convert_xy_to_id(tile_x - 1, tile_y -1))->black != black || tiles->at(Convert_xy_to_id(tile_x, tile_y - 1))->tile_peice == 7) {
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
		if (On_Bored(tile_x + 2, tile_y + 1)) {
			if (tiles->at(Convert_xy_to_id(tile_x +2, tile_y + 1))->black != black || tiles->at(Convert_xy_to_id(tile_x + 2, tile_y + 1))->tile_peice == 7) {
				temp.x = tile_x + 2;
				temp.y = tile_y + 1;
				moves.push_back(temp);
			}
		}
		// +3 -1
		if (On_Bored(tile_x + 2, tile_y - 1)) {
			if (tiles->at(Convert_xy_to_id(tile_x + 2, tile_y - 1))->black != black || tiles->at(Convert_xy_to_id(tile_x + 2, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x + 2;
				temp.y = tile_y - 1;
				moves.push_back(temp);
			}
		}
		// -3 +1
		if (On_Bored(tile_x - 2, tile_y + 1)) {
			if (tiles->at(Convert_xy_to_id(tile_x - 2, tile_y + 1))->black != black || tiles->at(Convert_xy_to_id(tile_x - 2, tile_y + 1))->tile_peice == 7) {
				temp.x = tile_x - 2;
				temp.y = tile_y + 1;
				moves.push_back(temp);
			}
		}
		// -3 -1
		if (On_Bored(tile_x - 2, tile_y - 1)) {
			if (tiles->at(Convert_xy_to_id(tile_x - 2, tile_y - 1))->black != black || tiles->at(Convert_xy_to_id(tile_x - 2, tile_y - 1))->tile_peice == 7) {
				temp.x = tile_x - 2;
				temp.y = tile_y - 1;
				moves.push_back(temp);
			}
		}
		// +1 -3
		if (On_Bored(tile_x + 1, tile_y - 2)) {
			if (tiles->at(Convert_xy_to_id(tile_x + 1, tile_y - 2))->black != black || tiles->at(Convert_xy_to_id(tile_x + 1, tile_y - 2))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y - 2;
				moves.push_back(temp);
			}
		}
		// +1 +3
		if (On_Bored(tile_x + 1, tile_y + 2)) {
			if (tiles->at(Convert_xy_to_id(tile_x + 1, tile_y + 2))->black != black || tiles->at(Convert_xy_to_id(tile_x + 1, tile_y + 2))->tile_peice == 7) {
				temp.x = tile_x + 1;
				temp.y = tile_y + 2;
				moves.push_back(temp);
			}
		}
		// -1 -3
		if (On_Bored(tile_x - 1, tile_y - 2)) {
			if (tiles->at(Convert_xy_to_id(tile_x - 1, tile_y - 2))->black != black || tiles->at(Convert_xy_to_id(tile_x - 1, tile_y - 2))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y - 2;
				moves.push_back(temp);
			}
		}
		// -1 +3
		if (On_Bored(tile_x - 1, tile_y + 2)) {
			if (tiles->at(Convert_xy_to_id(tile_x - 1, tile_y + 2))->black != black || tiles->at(Convert_xy_to_id(tile_x - 1, tile_y + 2))->tile_peice == 7) {
				temp.x = tile_x - 1;
				temp.y = tile_y + 2;
				moves.push_back(temp);
			}
		}

	}

	// casle 
	if (tile_peice == 6) {
		//up
		for (int i = tile_y+1; i < 8; i++) {
			if (tiles->at(Convert_xy_to_id(tile_x, i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = i;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(Convert_xy_to_id(tile_x, i))->black != black) {
					temp.x = tile_x;
					temp.y = i;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
		// down
		for (int i = 1; i < tile_y+1; i++) {
			if (tiles->at(Convert_xy_to_id(tile_x, tile_y - i))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x;
				temp.y = tile_y - i;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(Convert_xy_to_id(tile_x, tile_y - i))->black != black) {
					temp.x = tile_x;
					temp.y = tile_y - i;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
		// right
		for (int i = tile_x+1; i < 8; i++) {
			if (tiles->at(Convert_xy_to_id(i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = i;
				temp.y = tile_y;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(Convert_xy_to_id(i, tile_y))->black != black) {
					temp.x = i;
					temp.y = tile_y;
					moves.push_back(temp);
					break;
				}
				break;
			}
		}
		// left
		for (int i = 1; i < tile_x+1; i++) {
			if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y))->tile_peice == 7) { // if the tile infront is clear
				temp.x = tile_x - i;
				temp.y = tile_y;
				moves.push_back(temp);
			}
			else {
				if (tiles->at(Convert_xy_to_id(tile_x - i, tile_y))->black != black) {
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

bool Tile::Can_take_king(std::vector<Tile*>* tiles) {
	std::vector<pos> moves = get_moves(tiles);
	for (int i = 0; i < moves.size(); i++) {
		if (On_Bored(moves.at(i).x, moves.at(i).y)) {
			if (tiles->at(Convert_xy_to_id(moves.at(i).x, moves.at(i).y))->get_tile_peice() == 4 && tiles->at(Convert_xy_to_id(moves.at(i).x, moves.at(i).y))->get_color() != black) {
				return true;
			}
		}
	}
	return false;
}




bool Tile::On_Bored(int x, int y)
{
	if (x > 7 || y > 7 || x < 0 || y < 0) {
		return false;
	}
	return true;
}

Tile::~Tile()
{
}
