#ifndef INC_INTROMOVIE
#define INC_INTROMOVIE
#include "MovieBas.h"
#include "Star.h"
#include "DialogueBox.h"

class IntroMovie:public MovieBas
{
public:
	IntroMovie();
	virtual void update();
	virtual void draw();
	virtual bool playing();
	virtual void countup();
	virtual void endit();
	void act();
	void act2();
private:
	std::vector<Star*> mStars;
	std::vector<DialogueBox*> mDialogs;
	Star mStixWalk;
	Star mStixExt;
	Star mStixExtStill;
	Star mStixJumpDown;
	Star mDoorOpen;
	Star mDoorClose;
	Star mDoor2Open;
	Star mDoor2Close;
	Star mMeanix;
	Star mMeanixStill;
	Star mMeanixHat;
	Star mGlass;
	sf::RenderWindow& mWindow;
	bool mPlaying, mTalk;
	float mCounter, mDia;
	sf::Sprite mBackground, mBackground2;
};

#endif