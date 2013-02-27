#include "Timer.h"
#include <iostream>
#include "Window.h"

sf::Clock Timer::mClock;
sf::Clock Timer::mSecondClock;
Animation* Timer::currentNr;
int Timer::mDec;
int Timer::mSek;
int Timer::mMin;
int Timer::mHour;

Timer::Timer():
	mNumbers("Numbers", 1, 9)
{
	currentNr = &mNumbers;
	mDec = 0;
	mSek = 0;
	mMin = 0;
	mHour = 0;
	restartClock();
}

Timer::~Timer()
{}

Timer& Timer::getInstance()
{
	Timer Timer;
	return Timer;
}

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
		mDec = 0;
		mSek = 0;
		mMin = 0;
		mHour = 0;
		restartClock();
	}
}

void Timer::update()
{
	//För att få fram vilken bild som skall visas
	mDec = mClock.getElapsedTime().asMilliseconds() / 100;
	if(mDec >= 10)
	{
		mDec = 0;
		mClock.restart();
		mSek++;
		if(mSek > 59)
		{
			mSek = 0;
			mMin++;
			if(mMin > 59)
			{
				mMin = 0;
				mHour++;
			}
		}
	}
}

void Timer::render()
{
	for(int i=0; i<16; i++)
	{
		std::cout << std::endl;
	}
	std::cout << "Bild tid" << std::endl;
	std::cout << "Dec: " << mDec << std::endl;
	std::cout << "Sek: " << mSek << std::endl;
	std::cout << "Min: " << mMin << std::endl;
	std::cout << "Hour: " << mHour << std::endl;
	std::cout << "SecondClock: " << std::endl;
	std::cout << "Dec: " << mSecondClock.getElapsedTime().asMilliseconds() / 100 << std::endl;
	std::cout << "Sek: " << mSecondClock.getElapsedTime().asSeconds() << std::endl;
	std::cout << "Min: " << mSecondClock.getElapsedTime().asSeconds() / 60 << std::endl;
	std::cout << "Hour: " << mSecondClock.getElapsedTime().asSeconds() / 3600 << std::endl;

}