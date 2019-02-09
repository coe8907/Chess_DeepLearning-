#include "AI_2.h"


int AI_2::Convert_xy_to_id3(int x, int y) {
	return x * 8 + y;
}
bool AI_2::On_Bored(int x, int y)
{
	if (x > 7 || y > 7 || x < 0 || y < 0) {
		return false;
	}
	return true;
}
my_move AI_2::Get_move(std::vector<Tile*> tiles)
{
	cut_peices = 0;
	test_pre = 0;
	std::vector<Tile *> temp;
	for (int i = 0; i < tiles.size(); i++) {
		temp.push_back(new Tile(*tiles.at(i)));
	}
	my_move best_move;
	best_move.score = -100;
	for (int i = 0; i < tiles.size(); i++) {
		if (tiles.at(i)->get_color() == black) {
			std::vector <Tile::pos> moves = tiles.at(i)->get_moves(&tiles);
			sort_moves(temp, &moves);
			for (int x = 0; x < moves.size(); x++) {
				int c_score = -100;
				if (On_Bored(moves.at(x).x, moves.at(x).y)) {
					if (make_move(temp, Convert_xy_to_id3(moves.at(x).x, moves.at(x).y), i)) {

						c_score = Min_Max(temp, 0, 2, false,-9999,9999);
						temp.at(Convert_xy_to_id3(moves.at(x).x, moves.at(x).y)) = (new Tile(*tiles.at(Convert_xy_to_id3(moves.at(x).x, moves.at(x).y))));
						temp.at(i) = new Tile(*tiles.at(i));
						if (c_score > best_move.score) {
							best_move.score = c_score;
							best_move.to = Convert_xy_to_id3(moves.at(x).x, moves.at(x).y);
							best_move.from = i;
						}
					}
					else {
						temp.at(Convert_xy_to_id3(moves.at(x).x, moves.at(x).y)) = (new Tile(*tiles.at(Convert_xy_to_id3(moves.at(x).x, moves.at(x).y))));
						temp.at(i) = new Tile(*tiles.at(i));
					}
				}
			}
		}
	}
	std::cout <<"move found : moves tested " + test_pre << " peices cut = " << cut_peices << std::endl;
	temp.clear();
	return best_move;
}

int AI_2::Min_Max(std::vector<Tile*> tiles, int depth, int max_depth, bool isMax,int alpha, int beta) {
	if (depth >= max_depth) {
		return get_board_value(tiles, isMax);
	}
	std::vector<Tile *> temp = tiles;
	/*for (int i = 0; i < tiles.size(); i++) {
		temp.push_back(new Tile(*tiles.at(i)));
	}*/
	int best;
	bool break_out = false;

	if (isMax) {
		best = -9999;
		for (int i = 0; i < tiles.size(); i++) {
			if (break_out) {
				//std::cout << "tree cut -" << (tiles.size() - i) << std::endl;
				cut_peices += (tiles.size() - i);
				break;
			}
			if (tiles.at(i)->get_color() == black) {
				std::vector <Tile::pos> moves = tiles.at(i)->get_moves(&tiles);
				sort_moves(temp, &moves);
				for (int x = 0; x < moves.size(); x++) {
					if (On_Bored(moves.at(x).x, moves.at(x).y)) {
						if (make_move(temp, Convert_xy_to_id3(moves.at(x).x, moves.at(x).y), i)) {
							best = std::max(best, Min_Max(temp, depth + 1, max_depth, !isMax,alpha,beta));
							alpha = std::max(alpha, best);
							if (beta <= alpha) {
								break_out = true;
								break;
							}
							
						}
						else {
							best = std::min(best, -9999);
						}
						temp.at(Convert_xy_to_id3(moves.at(x).x, moves.at(x).y)) = (new Tile(*tiles.at(Convert_xy_to_id3(moves.at(x).x, moves.at(x).y))));
						temp.at(i) = new Tile(*tiles.at(i));
					}
				}
			}
		}
	}
	else {
		best = 9999;
		for (int i = 0; i < tiles.size(); i++) {
			if (break_out) {
				//std::cout << "tree cut -" << (tiles.size() - i) << std::endl;
				cut_peices += (tiles.size() - i);
				break;
			}
			bool bre = false;
			if (tiles.at(i)->get_color() != black) {
				std::vector <Tile::pos> moves = tiles.at(i)->get_moves(&tiles);
				sort_moves(temp, &moves);
				for (int x = 0; x < moves.size(); x++) {
					if (On_Bored(moves.at(x).x, moves.at(x).y)) {
						if (make_move(temp, Convert_xy_to_id3(moves.at(x).x, moves.at(x).y), i)) {
							best = std::min(best, Min_Max(temp, depth + 1, max_depth, !isMax,alpha,beta));
							beta = std::min(beta, best);
							if (beta <= alpha) {
								break_out = true;
								break;
							}
							
						}
						else {
							best = std::min(best, 9999);
						}
						temp.at(Convert_xy_to_id3(moves.at(x).x, moves.at(x).y)) = (new Tile(*tiles.at(Convert_xy_to_id3(moves.at(x).x, moves.at(x).y))));
						temp.at(i) = new Tile(*tiles.at(i));
						
					}
				}
			}
		}
	}
	temp.clear();
	return best;
}




bool AI_2::make_move(std::vector<Tile *> temp, int to, int selected) {
	Tile * b = temp.at(to);
	int old_x = temp.at(selected)->get_tile_x();
	int old_y = temp.at(selected)->get_tile_y();
	temp.at(selected)->move(b->get_tile_x(), b->get_tile_y());
	b->move(old_x, old_y);

	temp.at(to) = temp.at(selected);
	temp.at(selected) = b;
	

	b->Set_peice(7,true);
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 7; y++) {
			if (temp.at(Convert_xy_to_id3(x, y))->get_color() != temp.at(to)->get_color() && temp.at(Convert_xy_to_id3(x, y))->get_tile_peice() != 7) {
				if (temp.at(Convert_xy_to_id3(x, y))->Can_take_king(&temp)) {
					return false;
				}
			}
		}
	}
	
	return true;
}
void AI_2::sort_moves(std::vector<Tile *> temp,std::vector <Tile::pos> * moves) {
	for (int i = 0; i < moves->size(); i++) {
		int chigh = -9999;
		int id = 0;
		for (int e = 0; e < moves->size(); e++) {
			if (get_move_aprox_value(temp, Convert_xy_to_id3(moves->at(e).x, moves->at(e).y), i) > chigh) {
				chigh = get_move_aprox_value(temp, Convert_xy_to_id3(moves->at(e).x, moves->at(e).y), i);
				id = e;
			}
		}
		std::swap(moves->begin() + i, moves->begin() + id);

	}
}
int AI_2::get_move_aprox_value(std::vector<Tile *> temp, int to, int selected) {
	int move_value = 0;
	if (temp.at(to)->get_value() == 0) {
		return move_value;
	}

	// if the selected peice is worth more than the other peice 
	if (temp.at(to)->get_value() < temp.at(selected)->get_value()) { // usaly bad move
		move_value += (temp.at(to)->get_value()- temp.at(selected)->get_value());
	}
	// if the selected peice is worth less than the other peice 
	if (temp.at(to)->get_value() > temp.at(selected)->get_value()) { // usaly good move 
		move_value += (temp.at(to)->get_value() - temp.at(selected)->get_value());
	}
	return move_value;
}
int AI_2::get_board_value(std::vector<Tile*> tiles, bool color)
{

	int black_score = 0;
	int white_score = 0;
	if (test_pre % 100000 == 0) {
		std::cout << test_pre << std::endl;
	}
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
	//if (test_pre == 0) {
		//std::cout << "white points = " << black_score - white_score << "  black points = "<< white_score - black_score << std::endl;
	//}

	test_pre++;

	if (black) { // white 
		return white_score - black_score;
	}
	else {
		return black_score - white_score;
	}
}



AI_2::AI_2()
{
}


AI_2::~AI_2()
{
}
