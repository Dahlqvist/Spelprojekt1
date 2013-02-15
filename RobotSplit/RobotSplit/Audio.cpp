#include "Audio.h"

#include "StateInput.h"
#include "Window.h"
#include "MenuClock.h"
#include "Music.h"
#include "Sound.h"

Audio::Audio(): mStateInput(StateInput::getInstance()),
			mMainBackground("Main", 1, 1),
			mInGameBackground("Ingame", 1, 1),
			mEffectVolyme("EffectVolym", 1, 2),
			mMusicVolyme("MusicVolym", 1, 2),
			mEffectMuteChecked("EffectMuteChecked", 1, 2),
			mEffectMuteUnchecked("EffectMuteUnChecked", 1, 2),
			mMusicMuteChecked("MusicMuteChecked", 1, 2),
			mMusicMuteUnchecked("MusicMuteUnChecked", 1, 2),
			mBack("Back", 1, 2),
			mBlip("Blip", 1, 1),
			mWindow(Window::getWindow()),
			mStatus(0),
			mBlipPos(240, 150),
			currentBackground(&mMainBackground),
			currentSelection(&mBack),
			mEVolyme(100),
			mMVolyme(100),
			mChangeVolyme(false)
{
	sf::Vector2f tempPos(mWindow.getSize().x/2-mMainBackground.getSprite().getGlobalBounds().width/2, 0);
	sf::Vector2f tempPos2(mWindow.getSize().x/2-mInGameBackground.getSprite().getGlobalBounds().width/2, 0);
	mMainBackground.setPosition(tempPos);
	mInGameBackground.setPosition(tempPos2);
	mEffectVolyme.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 150));
	mMusicVolyme.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 250));
	mEffectMuteUnchecked.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 350));
	mMusicMuteUnchecked.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 450));
	mBack.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 550));
	mBlipPos +=tempPos;
	mBlip.setPosition(mBlipPos);

	mEffectMuteChecked.setAnimate(false);
	mEffectMuteUnchecked.setAnimate(false);
	mEffectVolyme.setAnimate(false);
	mMusicMuteChecked.setAnimate(false);
	mMusicMuteUnchecked.setAnimate(false);
	mMusicVolyme.setAnimate(false);
	mBack.setAnimate(false);
}

Audio::~Audio()
{}

void Audio::update()
{
	if(StateInput::getMenuStatus())
		currentBackground = &mMainBackground;
	else if(!StateInput::getMenuStatus())
		currentBackground = &mInGameBackground;
	if(mStatus == 0)
		currentSelection = &mEffectVolyme;
	else if(mStatus == 1)
		currentSelection = &mMusicVolyme;
	else if(mStatus == 2)
		currentSelection = &mEffectMuteUnchecked;
	else if(mStatus == 3)
		currentSelection = &mMusicMuteUnchecked;
	else if(mStatus == 4)
		currentSelection = &mBack;
	currentSelection->setCurrentFrame(1);
	currentSelection->update();
	input();
}

void Audio::render()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(currentBackground->getSprite());
	mWindow.draw(mEffectVolyme.getSprite());
	mWindow.draw(mMusicVolyme.getSprite());
	mWindow.draw(mEffectMuteUnchecked.getSprite());
	mWindow.draw(mMusicMuteUnchecked.getSprite());
	mWindow.draw(mBack.getSprite());
	mWindow.draw(mBlip.getSprite());
	mWindow.display();
}

void Audio::input()
{
	int mChoices = 4;
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
			{
				mChangeVolyme = !mChangeVolyme;
				Sound::changeVolume(mEVolyme);
			}
			else if(mStatus == 1)
			{
				mChangeVolyme = !mChangeVolyme;
				Music::changeVolyme(mMVolyme);
			}
			else if(mStatus == 2)
			{}
			else if(mStatus == 3)
			{}
			else if(mStatus == 4)
				mStateInput.changeState("Last");
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && mChangeVolyme == true)
		{
			lowerVolyme();
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mChangeVolyme == true)
		{
			raiseVolyme();
		}
		MenuClock::restartClock();
	}
}

void Audio::raiseVolyme()
{
	if(mStatus == 0)
	{
		if(mEVolyme < 100)
			mEVolyme++;
	}
	else if(mStatus == 1)
	{
		if(mMVolyme < 100)
			mMVolyme++;
	}
}

void Audio::lowerVolyme()
{
	if(mStatus == 0)
	{
		if(mEVolyme > 0)
			mEVolyme--;
	}
	else if(mStatus == 1)
	{
		if(mMVolyme > 0)
			mMVolyme--;
	}
}