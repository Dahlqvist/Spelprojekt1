#include "BankMovie.h"
#include <iostream>

BankMovie::BankMovie():
mWindow(Window::getWindow()),
	mExclMark(Animation("Excl", 100, 1), sf::Vector2f(1060, 330), false, false),
	mLights1(Animation("PoliceLight", 100, 8), sf::Vector2f(204, 236), false, true),
	mLights2(Animation("PoliceLight", 100, 8), sf::Vector2f(501, 236), false, true),
	mLights3(Animation("PoliceLight", 100, 8), sf::Vector2f(801, 236), false, true)
{
	mBackground=TextureManager::getSprite("CinemaBG3");
	mPlaying=true;
	mCounter=0;
	mTime=0;
	mColor=sf::Color(255, 255, 255, 255);

	mStars.push_back(&mExclMark);
	mStars.push_back(&mLights1);
	mStars.push_back(&mLights2);
	mStars.push_back(&mLights3);
}
void BankMovie::update()
{
	mTime++;
	BankMovie::act();
	for(unsigned int i=0; i<mStars.size(); i++)
	{
		if(mStars[i]->getActive())
		{
			mStars[i]->update();
		}
	}
}
void BankMovie::draw()
{
	mWindow.clear();
	mWindow.draw(mBackground);
	for(unsigned int i=0; i<mStars.size(); i++)
	{
		if(mStars[i]->getActive())
		{
			sf::Sprite Temp=mStars[i]->getSprite();
			Temp.setColor(mColor);
			mWindow.draw(Temp);
		}
	}
	mWindow.display();
}
bool BankMovie::playing()
{
	return mPlaying;
}
void BankMovie::countup()
{
	mCounter++;
}
void BankMovie::endit()
{
	mPlaying=false;
}
void BankMovie::act()
{
	//std::cout << mTime << std::endl;
	if(mTime>100 && mTime<200)
	{
		mExclMark.setActive(true);
		Sound::playSound("StixTalkAngry");
	}
	else if(mTime>200 && mTime<300)
	{
		mExclMark.setActive(false);
		mLights1.setActive(true);
	}
	else if(mTime>300 && mTime<400)
	{
		mLights2.setActive(true);
	}
	else if(mTime>400 && mTime<700)
	{
		mLights3.setActive(true);
	}
	else if(mTime>700 && mTime<800)
	{
		mColor=sf::Color(255, 255, 255, 255*(1-(mTime-900)/100));
		mBackground.setColor(mColor);
	}
	else if(mTime>900)
	{
		mPlaying=false;
	}
}