#include "Option.h"
#include "StateInput.h"
#include "Window.h"
#include "MenuClock.h"

Option::Option(): mStateInput(StateInput::getInstance()),
			mMainBackground("Main", 1, 1),
			mInGameBackground("Ingame", 1, 1),
			mAudio("Audio", 1, 2),
			mControls("Controls", 1, 2),
			mBack("Back", 1, 2),
			mBlip("Blip", 1, 1),
			mWindow(Window::getWindow()),
			mStatus(0),
			mBlipPos(240, 150),
			currentBackground(&mMainBackground),
			currentSelection(&mAudio)
{
	sf::Vector2f tempPos(mWindow.getSize().x/2-mMainBackground.getSprite().getGlobalBounds().width/2, 0);
	sf::Vector2f tempPos2(mWindow.getSize().x/2-mInGameBackground.getSprite().getGlobalBounds().width/2, 0);
	mMainBackground.setPosition(tempPos);
	mInGameBackground.setPosition(tempPos2);
	mAudio.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 150));
	mControls.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 250));
	mBack.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 350));
	mBlipPos +=tempPos;
	mBlip.setPosition(mBlipPos);

	mAudio.setAnimate(false);
	mControls.setAnimate(false);
	mBack.setAnimate(false);
}

Option::~Option()
{}

void Option::update()
{
	if(StateInput::getMenuStatus())
		currentBackground = &mMainBackground;
	else if(!StateInput::getMenuStatus())
		currentBackground = &mInGameBackground;
	if(mStatus == 0)
		currentSelection = &mAudio;
	else if(mStatus == 1)
		currentSelection = &mControls;
	else if(mStatus == 2)
		currentSelection = &mBack;
	currentSelection->setCurrentFrame(1);
	currentSelection->update();
		
	input();
}

void Option::render()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(currentBackground->getSprite());
	mWindow.draw(mAudio.getSprite());
	mWindow.draw(mControls.getSprite());
	mWindow.draw(mBack.getSprite());
	mWindow.draw(mBlip.getSprite());
	mWindow.display();
}

void Option::input()
{
	int mChoices = 2;
	double mDelay = 0.15;
	float mTimer = MenuClock::getClock().getElapsedTime().asSeconds();
	if(mTimer > mDelay)
	{
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (mStatus < mChoices))
		{
			mBlipPos.y += 100;
			mBlip.setPosition(mBlipPos);
			mStatus++;
			currentSelection->setCurrentFrame(0);
			currentSelection->update();
		}
		else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (mStatus > 0 ))
		{			
			if(mStatus > 0)
				mBlipPos.y -= 100;
			mBlip.setPosition(mBlipPos);
			mStatus--;
			currentSelection->setCurrentFrame(0);
			currentSelection->update();
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if(mStatus == 0)
				mStateInput.changeState("Audio");
			else if(mStatus == 1)
				mStateInput.changeState("Controls");
			else if(mStatus == 2)
				mStateInput.changeState("Last");
		}
		MenuClock::restartClock();
	}
}