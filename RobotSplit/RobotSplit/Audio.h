#ifndef INC_AUDIO
#define INC_AUDIO

#include "State.h"
#include "Animation.h"

class StateInput;

class Audio: public State
{
public:
	Audio();
	virtual ~Audio();
	virtual void update();
	virtual void render();

	void input();
private:
	StateInput& mStateInput;
	Animation *currentBackground;
	Animation mMainBackground;
	Animation mInGameBackground;
	Animation mBack;
	Animation mBlip;

	int mStatus;

	sf::Vector2f mBlipPos;

	sf::RenderWindow &mWindow;
};

#endif