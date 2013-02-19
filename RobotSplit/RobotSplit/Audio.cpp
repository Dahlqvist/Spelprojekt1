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
			mEffectLeftArrow("LeftArrow", 1, 2),
			mEffectRightArrow("RightArrow", 1, 2),
			mEffectNumbers1("Numbers", 1, 20),
			mEffectNumbers10("Numbers", 1, 20),
			mEffectNumbers100("Numbers", 1, 20),
			mMusicVolyme("MusicVolym", 1, 2),
			mMusicLeftArrow("LeftArrow", 1, 2),
			mMusicRightArrow("RightArrow", 1, 2),
			mMusicNumbers1("Numbers", 1, 20),
			mMusicNumbers10("Numbers", 1, 20),
			mMusicNumbers100("Numbers", 1, 20),
			mEffectMute("EffectMute", 1, 4),
			mMusicMute("MusicMute", 1, 4),
			mBack("Back", 1, 2),
			mBlip("Blip", 1, 1),
			mWindow(Window::getWindow()),
			mStatus(0),
			mBlipPos(240, 150),
			currentBackground(&mMainBackground),
			currentSelection(&mBack),
			mEVolyme(100),
			mMVolyme(100),
			mChangeVolyme(false),
			mEffectNr1(0),
			mEffectNr10(0),
			mEffectNr100(1),
			mEffectHighlightNr(0),
			mMusicNr1(0),
			mMusicNr10(0),
			mMusicNr100(1),
			mMusicHighlightNr(0),
			mEMute(false),
			mMMute(false),
			mHighlight(1)

{	
	setSpritePosition();
	setAnimate();
}

void Audio::setSpritePosition()
{
	sf::Vector2f tempPos(mWindow.getSize().x/2-mMainBackground.getSprite().getGlobalBounds().width/2, 0);
	sf::Vector2f tempPos2(mWindow.getSize().x/2-mInGameBackground.getSprite().getGlobalBounds().width/2, 0);
	mMainBackground.setPosition(tempPos);
	mInGameBackground.setPosition(tempPos2);
	mEffectVolyme.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 150));

	mEffectLeftArrow.setPosition(sf::Vector2f(mEffectVolyme.getSprite().getPosition().x + mEffectVolyme.getSprite().getGlobalBounds().width + 24, tempPos.y + 150));
	mEffectNumbers100.setPosition(sf::Vector2f(mEffectLeftArrow.getSprite().getPosition().x + mEffectLeftArrow.getSprite().getGlobalBounds().width + 6, tempPos.y + 150));
	mEffectNumbers10.setPosition(sf::Vector2f(mEffectNumbers100.getSprite().getPosition().x + mEffectNumbers100.getSprite().getGlobalBounds().width + 6, tempPos.y + 150));
	mEffectNumbers1.setPosition(sf::Vector2f(mEffectNumbers10.getSprite().getPosition().x + mEffectNumbers10.getSprite().getGlobalBounds().width + 6, tempPos.y + 150));
	mEffectRightArrow.setPosition(sf::Vector2f(mEffectNumbers1.getSprite().getPosition().x + mEffectNumbers1.getSprite().getGlobalBounds().width + 6, tempPos.y + 150));

	mMusicVolyme.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 250));

	mMusicLeftArrow.setPosition(sf::Vector2f(mMusicVolyme.getSprite().getPosition().x + mMusicVolyme.getSprite().getGlobalBounds().width + 24, tempPos.y + 250));
	mMusicNumbers100.setPosition(sf::Vector2f(mMusicLeftArrow.getSprite().getPosition().x + mMusicLeftArrow.getSprite().getGlobalBounds().width + 6, tempPos.y + 250));
	mMusicNumbers10.setPosition(sf::Vector2f(mMusicNumbers100.getSprite().getPosition().x + mMusicNumbers100.getSprite().getGlobalBounds().width + 6, tempPos.y + 250));
	mMusicNumbers1.setPosition(sf::Vector2f(mMusicNumbers10.getSprite().getPosition().x + mMusicNumbers10.getSprite().getGlobalBounds().width + 6, tempPos.y + 250));
	mMusicRightArrow.setPosition(sf::Vector2f(mMusicNumbers1.getSprite().getPosition().x + mMusicNumbers1.getSprite().getGlobalBounds().width + 6, tempPos.y + 250));

	mEffectMute.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 350));
	mMusicMute.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 450));
	mBack.setPosition(sf::Vector2f(tempPos.x + 300, tempPos.y + 550));
	mBlipPos +=tempPos;
	mBlip.setPosition(mBlipPos);
}

void Audio::setAnimate()
{
	mEffectMute.setAnimate(false);
	mEffectVolyme.setAnimate(false);
	mEffectNumbers1.setAnimate(false);
	mEffectNumbers10.setAnimate(false);
	mEffectNumbers100.setAnimate(false);
	mEffectLeftArrow.setAnimate(false);
	mEffectRightArrow.setAnimate(false);
	mMusicMute.setAnimate(false);
	mMusicVolyme.setAnimate(false);
	mMusicNumbers1.setAnimate(false);
	mMusicNumbers10.setAnimate(false);
	mMusicNumbers100.setAnimate(false);
	mMusicLeftArrow.setAnimate(false);
	mMusicRightArrow.setAnimate(false);
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
		currentSelection = &mEffectMute;
	else if(mStatus == 3)
		currentSelection = &mMusicMute;
	else if(mStatus == 4)
		currentSelection = &mBack;

	if(mChangeVolyme)
		currentSelection ->setCurrentFrame(0);
	else	
		currentSelection ->setCurrentFrame(1);

	currentSelection ->update();
	
	updateNumbers();
	input();
}

void Audio::render()
{
	mWindow.clear(sf::Color::Black);
	mWindow.draw(currentBackground->getSprite());
	mWindow.draw(mEffectVolyme.getSprite());
	mWindow.draw(mMusicVolyme.getSprite());
	mWindow.draw(mEffectMute.getSprite());
	mWindow.draw(mMusicMute.getSprite());
	mWindow.draw(mEffectNumbers1.getSprite());
	mWindow.draw(mEffectNumbers10.getSprite());
	mWindow.draw(mEffectNumbers100.getSprite());
	mWindow.draw(mEffectLeftArrow.getSprite());
	mWindow.draw(mEffectRightArrow.getSprite());
	mWindow.draw(mMusicNumbers1.getSprite());
	mWindow.draw(mMusicNumbers10.getSprite());
	mWindow.draw(mMusicNumbers100.getSprite());
	mWindow.draw(mMusicLeftArrow.getSprite());
	mWindow.draw(mMusicRightArrow.getSprite());
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
		changeSelection(mChoices);
		select();
		volymeInput();
		MenuClock::restartClock();
	}
}

void Audio::changeSelection(int choices)
{
	int mChoices = choices;
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (mStatus < mChoices) && (!mChangeVolyme))
	{
		mBlipPos.y += 100;
		mBlip.setPosition(mBlipPos);
		mStatus++;
		currentSelection->setCurrentFrame(0);
		currentSelection->update();
	}
	else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (mStatus > 0 ) && (!mChangeVolyme))
	{			
		if(mStatus > 0)
			mBlipPos.y -= 100;
		mBlip.setPosition(mBlipPos);
			mStatus--;
		currentSelection->setCurrentFrame(0);
		currentSelection->update();
	}
}

void Audio::select()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		if(mStatus == 0)
		{
			mChangeVolyme = !mChangeVolyme;
			if(mChangeVolyme == true)
			{
				mEffectHighlightNr = 10;
				currentSelection ->setCurrentFrame(0);
				currentSelection ->update();
			}
			else
			{
				mEffectHighlightNr = 0;
				currentSelection ->setCurrentFrame(1);
				currentSelection ->update();
			}
			Sound::pauseSound("Lava");
			Sound::changeVolume(mEVolyme);
			Sound::playSound("Lava");
		}
		else if(mStatus == 1)
		{
			mChangeVolyme = !mChangeVolyme;
			if(mChangeVolyme == true)
			{
				mMusicHighlightNr = 10;
			}
			else
			{
				mMusicHighlightNr = 0;
			}
			Music::pauseMusic();
			Music::changeVolyme(mMVolyme);
			Music::playMusic();
		}
		else if(mStatus == 2)
		{
			mEMute = !mEMute;
			currentSelection ->setCurrentFrame(2);
			currentSelection ->update();
		}
		else if(mStatus == 3)
		{
			mMMute = !mMMute;
			currentSelection ->setCurrentFrame(2);
			currentSelection ->update();
		}
		else if(mStatus == 4)
			mStateInput.changeState("Last");
	}
}

void Audio::volymeInput()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && mChangeVolyme == true)
	{
		if(mStatus == 0)
			lowerNumbers(true);
		else if(mStatus == 1)
			lowerNumbers(false);
		lowerVolyme();		
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && mChangeVolyme == true)
	{
		if(mStatus == 0)
			raiseNumbers(true);
		else if(mStatus == 1)
			raiseNumbers(false);
		raiseVolyme();
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

void Audio::raiseNumbers(bool effect)
{
	if((effect == true) && (mEVolyme != 100))
	{
		mEffectNr1++;
		if(mEffectNr1 >= 10)
		{
			mEffectNr1 = 0;
			mEffectNr10++;
			if(mEffectNr10 >= 10)
			{
				mEffectNr10 = 0;
				mEffectNr100 = 1;
			}
		}
	}
	//Music
	else if((effect == false && mMVolyme != 100))
	{
		mMusicNr1++;
		if(mMusicNr1 >= 10)
		{
			mMusicNr1 = 0;
			mMusicNr10++;
			if(mMusicNr10 >= 10)
			{
				mMusicNr10 = 0;
				mMusicNr100 = 1;
			}
		}
	}
}

void Audio::lowerNumbers(bool effect)
{
	if((effect == true) && mEVolyme > 0)
	{
		mEffectNr1--;
		if(mEffectNr1 < 0)
		{
			mEffectNr1 = 9;
			mEffectNr10--;
			if(mEffectNr10 < 0)
			{
				mEffectNr10 = 9;
				mEffectNr100 = 0;
			}
		}	
	}
	else if((effect == false) && mMVolyme > 0)
	{
		mMusicNr1--;
		if(mMusicNr1 < 0)
		{
			mMusicNr1 = 9;
			mMusicNr10--;
			if(mMusicNr10 < 0)
			{
				mMusicNr10 = 9;
				mMusicNr100 = 0;
			}
		}	
	}
}

void Audio::updateNumbers()
{
	mEffectNumbers1.setCurrentFrame(mEffectNr1 + mEffectHighlightNr);
	mEffectNumbers1.update();
	
	mEffectNumbers10.setCurrentFrame(mEffectNr10 + mEffectHighlightNr);
	mEffectNumbers10.update();

	mEffectNumbers100.setCurrentFrame(mEffectNr100 + mEffectHighlightNr);
	mEffectNumbers100.update();

	mMusicNumbers1.setCurrentFrame(mMusicNr1 + mMusicHighlightNr);
	mMusicNumbers1.update();
	
	mMusicNumbers10.setCurrentFrame(mMusicNr10 + mMusicHighlightNr);
	mMusicNumbers10.update();

	mMusicNumbers100.setCurrentFrame(mMusicNr100 + mMusicHighlightNr);
	mMusicNumbers100.update();
}