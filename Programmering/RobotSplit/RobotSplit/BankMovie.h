#ifndef INC_BANKMOVIE
#define INC_BANKMOVIE
#include "MovieBas.h"
#include "Star.h"
#include "DialogueBox.h"

class BankMovie:public MovieBas
{
public:
	BankMovie();
	virtual void update();
	virtual void draw();
	virtual bool playing();
	virtual void countup();
	virtual void endit();
	void act();
	void act2();
	void act3();
private:
	std::vector<Star*> mStars;
	Star mExclMark;
	Star mLights1;
	Star mLights2;
	Star mLights3;
	Star mPolice;
	Star mPolice2;
	Star mPoliceWalk;
	Star mPoliceWalk2;
	Star mStix;
	Star mStixWalk;
	Star mStixSad;
	Star mJudge;
	Star mTrapDoor;
	Star mButton;
	Star mPressButton;
	Star mFloor;
	sf::RenderWindow& mWindow;
	bool mPlaying;
	float mCounter, mTime;
	sf::Sprite mBackground, mBackground2;
	sf::Color mColor;
};

#endif