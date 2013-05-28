#include "IntroMovie.h"

IntroMovie::IntroMovie():
mWindow(Window::getWindow()),
	mStixWalk(Animation("StixWalk", 100, 8), sf::Vector2f(0, 540), true, true),
	mStixExt(Animation("StixExt", 70, 17), sf::Vector2f(0, 0), false, false),
	mStixExtStill(Animation("StixExtStill", 100, 1), sf::Vector2f(510, 577), false, false),
	mStixJumpDown(Animation("StixExt2", 70, 17), sf::Vector2f(510, 1577), false, false),
	mDoorOpen(Animation("DoorOpen", 100, 8), sf::Vector2f(898, 419), false, false),
	mDoorClose(Animation("DoorClose", 100, 8), sf::Vector2f(898, 419), false, false),
	mDoor2Open(Animation("Door2Open", 100, 8), sf::Vector2f(0, 503), false, false),
	mDoor2Close(Animation("Door2Close", 100, 8), sf::Vector2f(0, 503), false, false),
	mMeanix(Animation("MeanixBank", 100, 8), sf::Vector2f(806, 576), false, true),
	mMeanixStill(Animation("MeanixBank3", 100, 1), sf::Vector2f(806, 576), false, false),
	mMeanixHat(Animation("MeanixBank4", 100, 28), sf::Vector2f(791, 0), false, false)
{
	mCounter=0;
	mPlaying=true;
	mBackground=TextureManager::getSprite("CinemaBG1");
	mBackground2=TextureManager::getSprite("CinemaBG2");

	mDialogs.push_back(new DialogueBox(sf::Vector2f(600, 300), "DialogueBox1", "Glad you could make it and welcome to my \nhumble office here at X-inaem", false, false, "Dia1"));
	mDialogs.push_back(new DialogueBox(sf::Vector2f(300, 400), "DialogueBox1", "Thank you good sir, lets skip to business \nand focus on the job.", false, false, "Dia1"));
	mDialogs.push_back(new DialogueBox(sf::Vector2f(600, 300), "DialogueBox1", "Straight to the point eh, I like it. What \nI need you to do is test out the new security \nsystem at the sector bank; I sure hope you \nwon't make it, if you know what I mean. \nHar-har", false, false, "Dia1"));
	mDialogs.push_back(new DialogueBox(sf::Vector2f(300, 400), "DialogueBox1", "We will see... And the payment is as instructed \nin the worker holos", false, false, "Dia1"));
	mDialogs.push_back(new DialogueBox(sf::Vector2f(600, 300), "DialogueBox1", "Of course, we are offering you the payment should \nyou fail or not. The only thing we need \nis that you use your talents to try and \nbreak the security for the bank, nothing \nless and nothing more.", false, false, "Dia1"));
	mDialogs.push_back(new DialogueBox(sf::Vector2f(300, 400), "DialogueBox1", "I'm on it, when can I start?", false, false, "Dia1"));
	mDialogs.push_back(new DialogueBox(sf::Vector2f(600, 300), "DialogueBox1", "Right now! Good luck Stix!", false, false, "Dia1"));

	mStars.push_back(&mDoor2Open);
	mStars.push_back(&mDoorOpen);
	mStars.push_back(&mStixWalk);
	mStars.push_back(&mStixExt);
	mStars.push_back(&mStixExtStill);
	mStars.push_back(&mStixJumpDown);
	mStars.push_back(&mDoorClose);
	mStars.push_back(&mDoor2Close);
	mStars.push_back(&mMeanix);
	mStars.push_back(&mMeanixStill);
	mStars.push_back(&mMeanixHat);
	Music::loadMusic("Music/tutorial_3.wav");
	mTalk=false;
	mDia=0;
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

	for(unsigned int i=0; i<mStars.size(); i++)
	{
		if(mStars[i]->getActive())
		{
			mWindow.draw(mStars[i]->getSprite());
		}
	}
	for(unsigned int i=0; i<mDialogs.size(); i++)
	{
		if(mDialogs[i]->getVisible())
		{
			mWindow.draw(mDialogs[i]->getSprite());
			mWindow.draw(mDialogs[i]->getText());
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
			mStixWalk.setPosition(sf::Vector2f(-64, 608));
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
	Music::playMusic();
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
		if(mCounter-2<mDialogs.size())
		{
			for(unsigned int i=0; i<mDialogs.size(); i++)
			{
				if(mCounter-2==i)
				{
					mDialogs[i]->activate();
					if(i%2==1 && mTalk==false)
					{
						Sound::playSound("StixTalkNormal");
						Sound::stopSound("MeanixTalkNormal");
						mTalk=true;
					}
					else if(mTalk==false)
					{	
						Sound::playSound("MeanixTalkNormal");
						Sound::stopSound("StixTalkNormal");
						mTalk=true;
					}
				}
				else
				{
					mDialogs[i]->deactivate();
				}
			}
		}
		else
		{
			if(mStixJumpDown.getDone()==false && mMeanixHat.getDone()==false)
			{
				mDialogs[mDialogs.size()-1]->deactivate();
				mStixExtStill.setActive(false);
				mStixExt.setActive(false);
				mStixJumpDown.setActive(true);
				mMeanixStill.setActive(false);
				mMeanixHat.setActive(true);
			}
			else if(mStixJumpDown.getDone()==true && mMeanixHat.getDone()==true)
			{
				mPlaying=false;
			}
		}
	}
	for(unsigned int i=0; i<mStars.size(); i++)
	{
		if(mStars[i]->getActive())
		{
			mStars[i]->update();
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
		mStixWalk.setPosition(sf::Vector2f(-64, 608));
		mDoor2Open.setActive(true);
		mDoorClose.setActive(false);
		mMeanix.setActive(true);
	}
	else if(mCounter==2)
	{
		mStixExt.setActive(false);
		mStixWalk.setActive(false);
		mDoor2Open.setActive(false);
		mDoor2Close.setActive(false);
		mStixExtStill.setActive(true);
		mMeanix.setActive(false);
		mMeanixStill.setActive(true);
		//mBackground2=TextureManager::getSprite("Tutorial1Office");

	}
	else
	{
		mTalk=false;
	}
}

void IntroMovie::endit()
{
	mPlaying=false;
}