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

	virtual void input();
private:
	StateInput& mStateInput;
	Animation *currentSelection;
	Animation mBackground;
	Animation mNewGame;
	Animation mOptions;
	Animation mQuit;
	Animation mBlip;

	int mStatus;

	sf::Vector2f mBlipPos;

	sf::RenderWindow &mWindow;

};

#endif