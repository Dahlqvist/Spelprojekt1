#include "Splash.h"
#include "TextureManager.h"
#include <iostream>
bool Splash::mStatus;


Splash::Splash():
	mWindow(Window::getWindow()),
	mSplash("Watermelon", 1, 1),
	currentAnimation(&mSplash)
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
	mSplash.update();
}

void Splash::render()
{
	mWindow.clear(sf::Color::Black);
	sf::Sprite Temp=mSplash.getSprite();
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

void Splash::runSplash(std::string sprite, int timePerFrame, int nrFrames)
{
	mSplash = Animation(sprite, timePerFrame, nrFrames);
}

bool Splash::getStatus()
{
	return mStatus;
}