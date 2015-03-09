#ifndef INPUT_H_INC
#define INPUT_H_INC

#include <iostream>
#include "System.h"
#include "SDL.h"
#include "Event.h"
#include <queue>

class Input : public System {

public:
	SDL_Window *mainWindow;
	std::queue<Event> eventQueue;
	Uint32 *keyState;
	void update(float dt);
    Input(SDL_Window *mainWindow);
    ~Input();
};

#endif