#ifndef INC_INTROMOVIE
#define INC_INTROMOVIE
#include "MovieBas.h"
#include "Star.h"

class IntroMovie:public MovieBas
{
public:
	IntroMovie();
	virtual void update();
	virtual void draw();
	virtual bool playing();
	void act();
	void act2();
private:
	std::vector<Star*> Stars;
	Star mStixWalk;
	Star mStixExt;
	Star mDoorOpen;
	Star mDoorClose;
	Star mDoor2Open;
	Star mDoor2Close;
	Star mMeanix;
	Star mMeanixStill;
	sf::RenderWindow& mWindow;
	bool mPlaying;
	float mCounter;
	sf::Sprite mBackground, mBackground2;
};

#endif