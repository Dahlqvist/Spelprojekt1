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
			mBlipPos(240, 150)

{
	sf::Vector2f tempPos(mWindow.getSize().x/2-mBackground.getSprite().getGlobalBounds().width/2, 0);
	mBackground.setPosition(tempPos);
	mResume.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 150));
	mOptions.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 250));
	mQuit.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 350));
	mBlipPos +=tempPos;
	mBlip.setPosition(mBlipPos);
}

InGameMenu::~InGameMenu()
{}

void InGameMenu::update()
{
	if(mStateInput.getMenuStatus())
		mStateInput.changeMenu();
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
	double mDelay = 0.15;
	float mTimer = MenuClock::getClock().getElapsedTime().asSeconds();
	if(mTimer > mDelay)
	{
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (mStatus < mChoices))
		{
			mBlipPos.y += 100;
			mBlip.setPosition(mBlipPos);
			mStatus++;
		}
		else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (mStatus > 0 ))
		{			
			if(mStatus > 0)
				mBlipPos.y -= 100;
			mBlip.setPosition(mBlipPos);
			mStatus--;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if(mStatus == 0)
				mStateInput.changeState("Last");
			else if(mStatus == 1)
				mStateInput.changeState("Option");
			else if(mStatus == 2)
				mStateInput.changeState("QuitToMenu");
		}
		MenuClock::restartClock();
	}
}