#include "BankMovie.h"
#include <iostream>

BankMovie::BankMovie():
mWindow(Window::getWindow()),
	mExclMark(Animation("Excl", 100, 1), sf::Vector2f(1060, 330), false, false),
	mLights1(Animation("PoliceLight", 100, 8), sf::Vector2f(204, 236), false, true),
	mLights2(Animation("PoliceLight", 100, 8), sf::Vector2f(501, 236), false, true),
	mLights3(Animation("PoliceLight", 100, 8), sf::Vector2f(801, 236), false, true),
	mPolice(Animation("PoliceStill", 100, 1), sf::Vector2f(666, 531), false, false),
	mStix(Animation("StixWhole", 100, 1), sf::Vector2f(844, 574), false, false),
	mStixSad(Animation("StixSad", 100, 1), sf::Vector2f(844, 574), false, false),
	mJudge(Animation("JudgeAni", 100, 8), sf::Vector2f(1140, 280), false, true)
{
	mBackground=TextureManager::getSprite("CinemaBG3");
	mBackground2=TextureManager::getSprite("CinemaBG4");
	mPlaying=true;
	mCounter=0;
	mTime=0;
	mColor=sf::Color(255, 255, 255, 255);
	Music::stopMusic();

	mStars.push_back(&mExclMark);
	mStars.push_back(&mLights1);
	mStars.push_back(&mLights2);
	mStars.push_back(&mLights3);
	mStars.push_back(&mPolice);
	mStars.push_back(&mStix);
	mStars.push_back(&mStixSad);
	mStars.push_back(&mJudge);
}
void BankMovie::update()
{
	mTime++;
	if(mCounter==0)
		BankMovie::act();
	else if(mCounter==1)
		BankMovie::act2();
	else
		mPlaying=false;

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
	if(mCounter==0)
	{
		mWindow.draw(mBackground);
	}
	else if(mCounter==1)
	{
		mBackground2.setColor(mColor);
		mWindow.draw(mBackground2);
	}

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
	if(mCounter==1)
	{
		mLights1.setActive(false);
		mLights2.setActive(false);
		mLights3.setActive(false);
		mTime=0;
		mColor=sf::Color(255, 255, 255, 255);
		mExclMark.setActive(false);
	}
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
		mCounter++;
		mLights1.setActive(false);
		mLights2.setActive(false);
		mLights3.setActive(false);
		mTime=0;
		mColor=sf::Color(255, 255, 255, 255);
	}
}
void BankMovie::act2()
{
	if(mTime<100)
	{
		mColor=sf::Color(255, 255, 255, 255*(mTime/100));
		mJudge.setActive(true);
		mPolice.setActive(true);
		mStix.setActive(true);
	}
	else if(mTime<200)
	{
	
	}
	else if(mTime<400)
	{
		Sound::playSound("MeanixTalkNormal");
	}
	else if(mTime<500)
	{
		Sound::playSound("StixTalkSad");
		mStix.setActive(false);
		mStixSad.setActive(true);
	}
	else if(mTime<800)
	{
	
	}
	else if(mTime>800)
	{
		mCounter++;
	}
}