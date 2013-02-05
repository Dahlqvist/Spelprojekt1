#ifndef INC_SPLASH
#define INC_SPLASH

#include "State.h"

class StateInput;

class Splash: public State
{
public:
	Splash(sf::RenderWindow& window);
	virtual ~Splash();
	virtual void update();
	virtual void render();
private:
	StateInput& mStateInput;
	sf::RenderWindow& mWindow;
};

#endif