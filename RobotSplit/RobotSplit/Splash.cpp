#include "Splash.h"
#include "StateInput.h"
#include "Window.h"
#include "TextureManager.h"


Splash::Splash():
	mStateInput(StateInput::getInstance()),
	mWindow(Window::getWindow()),
	mWatermelon("Watermelon", 1, 1),
	mConcept1("RobotSplitConcept1", 1, 1),
	currentAnimation(&mWatermelon)
	
{
	mTime.restart();
}

Splash::~Splash()
{
	delete currentAnimation;
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
		mStateInput.changeState("Menu");
	//När Splash-screen är klar skall menu visas
	//mStateInput.changeState("Menu");	
}

void Splash::render()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(currentAnimation->getSprite());
	mWindow.display();
}