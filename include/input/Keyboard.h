#ifndef KEYBOARD_H_INC
#define KEYBOARD_H_INC

#include "SDL.h"
#include "input/Device.h"

class Keyboard : public Device{

public:
	bool *keyArray;
	void update();
	Keyboard();
	~Keyboard();

};


#endif
