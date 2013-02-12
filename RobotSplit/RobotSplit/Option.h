#ifndef INC_Option
#define INC_Option

#include "Animation.h"
#include "State.h"

class StateInput;

class Option: public State
{
public:
	Option();
	virtual ~Option();
	virtual void update();
	virtual void render();

	void input();
private:
	StateInput& mStateInput;
	Animation *currentBackground;
	Animation mMainBackground;
	Animation mInGameBackground;
	Animation mNewGame;
	Animation mOptions;
	Animation mBack;
	Animation mBlip;

	int mStatus;

	sf::Vector2f mBlipPos;

	sf::RenderWindow &mWindow;

};

#endif