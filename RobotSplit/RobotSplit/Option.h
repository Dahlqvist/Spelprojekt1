#ifndef INC_OPTION
#define INC_OPTION

#include "State.h"

class StateInput;

class Option: public State
{
public:
	Option();
	virtual ~Option();
	virtual void update();
	virtual void render(sf::RenderWindow& window);
private:
	int p;
	void choice();
	StateInput& mStateInput;
};

#endif