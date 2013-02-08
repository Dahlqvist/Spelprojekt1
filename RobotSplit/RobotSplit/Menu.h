#ifndef INC_MENU
#define INC_MENU

#include "Animation.h"
#include "State.h"

class StateInput;

class Menu: public State
{
public:
	Menu();
	virtual ~Menu();
	virtual void update();
	virtual void render();

	void input();
private:
	StateInput& mStateInput;
	Animation mBackground;
	Animation mNewGame;
	Animation mOptions;
	Animation mQuit;

	sf::RenderWindow &mWindow;

};

#endif