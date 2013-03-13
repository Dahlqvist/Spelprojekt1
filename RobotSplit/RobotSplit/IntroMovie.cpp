#include "IntroMovie.h"
#include "Window.h"
#include "TextureManager.h"

IntroMovie::IntroMovie():
mWindow(Window::getWindow()),
	mStixWalk(Animation("StixWalk", 100, 6), sf::Vector2f(0, 540), true, true),
	mStixExt(Animation("StixExt", 100, 17), sf::Vector2f(0, 0), false, false),
	mDoorOpen(Animation("DoorOpen", 100, 8), sf::Vector2f(898, 419), false, false),
	mDoorClose(Animation("DoorClose", 100, 8), sf::Vector2f(898, 419), false, false),
	mDoor2Open(Animation("DoorOpen", 100, 8), sf::Vector2f(0, 503), false, false),
	mDoor2Close(Animation("DoorClose", 100, 8), sf::Vector2f(0, 503), false, false),
	mMeanix(Animation("MeanixBank", 100, 8), sf::Vector2f(806, 576), false, true),
	mMeanixStill(Animation("MeanixBank2", 100, 1), sf::Vector2f(806, 576), false, false)
{
	mCounter=0;
	mPlaying=true;
	mBackground=TextureManager::getSprite("CinemaBG1");
	mBackground2=TextureManager::getSprite("CinemaBG2");

	Stars.push_back(&mDoor2Open);
	Stars.push_back(&mDoorOpen);
	Stars.push_back(&mStixWalk);
	Stars.push_back(&mStixExt);
	Stars.push_back(&mDoorClose);
	Stars.push_back(&mDoor2Close);
	Stars.push_back(&mMeanix);
	Stars.push_back(&mMeanixStill);
}

void IntroMovie::draw()
{
	mWindow.clear();
	if(mCounter==0)
	{
		mWindow.draw(mBackground);
	}
	else
	{
		mWindow.draw(mBackground2);
	}

	for(unsigned int i=0; i<Stars.size(); i++)
	{
		if(Stars[i]->getActive())
		{
			mWindow.draw(Stars[i]->getSprite());
		}
	}
	mWindow.display();
}

void IntroMovie::act()
{
	if(mStixWalk.getPosition().x<800)
	{
		mStixWalk.setPosition(mStixWalk.getPosition()+sf::Vector2f(1, 0));
	}
	else if(mStixWalk.getPosition().x<950)
	{
		mDoorOpen.setActive(true);
		mStixWalk.setPosition(mStixWalk.getPosition()+sf::Vector2f(1, 0));
	}
	else if(mStixWalk.getPosition().x<965)
	{
		mStixWalk.setPosition(mStixWalk.getPosition()+sf::Vector2f(0.2, -0.3));
	}
	else
	{
		mDoorOpen.setActive(false);
		mDoorClose.setActive(true);
		if(mDoorClose.getDone()==true)
		{
			mCounter++;
			mStixWalk.setPosition(sf::Vector2f(0, 608));
			mDoor2Open.setActive(true);
			mDoorClose.setActive(false);
			mMeanix.setActive(true);
		}
	}
}
void IntroMovie::act2()
{
	if(mDoor2Open.getDone()==false)
	{
	
	}
	else if(mStixWalk.getPosition().x<578)
	{
		if(mStixWalk.getPosition().x>150)
		{
			mDoor2Open.setActive(false);
			mDoor2Close.setActive(true);
		}
		mStixWalk.setPosition(mStixWalk.getPosition()+sf::Vector2f(1, 0));
		mStixExt.setPosition(mStixWalk.getPosition()+sf::Vector2f(-68, -31));
	}
	else
	{
		mStixWalk.setActive(false);
		mStixExt.setActive(true);
		if(mStixExt.getDone()==true)
		{
			mCounter++;
			mMeanix.setActive(false);
			mMeanixStill.setActive(true);
		}
	}
}

void IntroMovie::update()
{
	if(mCounter==0)
	{
		IntroMovie::act();
	}
	else if(mCounter==1)
	{
		IntroMovie::act2();
	}
	else
	{
		mPlaying=false;
		//if(knapptryck)
		//	if(mPratbubblorcounter<Pratbubblor.size())
		//	mPratbubblorcounter++
		//	mSetactivepratbubbla(mPratbubblorcounter)
		//	else
		//	mPlaying=false;
	}
	for(unsigned int i=0; i<Stars.size(); i++)
	{
		if(Stars[i]->getActive())
		{
			Stars[i]->update();
		}
	}
}

bool IntroMovie::playing()
{
	return mPlaying;
}

void IntroMovie::countup()
{
	mCounter++;
	if(mCounter==1)
	{
		mStixWalk.setPosition(sf::Vector2f(0, 608));
		mDoor2Open.setActive(true);
		mDoorClose.setActive(false);
		mMeanix.setActive(true);
	}
	else if(mCounter==2)
	{
		mMeanix.setActive(false);
		mMeanixStill.setActive(true);
	}
}

void IntroMovie::endit()
{
	mPlaying=false;
}