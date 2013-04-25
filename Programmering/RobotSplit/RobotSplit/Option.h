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

	virtual void input();
private:
	StateInput& mStateInput;
	Animation *currentBackground;
	Animation *currentSelection;
	Animation mMainBackground;
	Animation mInGameBackground;
	Animation mAudio;
	Animation mControls;
	Animation mBack;
	Animation mBlip;
	Animation mTimer;

	int mStatus;

	sf::Vector2f mBlipPos;

	sf::RenderWindow &mWindow;

};

#endif