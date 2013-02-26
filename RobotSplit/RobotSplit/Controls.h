#ifndef INC_CONTROLS
#define INC_CONTROLS

#include "State.h"
#include "Animation.h"

class StateInput;

class Controls: public State
{
public:
	Controls();
	virtual ~Controls();
	virtual void update();
	virtual void render();
	virtual void input();

private:
};

#endif