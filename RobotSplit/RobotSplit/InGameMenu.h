#ifndef INC_INGAMEMENU
#define INC_INGAMEMENU

#include "Animation.h"
#include "State.h"

class StateInput;
class Game;

class InGameMenu: public State
{
public:
	InGameMenu();
	virtual ~InGameMenu();
	virtual void update();
	virtual void render();
	virtual void input();
private:
	StateInput& mStateInput;
	Animation *currentSelection;
	Animation mBackground;
	Animation mResume;
	Animation mOptions;
	Animation mQuit;
	Animation mBlip;
	Animation mYes;
	Animation mNo;

	void sure(bool b);
	bool mShowSure;

	int mStatus;
	int mChoices;

	sf::Vector2f mBlipPos;
	sf::RenderWindow &mWindow;

};

#endif