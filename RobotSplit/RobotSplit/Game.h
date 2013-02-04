#ifndef INC_GAME
#define INC_GAME

#include "State.h"

class StateInput;

class Game: public State
{
public:
	Game();
	virtual ~Game();
	virtual void update();
	virtual void render();
private:
	void choice();
	int q;
	StateInput& mStateInput;
};

#endif