#ifndef INC_CONTROLS
#define INC_CONTROLS

#include "State.h"
#include "Animation.h"


class StateInput;

class Controls: public State
{
public:
	Controls();
	virtual ~Controls();
	virtual void update();
	virtual void render();
	virtual void input();

private:
	StateInput& mStateInput;
	Animation *currentSelection;
	Animation *currentBackground;
	Animation mBackground;
	Animation mInGameBackground;
	Animation mControlSchedule;
	Animation mBlip;
	Animation mBack;

	int mStatus;

	sf::Vector2f mBlipPos;
	sf::RenderWindow &mWindow;
};

#endif