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
	std::vector <leaf> tree = Gen_tree(tiles, Search_death);
	my_move t;
	t.score =- 1000;
	for (int i = 0; i < tree.size(); i++) {
		if (t.score < tree.at(i).score) {
			t.to = tree.at(i).to;
			t.from = tree.at(i).from;
			t.score = tree.at(i).score;
		}
	}
	return t;

}
std::vector <leaf> AI::Gen_tree(std::vector<Tile*> tiles, int Search_depth) {
	std::vector < std::vector<leaf>> tree;
	tree.push_back(get_ranked_moves(tiles, black, 0));

	for (int depth = 0; depth < Search_depth; depth++) {
		std::vector<leaf> leaf_layer;
		for (int brantch = 0; brantch < tree.at(depth).size(); brantch++) {
			std::vector<my_move> movelist;
			std::vector<Tile *> temp;
			for (int i = 0; i < tiles.size(); i++) {
				temp.push_back(new Tile(*tiles.at(i)));
			}
			for (int i = depth; i > 0 ; i--) {
				my_move temp_move;
				int b_master = tree.at(i).at(brantch).master;
				temp_move.from = tree.at(i).at(b_master).from;
				temp_move.to = tree.at(i).at(b_master).to;
				movelist.push_back(temp_move);
				
			}
			my_move temp_move;
			temp_move.from = tree.at(depth).at(brantch).from;
			temp_move.to = tree.at(depth).at(brantch).to;
			movelist.push_back(temp_move);

			for (int i = 0; i < movelist.size(); i++) {
				make_move(temp, movelist.at(i).to, movelist.at(i).from);
			}
			if (!(depth % 2 == 0)) {
				std::vector<leaf> t = get_ranked_moves(temp, !black, brantch);
				leaf_layer.insert(leaf_layer.end(), t.begin(), t.end());
			}
			else {
				std::vector<leaf> t = get_ranked_moves(temp, black, brantch);
				leaf_layer.insert(leaf_layer.end(), t.begin(), t.end());
			}
			
			
		}tree.push_back(leaf_layer);
	}
	for (int i = tree.size()-1; i > 0; i--) {
		if (!(i % 2 == 0)) {
			// min
		
			for (int n = 0; n < tree.at(i-1).size(); n++) {
				int low = 10000000;
				for (int leaf_i = 0; leaf_i < tree.at(i).size(); leaf_i++) {
					if (tree.at(i).at(leaf_i).score < low) {
						low = tree.at(i).at(leaf_i).score;
					}
				}
				tree.at(i - 1).at(n).score = low;
			}

		}
		else {
			// max
			for (int n = 0; n < tree.at(i - 1).size(); n++) {
				int high = -10000000;
				for (int leaf_i = 0; leaf_i < tree.at(i).size(); leaf_i++) {
					if (tree.at(i).at(leaf_i).score > high) {
						high = tree.at(i).at(leaf_i).score;
					}
				}
				tree.at(i - 1).at(n).score = high;
			}
			
		}
	
	}
	return tree.at(0);

}
// returns a vector of all posiable moves with the a score for each
std::vector <leaf> AI::get_ranked_moves(std::vector<Tile*> tiles,bool team,int master) {
	std::vector<Tile *> temp;
	for (int i = 0; i < tiles.size(); i++) {
		temp.push_back(new Tile(*tiles.at(i)));
	}
	// store best move 
	std::vector <leaf> ranked_moves;
	// test all peices 
	for (int peice = 0; peice < temp.size(); peice++) {
		if(temp.at(peice)->get_color() == team){
		// test all of peices moves
		std::vector <Tile::pos> moves = temp.at(peice)->get_moves(&temp);
		for (int move = 0; move < moves.size(); move++) {

			int to = Convert_xy_to_id2(moves.at(move).x, moves.at(move).y);
			if (make_move(temp, to, peice)) {
				leaf temp_move;
				temp_move.master = master;
				temp_move.score = get_board_value(temp,team);
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
int AI::get_board_value(std::vector<Tile*> tiles ,bool color)
{
	int black_score = 0;
	int white_score = 0;

	for (int i = 0; i < tiles.size(); i++) {							
		if (tiles.at(i)->Get_peice() == 1) {							//Pawn
			if (tiles.at(i)->get_color() == false) {						//white 
				white_score += 1;
			}
			else {														//black
				black_score += 1;
			}
		}
		
		if (tiles.at(i)->Get_peice() == 2) {							//Bishup
			if (tiles.at(i)->get_color() == false) {						//white 
				white_score += 3;
			}
			else {														//black
				black_score += 3;
			}
		}
		if (tiles.at(i)->Get_peice() == 3) {							//Queen
			if (tiles.at(i)->get_color() == false) {						//white 
				white_score += 9;
			}
			else {														//black
				black_score += 9;
			}
		}
		if (tiles.at(i)->Get_peice() == 4) {							//King
			if (tiles.at(i)->get_color() == false) {						//white 
				white_score += 3;
			}
			else {														//black
				black_score += 3;
			}
		}
		if (tiles.at(i)->Get_peice() == 5) {							//Knight
			if (tiles.at(i)->get_color() == false) {						//white 
				white_score += 3;
			}
			else {														//black
				black_score += 3;
			}
		}
		if (tiles.at(i)->Get_peice() == 6) {							//Casle
			if (tiles.at(i)->get_color() == false) {						//white 
				white_score += 5;
			}
			else {														//black
				black_score += 5;
			}
		}
	}
	if (color == false) // white 
		return black_score;

	return white_score;
}

AI::AI()
{
}


AI::~AI()
{
}
