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

	
private:
	void input();
	void raiseVolyme();
	void lowerVolyme();

	StateInput& mStateInput;
	Animation *currentBackground;
	Animation *currentSelection;
	Animation mMainBackground;
	Animation mInGameBackground;
	Animation mBack;
	Animation mBlip;
	Animation mEffectMuteChecked;
	Animation mEffectMuteUnchecked;
	Animation mEffectVolyme;
	Animation mMusicMuteChecked;
	Animation mMusicMuteUnchecked;
	Animation mMusicVolyme;

	int mStatus;
	float mEVolyme;
	float mMVolyme;
	bool mChangeVolyme;

	sf::Vector2f mBlipPos;

	sf::RenderWindow &mWindow;
};

#endif