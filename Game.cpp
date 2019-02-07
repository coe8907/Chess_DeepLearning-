#include "Game.h"

SDL_Renderer* Game::m_Renderer = nullptr;
int Convert_xy_to_id(int x, int y) {
	return x * 8 + y;
}
Game::Game(){
	m_Window = nullptr;
	m_Renderer = nullptr;

	SDL_Init(SDL_INIT_VIDEO);

	m_Window = SDL_CreateWindow("SOKO II Cold Night", 250,50,640,480,0);
	if (!m_Window) {
		printf("ohhhhh well fuck, it didnt work window = false");
		getchar();
		return;
	}
	m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
	if (!m_Renderer) {
		printf("ohhhhh well fuck, it didnt work renderer = false");
		getchar();
		return;
	}
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			floor.push_back(new Tile(x, y, 0));
			floor.at(x*8 + y)->Set_peice(7, true);
		}
	}
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			tiles.push_back(new Tile(x, y, 0));
			tiles.at(x * 8 + y)->Set_peice(7, false);
		}
	}
	
	set_bored();
	
}



void Game::set_bored()
{
	tiles.at(Convert_xy_to_id(4, 4))->Set_peice(2,false);

	tiles.at(0)->Set_peice(6, true);
	tiles.at(1)->Set_peice(1, true);

	tiles.at(6)->Set_peice(1, false);
	tiles.at(7)->Set_peice(6, false);

	tiles.at(8)->Set_peice(5, true);
	tiles.at(9)->Set_peice(1, true);

	tiles.at(14)->Set_peice(1, false);
	tiles.at(15)->Set_peice(5, false);

	tiles.at(16)->Set_peice(2, true);
	tiles.at(17)->Set_peice(1, true);

	tiles.at(22)->Set_peice(1, false);
	tiles.at(23)->Set_peice(2, false);

	tiles.at(24)->Set_peice(4, true);
	tiles.at(25)->Set_peice(1, true);

	tiles.at(30)->Set_peice(1, false);
	tiles.at(31)->Set_peice(4, false);

	tiles.at(32)->Set_peice(3, true);
	tiles.at(33)->Set_peice(1, true);

	tiles.at(38)->Set_peice(1, false);
	tiles.at(39)->Set_peice(3, false);

	tiles.at(40)->Set_peice(2, true);
	tiles.at(41)->Set_peice(1, true);

	tiles.at(46)->Set_peice(1, false);
	tiles.at(47)->Set_peice(2, false);

	tiles.at(48)->Set_peice(4, true);
	tiles.at(49)->Set_peice(1, true);

	tiles.at(54)->Set_peice(1, false);
	tiles.at(55)->Set_peice(4, false);
	
	tiles.at(56)->Set_peice(5, true);
	tiles.at(57)->Set_peice(1, true);

	tiles.at(62)->Set_peice(1, false);
	tiles.at(63)->Set_peice(5, false);
	
	
}

std::vector<Tile::pos> t;
int selected = 0;
void Game::update() {
	input.I_Update();
	if (!(move % 2 == 0)) {
		AI_move(&temp_ai);
	}
	else {
		if (tiles.at(Convert_xy_to_id(input.last_click.x / 40, input.last_click.y / 40))->get_color() == false && tiles.at(Convert_xy_to_id(input.last_click.x / 40, input.last_click.y / 40))->get_tile_peice() != 7) {
			for (int i = 0; i < t.size(); i++) {
				floor.at(Convert_xy_to_id(t.at(i).x, t.at(i).y))->Set_peice(7, true);
			}
			t = tiles.at(Convert_xy_to_id(input.last_click.x / 40, input.last_click.y / 40))->get_moves(&tiles);
			selected = Convert_xy_to_id(input.last_click.x / 40, input.last_click.y / 40);
			for (int i = 0; i < t.size(); i++) {
				floor.at(Convert_xy_to_id(t.at(i).x, t.at(i).y))->Set_peice(8, true);
			}
		}
		else {
			if(selected != -1){
				for (int i = 0; i < t.size(); i++) {
					if (t.at(i).x == (int)input.last_click.x / 40) {
						if (t.at(i).y == (int)input.last_click.y / 40) {
							make_move(Convert_xy_to_id(input.last_click.x / 40, input.last_click.y / 40));
							break;
						}
					}
				}
			}
		}
	}
}


bool Game::AI_move(AI* ai) {
	my_move t = ai->Get_move(tiles);
	return make_move(t.from, t.to);
}

bool Game::make_move(int from, int to) {
	selected = from;
	return make_move(to);
}

bool Game::make_move(int to) {
	
	std::vector<Tile *> temp;	
	for (int i = 0; i < tiles.size(); i++) {
		//Tile * d =  new ;
		
		temp.push_back(new Tile(*tiles.at(i)));
	}
	Tile * b = temp.at(to);
	int old_x = temp.at(selected)->get_tile_x();
	int old_y = temp.at(selected)->get_tile_y();
	temp.at(selected)->move(b->get_tile_x(), b->get_tile_y());
	b->move(old_x, old_y);

	temp.at(to) = temp.at(selected);
	temp.at(selected) = b;
	b->Set_peice(7, false);

	if (!(move % 2 == 0)) { // blacks move
		// check if move would put in check 
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 7; y++) {
				if (temp.at(Convert_xy_to_id(x, y))->get_color() == false && temp.at(Convert_xy_to_id(x, y))->get_tile_peice() != 7) {
					if (temp.at(Convert_xy_to_id(x, y))->Can_take_king(&temp)) {
						printf("INVALID MOVE:   Would Place in check ... ");
						input.clear_last_click();
						return false;
					}
				}
			}
		}

	}
	else {// white move 
		// check if move would put in check 
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 7; y++) {
				if (temp.at(Convert_xy_to_id(x, y))->get_color() == true && temp.at(Convert_xy_to_id(x, y))->get_tile_peice() != 7) {
					if (temp.at(Convert_xy_to_id(x, y))->Can_take_king(&temp)) {
						printf("INVALID MOVE:   Would Place in check ... ");
						input.clear_last_click();
						return false;
					}
				}
			}
		}
	}

	Tile * t = tiles.at(to);
	 old_x = tiles.at(selected)->get_tile_x();
	 old_y = tiles.at(selected)->get_tile_y();
	tiles.at(selected)->move(t->get_tile_x(), t->get_tile_y());
	t->move(old_x, old_y);

	tiles.at(to) = tiles.at(selected);
	tiles.at(selected) = t;
	t->Set_peice(7, false);

	selected = -1;
	move++;
	white_in_check = false;
	black_in_check = false;
	if (!(move % 2 == 0)) {
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 7; y++) {
				if (tiles.at(Convert_xy_to_id(x, y))->get_color() == false && tiles.at(Convert_xy_to_id(x, y))->get_tile_peice() != 7) {
					if (tiles.at(Convert_xy_to_id(x, y))->Can_take_king(&tiles)) {
						white_in_check = true;
					}
				}
			}
		}
	}
	else {
		for (int x = 0; x < 7; x++) {
			for (int y = 0; y < 7; y++) {
				if (tiles.at(Convert_xy_to_id(x, y))->get_color() == true && tiles.at(Convert_xy_to_id(x, y))->get_tile_peice() != 7) {
					if (tiles.at(Convert_xy_to_id(x, y))->Can_take_king(&tiles)) {
						black_in_check = true;
					}
				}
			}
		}
	}
	if (black_in_check == true) {
		printf("Black in Check !!!");
	}
	if (white_in_check == true) {
		printf("White in Check !!!");
	}
	return true;
}

void Game::paint() {
	if (m_Renderer) {
	
		int result = SDL_SetRenderDrawColor(m_Renderer,255,0,0,255);
		SDL_RenderClear(m_Renderer);
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				
				floor.at(x * 8 + y)->paint();
			}
		}
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				tiles.at(x * 8 + y)->paint();
			}
		}
		SDL_RenderPresent(m_Renderer);
		
	}
}

Game::~Game() {
	if (m_Renderer) {
		SDL_DestroyRenderer(m_Renderer);
	}
	if (m_Window) {
		SDL_DestroyWindow(m_Window);
	}
	tiles.empty();
}