#include "AI.h"


int Convert_xy_to_id2(int x, int y) {
	return x * 8 + y;
}
my_move AI::Get_move(std::vector<Tile*> tiles)
{
	
	// return best move 
	return Min_Max(tiles,2);
}
my_move AI::Min_Max(std::vector<Tile*> tiles,int Search_death)
{


}
std::vector <my_move> AI::get_ranked_moves(std::vector<Tile*> tiles,bool team) {
	std::vector<Tile *> temp;
	for (int i = 0; i < tiles.size(); i++) {
		temp.push_back(new Tile(*tiles.at(i)));
	}
	// store best move 
	std::vector <my_move> ranked_moves;
	// test all peices 
	for (int peice = 0; peice < temp.size(); peice++) {
		if(temp.at(peice)->get_color == team){
		// test all of peices moves
		std::vector <Tile::pos> moves = temp.at(peice)->get_moves(&temp);
		for (int move = 0; move < moves.size(); move++) {

			int to = Convert_xy_to_id2(moves.at(move).x, moves.at(move).y);
			if (make_move(temp, to, peice)) {
				my_move temp_move;

				temp_move.score = get_board_value(temp);
				temp_move.from = peice;
				temp_move.to = to;
				ranked_moves.push_back(temp_move);
			}
			temp.clear();
			for (int i = 0; i < tiles.size(); i++) {
				temp.push_back(new Tile(*tiles.at(i)));
			}
		}
		}
	}
	return ranked_moves;
}
bool AI::make_move(std::vector<Tile *> temp,int to,int selected) {
	Tile * b = temp.at(to);
	int old_x = temp.at(selected)->get_tile_x();
	int old_y = temp.at(selected)->get_tile_y();
	temp.at(selected)->move(b->get_tile_x(), b->get_tile_y());
	b->move(old_x, old_y);

	temp.at(to) = temp.at(selected);
	temp.at(selected) = b;
	b->Set_peice(7, false);
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 7; y++) {
			if (temp.at(Convert_xy_to_id2(x, y))->get_color() != black && temp.at(Convert_xy_to_id2(x, y))->get_tile_peice() != 7) {
				if (temp.at(Convert_xy_to_id2(x, y))->Can_take_king(&temp)) {
					return false;
				}
			}
		}
	}
	return true;
}
int AI::get_board_value(std::vector<Tile*> tiles)
{

	return 1;
}

AI::AI()
{
}


AI::~AI()
{
}
