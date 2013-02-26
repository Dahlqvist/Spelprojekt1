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
	virtual void input();
private:
	
	void changeSelection(int choices);
	void select();
	void volymeInput();
	void raiseVolyme();
	void raiseNumbers(bool effect);
	void lowerNumbers(bool effect);
	void lowerVolyme();
	void setAnimate();
	void setSpritePosition();
	void updateNumbers();

	StateInput& mStateInput;
	Animation *currentBackground;
	Animation *currentSelection;
	Animation mMainBackground;
	Animation mInGameBackground;
	Animation mBack;
	Animation mBlip;
	Animation mEffectMute;
	Animation mEffectVolyme;
	Animation mMusicMute;
	Animation mMusicVolyme;
	Animation mEffectNumbers1;
	Animation mEffectNumbers10;
	Animation mEffectNumbers100;
	Animation mMusicNumbers1;
	Animation mMusicNumbers10;
	Animation mMusicNumbers100;
	Animation mEffectLeftArrow;
	Animation mEffectRightArrow;
	Animation mMusicLeftArrow;
	Animation mMusicRightArrow;

	int mStatus;
	float mEVolyme;
	float mMVolyme;
	bool mChangeVolyme;
	bool mEMute;
	bool mMMute;

	sf::Clock mClock;

	int mHighlight;

	int mEffectNr1;
	int mEffectNr10;
	int mEffectNr100;
	int mEffectHighlightNr;

	int mMusicNr1;
	int mMusicNr10;
	int mMusicNr100;
	int mMusicHighlightNr;

	sf::Vector2f mBlipPos;

	sf::RenderWindow &mWindow;
};

#endif