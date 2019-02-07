#include "Input.h"
#include "include\SDL.h"



Input::Input()
{
	
}

Input::pos Input::getmousepos()
{
	pos place;
	SDL_GetMouseState(&place.x, &place.y);
	return place;
}
Input::keys Input::I_Update() {
	keys d;
	SDL_Event m_event;
	while (SDL_PollEvent(&m_event) != NULL) {
		if (m_event.type == SDL_MOUSEBUTTONDOWN) {
			SDL_MouseButtonEvent button_pressed = m_event.button;
			if (button_pressed.button == SDL_BUTTON_LEFT) {
				last_click = getmousepos();
			}
		}
		if (m_event.type == SDL_KEYDOWN) {
			SDL_Keycode keypressed = m_event.key.keysym.sym;
			
				if (keypressed == SDLK_UP) {
					d.up = true;
				}
				if (keypressed == SDLK_DOWN) {
					d.down = true;
				}
				if (keypressed == SDLK_LEFT) {
					d.left = true;
				}
				if (keypressed == SDLK_RIGHT) {
					d.right = true;
				
			}
		}
		if (m_event.type == SDL_KEYUP) {
			SDL_Keycode keypressed = m_event.key.keysym.sym;
			if (keypressed == SDLK_UP) {
				d.up = false;
			}
			if (keypressed == SDLK_DOWN) {
				d.down = false;
			}
			if (keypressed == SDLK_LEFT) {
				d.left = false;
			}
			if (keypressed == SDLK_RIGHT) {
				d.right = false;
			
			}
		}
	}
	return d;
}
Input::~Input()
{
}
