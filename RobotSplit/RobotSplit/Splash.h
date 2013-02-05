#ifndef INC_SPLASH
#define INC_SPLASH

#include "State.h"

class StateInput;

class Splash: public State
{
public:
	Splash();
	virtual ~Splash();
	virtual void update();
	virtual void render(sf::RenderWindow& window);
private:
	StateInput& mStateInput;
};

#endif