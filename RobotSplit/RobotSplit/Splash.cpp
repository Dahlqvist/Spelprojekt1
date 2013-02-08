#include "Splash.h"
#include "StateInput.h"
#include "Window.h"
#include "TextureManager.h"

bool Splash::mStatus;

Splash::Splash():
	mStateInput(StateInput::getInstance()),
	mWindow(Window::getWindow()),
	mWatermelon("Watermelon", 1, 1),
	mConcept1("RobotSplitConcept1", 1, 1),
	currentAnimation(&mWatermelon)	
{
	mTime.restart();
	mStatus = false;
}

Splash::~Splash()
{
	delete currentAnimation;
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
	mWindow.draw(currentAnimation->getSprite());
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