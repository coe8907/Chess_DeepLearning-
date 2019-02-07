#include "include\SDL.h"
#include "Game.h"
#include <chrono>
#include <iostream>



#undef main
bool running = true;
void mainloop();



Game* game;

int ups = 0;
int fps = 0;
auto end = std::chrono::system_clock::now();
auto sec_count_s = std::chrono::system_clock::now();
auto sec_count_e = std::chrono::system_clock::now();

void paint() {
	fps += 1;
	game->paint();
}

int main(void) {
	game = new Game;


	mainloop();
	if (game) {
	delete game;
	game = nullptr;
	}
	return 0;

	
}
void mainloop() {
	while (running) {

		auto start = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		while (start - end > (std::chrono::duration<double>)0.016) {
			game->update();
			ups++;
			end = std::chrono::system_clock::now();
		}

		paint();
		sec_count_e = std::chrono::system_clock::now();


		if (sec_count_e - sec_count_s > (std::chrono::duration<double>)1.00) {
			sec_count_s = std::chrono::system_clock::now();
			std::cout << "UPS " << ups << "   FPS " << fps << std::endl;
			ups = 0;
			fps = 0;


		}


	}
}
