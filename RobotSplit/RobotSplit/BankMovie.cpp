#include "BankMovie.h"
#include <iostream>

BankMovie::BankMovie():
mWindow(Window::getWindow()),
	mExclMark(Animation("Excl", 100, 1), sf::Vector2f(1060, 330), false, false),
	mLights1(Animation("PoliceLight", 100, 8), sf::Vector2f(204, 236), false, true),
	mLights2(Animation("PoliceLight", 100, 8), sf::Vector2f(501, 236), false, true),
	mLights3(Animation("PoliceLight", 100, 8), sf::Vector2f(801, 236), false, true),
	mPolice(Animation("PoliceStill", 100, 1), sf::Vector2f(590, 531), false, false),
	mPolice2(Animation("PoliceStillLeft", 100, 1), sf::Vector2f(900, 531), false, false),
	mPoliceWalk(Animation("PoliceWalking", 100, 8), sf::Vector2f(0, 531), false, true),
	mPoliceWalk2(Animation("PoliceWalking", 100, 8), sf::Vector2f(200, 531), false, true),
	mStix(Animation("StixWhole", 100, 1), sf::Vector2f(780, 574), false, false),
	mStixWalk(Animation("StixWalk", 100, 8), sf::Vector2f(110, 574), false, true),
	mStixSad(Animation("StixSad", 100, 1), sf::Vector2f(780, 574), false, false),
	mJudge(Animation("JudgeAni", 100, 8), sf::Vector2f(1080, 242), false, true),
	mTrapDoor(Animation("TrapDoor", 70, 15), sf::Vector2f(736, 668), false, false),
	mButton(Animation("Button", 100, 1), sf::Vector2f(1060, 368), false, false),
	mPressButton(Animation("JudgeButton", 70, 11), sf::Vector2f(1060, 242), false, false),
	mFloor(Animation("RattFloor", 100, 1), sf::Vector2f(736, 683), false, false)
{
	mBackground=TextureManager::getSprite("CinemaBG3");
	mBackground2=TextureManager::getSprite("CinemaBG4");
	mPlaying=true;
	mCounter=0;
	mTime=0;
	mColor=sf::Color(255, 255, 255, 255);

	mStars.push_back(&mExclMark);
	mStars.push_back(&mLights1);
	mStars.push_back(&mLights2);
	mStars.push_back(&mLights3);
	mStars.push_back(&mPolice);
	mStars.push_back(&mPolice2);
	mStars.push_back(&mStix);
	mStars.push_back(&mTrapDoor);
	mStars.push_back(&mStixSad);
	mStars.push_back(&mJudge);
	mStars.push_back(&mPoliceWalk);
	mStars.push_back(&mPoliceWalk2);
	mStars.push_back(&mStixWalk);
	mStars.push_back(&mFloor);
	mStars.push_back(&mButton);
	mStars.push_back(&mPressButton);
}
void BankMovie::update()
{
	mTime++;
	if(mCounter==0)
		BankMovie::act();
	else if(mCounter==1)
		BankMovie::act2();
	else if(mCounter==2)
		BankMovie::act3();
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
	else
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
	if(mCounter==2)
	{
		mColor=sf::Color(255, 255, 255, 255);
		mPoliceWalk.setActive(false);
		mPoliceWalk2.setActive(false);
		mStixWalk.setActive(false);
		mStix.setActive(true);
		mPolice.setActive(true);
		mPolice2.setActive(true);
		mTime=0;
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
		mPoliceWalk.setActive(true);
		mPoliceWalk2.setActive(true);
		mStixWalk.setActive(true);
		mJudge.setActive(true);
		mButton.setActive(true);
	}
	else if(mPoliceWalk.getPosition().x<590)
	{
		mPoliceWalk.setPosition(mPoliceWalk.getPosition() + sf::Vector2f(1, 0));
		mPoliceWalk2.setPosition(mPoliceWalk2.getPosition() + sf::Vector2f(1, 0));
		mStixWalk.setPosition(mStixWalk.getPosition() + sf::Vector2f(1, 0));
	}
	else if(mStixWalk.getPosition().x<780)
	{
		mPoliceWalk.setActive(false);
		mPolice.setActive(true);
		mPoliceWalk2.setPosition(mPoliceWalk2.getPosition() + sf::Vector2f(1, 0));
		mStixWalk.setPosition(mStixWalk.getPosition() + sf::Vector2f(1, 0));
	}
	else if(mPoliceWalk2.getPosition().x<900)
	{
		mStixWalk.setActive(false);
		mStix.setActive(true);
		mPoliceWalk2.setPosition(mPoliceWalk2.getPosition() + sf::Vector2f(1, 0));
	}
	else if(mPoliceWalk2.getPosition().x>=900)
	{
		mPoliceWalk2.setActive(false);
		mPolice2.setActive(true);
		mCounter++;
		mTime=0;
	}
}
void BankMovie::act3()
{
	if(mTime<200)
	{
		Sound::playSound("MeanixTalkNormal");
	}
	else if(mTime<400 && mTime>300)
	{
		Sound::playSound("StixTalkSad");
		mStix.setActive(false);
		mStixSad.setActive(true);
	}
	else if(mTime>600 && mTime<1000)
	{
		mJudge.setActive(false);
		mPressButton.setActive(true);
		mButton.setActive(false);
		if(mPressButton.getDone()==true){
			mTrapDoor.setActive(true);
			mFloor.setActive(true);
			if(mTrapDoor.getDone()==true)
			{
				mStixSad.setPosition(mStixSad.getPosition() + sf::Vector2f(0, 3));
				//Music::changeVolume(mMusicVolume);
			}
		}
	}
	else if(mTime>1000)
	{
		mCounter++;
	}
}