#include "Splash.h"
#include "StateInput.h"
#include "Window.h"
#include "TextureManager.h"
#include "Animation.h"

Splash::Splash():
	mStateInput(StateInput::getInstance()),
	mWindow(Window::getWindow()),
	mWatermelon("Watermelon"

{
	mTime.restart();
}

Splash::~Splash()
{}

void Splash::update()
{
	if(mTime.getElapsedTime().asSeconds() < 10)
	{
		currentSprite = &mWatermelon;
	}
	else if(mTime.getElapsedTime().asSeconds() > 10 )
	{
		currentSprite = &mConcept1;
	}
	//När Splash-screen är klar skall menu visas
	//mStateInput.changeState("Menu");	
}

sf::Sprite& Splash::returnSprite()
{
	return 

void Splash::render()
{

}