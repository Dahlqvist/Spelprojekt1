#include "Menu.h"
#include "StateInput.h"
#include "Window.h"
#include "TextureManager.h"

Menu::Menu(): mStateInput(StateInput::getInstance()),
			mBackground("Main", 1, 1),
			mNewGame("NewGame", 1, 2),
			mOptions("Options", 1, 2),
			mQuit("Quit", 1, 2),
			mBlip("Blip", 1, 1),
			mYes("Yes", 1, 2),
			mNo("No", 1, 2),
			mWindow(Window::getWindow()),
			mStatus(0),
			mChoices(0),
			mBlipPos(240, 150),
			currentSelection(&mNewGame),
			mSure(false),
			mShowSure(false)

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
	mYes.setAnimate(false);
	mNo.setAnimate(false);
	
}

Menu::~Menu()
{}

void Menu::update()
{
	if(!mStateInput.getMenuStatus())
		mStateInput.changeMenu();
	if(mStatus == 0)
	{
		if(mShowSure)
			currentSelection = &mNo;
		else
			currentSelection = &mNewGame;
	}
	else if(mStatus == 1)
	{
		if(mShowSure)
			currentSelection = &mYes;
		else
			currentSelection = &mOptions;
	}
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
	if(mShowSure)
		sure(false);
	else
	{
		mWindow.draw(mBlip.getSprite());
		mWindow.display();
	}
}



void Menu::input()
{
	int distance = 100;
	if(mShowSure)
	{
		mChoices = 1;
		distance = 55;
	}
	else
		mChoices = 2;

	if((Window::getEvent().type == sf::Event::KeyPressed && (Window::getEvent().key.code == sf::Keyboard::S ||Window::getEvent().key.code == sf::Keyboard::Down)) && (mStatus < mChoices))
	{
			mBlipPos.y += distance;
			mBlip.setPosition(mBlipPos);
			currentSelection->setCurrentFrame(0);
			currentSelection->update();
			mStatus++;
	}
	else if((Window::getEvent().type == sf::Event::KeyPressed && (Window::getEvent().key.code == sf::Keyboard::W || Window::getEvent().key.code == sf::Keyboard::Up)) && (mStatus > 0))
	{			
		mBlipPos.y -= distance;
		mBlip.setPosition(mBlipPos);
		currentSelection->setCurrentFrame(0);
		currentSelection->update();
		mStatus--;
	}
	else if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::Return)
	{
		if(mStatus == 0)
		{
			if(mShowSure)
			{
				mStatus = 2;
				mShowSure = false;
				mBlipPos = sf::Vector2f(mQuit.getSprite().getPosition().x - 60, mQuit.getSprite().getPosition().y);
				mBlip.setPosition(mBlipPos);
				currentSelection ->setCurrentFrame(0);
				currentSelection ->update();
				update();				
			}
			else
			{
				mStateInput.changeState("Game");
				mStateInput.changeState("Intro");
			}
		}
		else if(mStatus == 1)
		{
			if(mShowSure)
				mWindow.close();
			else
				mStateInput.changeState("Option");
		}
		else if(mStatus == 2)
		{
			mShowSure = true;
			mStatus = 0;
			
			mStateInput.changeState("End");
			sure(true);
		}
	}
}

void Menu::sure(bool b)
{
	sf::Sprite tempBackground = mBackground.getSprite();
	sf::Sprite tempSure = TextureManager::getSprite("Sure");

	tempBackground.setPosition(mWindow.getView().getCenter());
	tempBackground.setScale(0.5, 0.5);

	tempSure.setPosition(sf::Vector2f(tempBackground.getPosition().x + 125, tempBackground.getPosition().y + 75));
	if(b)
	{
		mBlipPos = sf::Vector2f(tempSure.getPosition().x, tempSure.getPosition().y + tempSure.getGlobalBounds().height +20);
		mBlip.setPosition(mBlipPos);
	}

	mNo.setPosition(sf::Vector2f(mBlip.getSprite().getPosition().x + mBlip.getSprite().getGlobalBounds().width + 20, tempSure.getPosition().y + tempSure.getGlobalBounds().height + 20));
	mYes.setPosition(sf::Vector2f(mNo.getSprite().getPosition().x, mNo.getSprite().getPosition().y + mNo.getSprite().getGlobalBounds().height + 10));
	

	mWindow.draw(tempBackground);
	mWindow.draw(tempSure);
	mWindow.draw(mYes.getSprite());
	mWindow.draw(mNo.getSprite());
	mWindow.draw(mBlip.getSprite());
	mWindow.display();
}