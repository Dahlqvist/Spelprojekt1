#include "Timer.h"
#include "Window.h"
#include "TextureManager.h"

sf::Clock Timer::mClock;
sf::Clock Timer::mSecondClock;
int Timer::mDec;
int Timer::mSek;
int Timer::mMin;
int Timer::mHour;

int Timer::m1Sek;
int Timer::m10Sek;
int Timer::m1Min;
int Timer::m10Min;
int Timer::m1Hour;
int Timer::m10Hour;

bool Timer::mShow;

Animation* Timer::mNumbers;

Timer::Timer():
	timerPos(sf::Vector2f(1200, 20)),
	mDot(TextureManager::getSprite("Dot")),
	mColon(TextureManager::getSprite("Colon"))

{
	load();

	initialize();
	restartClock();

	mNumbers->setPosition(sf::Vector2f(Window::getWindow().getSize()));
	mNumbers->setAnimate(false);
}

void Timer::load()
{
	mNumbers = new Animation("Numbers", 1, 20);
}

void Timer::initialize()
{
	mShow = true;

	mDec = 0;
	mSek = 0;
	mMin = 0;
	mHour = 0;

	m1Sek = 0;
	m10Sek = 0;
	m1Min = 0;
	m10Min = 0;
	m1Hour = 0;
	m10Hour = 0;
}

Timer::~Timer()
{
	delete mNumbers;
}

//Timer& Timer::getInstance()
//{
//	Timer temp;
//	return temp;
//}

sf::Clock& Timer::getClock()
{
	return mClock;
}

void Timer::restartClock()
{
	mSecondClock.restart();
	mClock.restart();
}

void Timer::input()
{
	if(Window::getEvent().type == sf::Event::KeyPressed && Window::getEvent().key.code == sf::Keyboard::G)
	{
		initialize();
		restartClock();
	}
}

void Timer::update()
{
	//För att få fram vilken bild som skall visas
	mDec = (mClock.getElapsedTime().asMilliseconds() / 100) % 10;
	mSek = mClock.getElapsedTime().asSeconds();
	mMin = mClock.getElapsedTime().asSeconds() / 60;
	mHour = mClock.getElapsedTime().asSeconds() / 3600;

	m1Sek = mSek % 10;
	m10Sek = (mSek / 10) % 6;
	m1Min = mMin % 10;
	m10Min = (mMin / 10) % 6;
	m1Hour = mHour % 10;
	m10Hour = (mHour / 10) % 10;

	timerPos = sf::Vector2f(1200, 20);
	if(mShow)
	{
		//tiondels sekunder
		updateNumbers(mDec);
		setDot();

		//ental sekunder
		updateNumbers(m1Sek);
	
		//tiotal sekunder
		updateNumbers(m10Sek);
		if(m1Min >= 1)
		{
			setColon();

			//ental minuter
			updateNumbers(m1Min);
			if(m10Min >= 1)
			{

				//tiotal minuter
				updateNumbers(m10Min);
				if(m1Hour >= 1)
				{
					setColon();

					//ental timmar
					updateNumbers(m1Hour);

					if(m10Hour >=1)
					//tiotal timmar
					updateNumbers(m10Hour);
				}
			}
		}
	}
}

void Timer::render()
{
	Window::getWindow().display();
}

void Timer::updateNumbers(int q)
{
	timerPos.x = timerPos.x - (10 + mNumbers->getSprite().getGlobalBounds().width);
	mNumbers->setCurrentFrame(q);
	mNumbers->setPosition(timerPos);
	mNumbers->update();
	Window::getWindow().draw(mNumbers->getSprite());
}

void Timer::setDot()
{
	sf::Vector2f dotPos;
	dotPos.x = (timerPos.x - (5 + mDot.getGlobalBounds().width));
	dotPos.y = (timerPos.y + (mNumbers->getSprite().getGlobalBounds().height - mDot.getGlobalBounds().height));
	timerPos.x = timerPos.x - 5;
	mDot.setPosition(dotPos);
	Window::getWindow().draw(mDot);
}

void Timer::setColon()
{
	sf::Vector2f colonPos;
	colonPos.x = (timerPos.x - (5 + mColon.getGlobalBounds().width));
	colonPos.y = (timerPos.y + ((mNumbers->getSprite().getGlobalBounds().height / 2) - (mColon.getGlobalBounds().height / 2)));
	timerPos.x = timerPos.x - 5;
	mColon.setPosition(colonPos);
	Window::getWindow().draw(mColon);
}

void Timer::changeStatus()
{
	mShow = !mShow;
}

bool Timer::getStatus()
{
	return mShow;
}