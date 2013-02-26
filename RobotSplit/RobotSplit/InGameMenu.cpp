#include "InGameMenu.h"
#include "StateInput.h"
#include "Window.h"
#include "MenuClock.h"
#include "Game.h"

InGameMenu::InGameMenu(): mStateInput(StateInput::getInstance()), 
			mBackground("Ingame", 1, 1),
			mResume("Resume", 1, 2),
			mOptions("Options", 1, 2),
			mQuit("Quit", 1, 2),
			mBlip("Blip", 1, 1),
			mWindow(Window::getWindow()),
			mStatus(0),
			mBlipPos(240, 150),
			currentSelection(&mResume)

{
	sf::Vector2f tempPos(mWindow.getSize().x/2-mBackground.getSprite().getGlobalBounds().width/2, 0);
	mBackground.setPosition(tempPos);
	mResume.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 150));
	mOptions.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 250));
	mQuit.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 350));
	mBlipPos +=tempPos;
	mBlip.setPosition(mBlipPos);

	mResume.setAnimate(false);
	mOptions.setAnimate(false);
	mQuit.setAnimate(false);
}

InGameMenu::~InGameMenu()
{}

void InGameMenu::update()
{
	if(mStateInput.getMenuStatus())
		mStateInput.changeMenu();
	if(mStatus == 0)
		currentSelection = &mResume;
	else if(mStatus == 1)
		currentSelection = &mOptions;
	else if(mStatus == 2)
		currentSelection = &mQuit;
	currentSelection->setCurrentFrame(1);
	currentSelection->update();
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
		if((Window::getEvent().type == sf::Event::KeyPressed && (Window::getEvent().key.code == sf::Keyboard::S ||Window::getEvent().key.code == sf::Keyboard::Down)) && (mStatus < mChoices))
		{
			mBlipPos.y += 100;
			mBlip.setPosition(mBlipPos);
			mStatus++;
			currentSelection->setCurrentFrame(0);
			currentSelection->update();
		}
		else if((Window::getEvent().type == sf::Event::KeyPressed && (Window::getEvent().key.code == sf::Keyboard::W || Window::getEvent().key.code == sf::Keyboard::Up)) && (mStatus > 0))
		{			
			if(mStatus > 0)
				mBlipPos.y -= 100;
			mBlip.setPosition(mBlipPos);
			mStatus--;
			currentSelection->setCurrentFrame(0);
			currentSelection->update();
		}
		else if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::Return)
		{
			if(mStatus == 0)
				mStateInput.changeState("Last");
			else if(mStatus == 1)
				mStateInput.changeState("Option");
			else if(mStatus == 2)
			{
				mBlipPos.y -= (100*mStatus);
				mBlip.setPosition(mBlipPos);
				currentSelection->setCurrentFrame(0);
				currentSelection->update();
				mStatus = 0;
				mStateInput.changeState("QuitToMenu");				
			}
		}
}