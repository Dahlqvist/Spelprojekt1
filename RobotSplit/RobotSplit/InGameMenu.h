#ifndef INC_INGAMEMENU
#define INC_INGAMEMENU

#include "Animation.h"
#include "State.h"

class StateInput;

class InGameMenu: public State
{
public:
	InGameMenu();
	virtual ~InGameMenu();
	virtual void update();
	virtual void render();

	void input();
private:
	StateInput& mStateInput;
	Animation mBackground;
	Animation mNewGame;
	Animation mOptions;
	Animation mQuit;
	Animation mBlip;

	int mStatus;
	double mDelay;
	float mTimer;

	sf::Vector2f mBlipPos;

	sf::RenderWindow &mWindow;

};

#endif