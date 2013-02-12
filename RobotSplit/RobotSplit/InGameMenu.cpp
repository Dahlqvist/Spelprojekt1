#include "InGameMenu.h"
#include "StateInput.h"
#include "Window.h"
#include "MenuClock.h"

InGameMenu::InGameMenu(): mStateInput(StateInput::getInstance()),
			mBackground("Ingame", 1, 1),
			mResume("Resume", 1, 1),
			mOptions("Options", 1, 1),
			mQuit("Quit", 1, 1),
			mBlip("Blip", 1, 1),
			mWindow(Window::getWindow()),
			mStatus(0),
			mBlipPos(240, 150),
			mDelay(0.1),
			mTimer(0)

{
	mResume.setPosition(sf::Vector2f(300, 150));
	mOptions.setPosition(sf::Vector2f(300, 250));
	mQuit.setPosition(sf::Vector2f(300, 350));
	mBlip.setPosition(mBlipPos);
}

InGameMenu::~InGameMenu()
{}

void InGameMenu::update()
{
	input();
}

void InGameMenu::render()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(mBackground.getSprite());
	mWindow.draw(mResume.getSprite());
	mWindow.draw(mOptions.getSprite());
	mWindow.draw(mQuit.getSprite());
	mWindow.draw(mBlip.getSprite());
	mWindow.display();
}

void InGameMenu::input()
{
	int mChoices = 2;
	mTimer = MenuClock::getClock().getElapsedTime().asSeconds();
	if(mTimer > mDelay)
	{
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (mStatus < mChoices))
		{
			mBlipPos.y += 100;
			mBlip.setPosition(mBlipPos);
			mStatus++;
			mDelay = 0.15;
		}
		else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (mStatus > 0 ))
		{			
			if(mStatus > 0)
				mBlipPos.y -= 100;
			mBlip.setPosition(mBlipPos);
			mStatus--;
			mDelay = 0.15;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if(mStatus == 0)
				mStateInput.changeState("Last");
			else if(mStatus == 1)
				mStateInput.changeState("Menu");
			else if(mStatus == 2)
				mWindow.close();
			mDelay = 2;
		}
		MenuClock::restartClock();
	}
}