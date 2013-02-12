#include "Splash.h"
#include "StateInput.h"
#include "Window.h"
#include "TextureManager.h"
#include <iostream>
bool Splash::mStatus;

Splash::Splash():
	mStateInput(StateInput::getInstance()),
	mWindow(Window::getWindow()),
	mWatermelon("Watermelon", 1, 1),
	mConcept1("RobotSplitConcept1", 1, 1),
	currentAnimation(&mWatermelon)	
{
	mTime.restart();
	//mConcept1.getSprite().scale(bilden/fönstret)
	mStatus = false;
}

Splash::~Splash()
{
//	delete currentAnimation;
}

Splash& Splash::getInstance()
{
	static Splash splash;
	return splash;
}

void Splash::update()
{
	if(mTime.getElapsedTime().asSeconds() < 3)
	{
		currentAnimation = &mWatermelon;
	}
	else if(mTime.getElapsedTime().asSeconds() > 3 )
	{
		currentAnimation = &mConcept1;
	}

	if(mTime.getElapsedTime().asSeconds() > 6 )
		runSplash(false);
}

void Splash::render()
{
	mWindow.clear(sf::Color::Black);
	sf::Sprite Temp=currentAnimation->getSprite();
	sf::View tempView = mWindow.getView();
	sf::Vector2u p = mWindow.getSize();
	float ratio = mWindow.getSize().y/Temp.getGlobalBounds().height;
	float x = (mWindow.getSize().x - (Temp.getGlobalBounds().width*ratio)) / 2;
	float y = (mWindow.getSize().y - (Temp.getGlobalBounds().height*ratio))/2;
	Temp.setPosition(x, y);
	Temp.scale(ratio, ratio);
	
	
	mWindow.draw(Temp);
	mWindow.display();
}

void Splash::runSplash(bool status)
{
	mStatus = status;
}

bool Splash::getStatus()
{
	return mStatus;
}