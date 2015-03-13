#include "input/Mouse.h"

Mouse::Mouse(){
	keyArray = new bool[SDL_NUM_SCANCODES];
	for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		keyArray[i] = false;
}

void Mouse::update(SDL_Event &event){
	if (event.type == SDL_KEYUP)
		keyArray[event.key.keysym.scancode] = false;
	else if (event.type == SDL_KEYDOWN)
		keyArray[event.key.keysym.scancode] = true;
}

Mouse::~Mouse(){
}