#include "Menu.h"
#include "StateInput.h"
#include "Window.h"

Menu::Menu(): mStateInput(StateInput::getInstance()),
			mBackground("Main", 1, 1),
			mNewGame("NewGame", 1, 2),
			mOptions("Options", 1, 2),
			mQuit("Quit", 1, 2),
			mBlip("Blip", 1, 1),
			mWindow(Window::getWindow()),
			mStatus(0),
			mBlipPos(240, 150),
			currentSelection(&mNewGame)

{
	sf::Vector2f tempPos(mWindow.getSize().x/2-mBackground.getSprite().getGlobalBounds().width/2, 0);
	mBackground.setPosition(tempPos);
	mNewGame.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 150));
	mOptions.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 250));
	mQuit.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 350));
	mBlipPos +=tempPos;
	mBlip.setPosition(mBlipPos);

	mNewGame.setAnimate(false);
	mOptions.setAnimate(false);
	mQuit.setAnimate(false);
	
}

Menu::~Menu()
{}

void Menu::update()
{
	if(!mStateInput.getMenuStatus())
		mStateInput.changeMenu();
	if(mStatus == 0)
		currentSelection = &mNewGame;
	else if(mStatus == 1)
		currentSelection = &mOptions;
	else if(mStatus == 2)
		currentSelection = &mQuit;
	currentSelection->setCurrentFrame(1);
	currentSelection->update();
}

void Menu::render()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(mBackground.getSprite());
	mWindow.draw(mNewGame.getSprite());
	mWindow.draw(mOptions.getSprite());
	mWindow.draw(mQuit.getSprite());
	mWindow.draw(mBlip.getSprite());
	mWindow.display();
}



void Menu::input()
{
	int mChoices = 2;
		//if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (mStatus < mChoices))

		if((Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::S) && (mStatus < mChoices))
		{
			mBlipPos.y += 100;
			mBlip.setPosition(mBlipPos);
			mStatus++;
			currentSelection->setCurrentFrame(0);
			currentSelection->update();
		}
		//else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (mStatus > 0 ))
		else if((Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::W) && (mStatus > 0))
		{			
			if(mStatus > 0)
				mBlipPos.y -= 100;
			mBlip.setPosition(mBlipPos);
			mStatus--;
			currentSelection->setCurrentFrame(0);
			currentSelection->update();
		}
//		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		else if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::Return)
		{
			if(mStatus == 0)
				mStateInput.changeState("Game");
			else if(mStatus == 1)
				mStateInput.changeState("Option");
			else if(mStatus == 2)
				mWindow.close();
		}
}