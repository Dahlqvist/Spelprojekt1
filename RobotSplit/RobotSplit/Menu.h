#ifndef INC_MENU
#define INC_MENU

class StateInput;

#include "State.h"

class Menu: public State
{
public:
	Menu();
	virtual ~Menu();
	virtual void update();
	virtual void render(sf::RenderWindow& window);

	void choice();
private:
	StateInput& mStateInput;
};

#endif