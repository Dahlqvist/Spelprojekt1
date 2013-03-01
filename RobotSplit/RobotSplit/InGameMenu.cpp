#include "InGameMenu.h"
#include "StateInput.h"
#include "Window.h"
#include "Game.h"
#include "Sound.h"
#include "Music.h"

InGameMenu::InGameMenu(): mStateInput(StateInput::getInstance()), 
			mBackground("Ingame", 1, 1),
			mResume("Resume", 1, 2),
			mOptions("Options", 1, 2),
			mQuit("Quit", 1, 2),
			mBlip("Blip", 1, 1),
			mYes("Yes", 1, 2),
			mNo("No", 1, 2),
			mWindow(Window::getWindow()),
			mStatus(0),
			mChoices(0),
			mBlipPos(240, 150),
			currentSelection(&mResume),
			mShowSure(false)

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
	mYes.setAnimate(false);
	mNo.setAnimate(false);
}

InGameMenu::~InGameMenu()
{}

void InGameMenu::update()
{
	if(mStateInput.getMenuStatus())
		mStateInput.changeMenu();
	if(mStatus == 0)
	{
		if(mShowSure)
			currentSelection = &mYes;
		else
			currentSelection = &mResume;
	}
	else if(mStatus == 1)
	{
		if(mShowSure)
			currentSelection = &mNo;
		else
			currentSelection = &mOptions;
	}
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
	
	if(mShowSure)
		sure(false);
	else
	{
		mWindow.draw(mBlip.getSprite());
		mWindow.display();
	}
}

void InGameMenu::input()
{
	if(!mShowSure)
		mChoices = 2;
	if((Window::getEvent().type == sf::Event::KeyPressed && (Window::getEvent().key.code == sf::Keyboard::S ||Window::getEvent().key.code == sf::Keyboard::Down)) && (mStatus < mChoices))
	{
		mBlipPos.y += 100;
		mBlip.setPosition(mBlipPos);
		currentSelection->setCurrentFrame(0);
		currentSelection->update();
		mStatus++;
	}
	else if((Window::getEvent().type == sf::Event::KeyPressed && (Window::getEvent().key.code == sf::Keyboard::W || Window::getEvent().key.code == sf::Keyboard::Up)) && (mStatus > 0))
	{			
		mBlipPos.y -= 100;
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
				mStatus = 0;
				Sound::stopSound("Lava");
				Music::stopMusic();
				mStateInput.changeState("QuitToMenu");
			}
			else
				mStateInput.changeState("Last");
		}
		else if(mStatus == 1)
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
				mStateInput.changeState("Option");
		}
		else if(mStatus == 2)
		{
			/*mBlipPos.y -= (100*mStatus);
			mBlip.setPosition(mBlipPos);
			currentSelection->setCurrentFrame(0);
			currentSelection->update();*/
			mShowSure = true;
			mStatus = 0;
			sure(true);
						
		}
	}
	else if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::Escape)
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
			mBlipPos.y -= (100*mStatus);
			mBlip.setPosition(mBlipPos);
			currentSelection->setCurrentFrame(0);
			currentSelection->update();
			mStatus = 0;
			mStateInput.changeState("Last");
		}
	}
}

void InGameMenu::sure(bool b)
{
	sf::Sprite tempBackground = mBackground.getSprite();
	sf::Sprite tempSure = TextureManager::getSprite("Sure");
	mChoices = 1;

	tempBackground.setPosition(mWindow.getView().getCenter());
	tempBackground.setScale(0.5, 0.5);

	tempSure.setPosition(sf::Vector2f(tempBackground.getPosition().x + 125, tempBackground.getPosition().y + 75));
	if(b)
	{
		//mBlip.setPosition(sf::Vector2f(tempSure.getPosition().x, tempSure.getPosition().y + tempSure.getGlobalBounds().height +20));
		mBlipPos = sf::Vector2f(tempSure.getPosition().x, tempSure.getPosition().y + tempSure.getGlobalBounds().height +20);
		mBlip.setPosition(mBlipPos);
	}

	mYes.setPosition(sf::Vector2f(mBlip.getSprite().getPosition().x + mBlip.getSprite().getGlobalBounds().width + 20, tempSure.getPosition().y + tempSure.getGlobalBounds().height + 20));
	mNo.setPosition(sf::Vector2f(mYes.getSprite().getPosition().x, mYes.getSprite().getPosition().y + mYes.getSprite().getGlobalBounds().height + 54));

	mWindow.draw(tempBackground);
	mWindow.draw(tempSure);
	mWindow.draw(mYes.getSprite());
	mWindow.draw(mNo.getSprite());
	mWindow.draw(mBlip.getSprite());
	mWindow.display();
}