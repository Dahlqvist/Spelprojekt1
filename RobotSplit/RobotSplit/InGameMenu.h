#ifndef INC_INGAMEMENU
#define INC_INGAMEMENU

#include "State.h"

class StateInput;

class InGameMenu: public State
{
public:
	InGameMenu();
	virtual ~InGameMenu();
	virtual void update();
	virtual void render(sf::RenderWindow& window);
private:
	void choice();
	StateInput& mStateInput;
};

#endif