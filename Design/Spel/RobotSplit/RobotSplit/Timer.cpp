#include "Timer.h"
#include "Window.h"
#include "TextureManager.h"

sf::Clock Timer::mClock;
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

int Timer::mTimeSave;

bool Timer::mShow;
bool Timer::mRun;

Animation* Timer::mNumbers;

Timer::Timer():
	timerPos(sf::Vector2f(1200, 20)),
	mDot(TextureManager::getSprite("Dot")),
	mColon(TextureManager::getSprite("Colon")),
	mFrame("TimeFrame", 1, 5)

{
	load();

	initialize();
	restartClock();

	mNumbers->setPosition(sf::Vector2f(Window::getWindow().getSize()));
	mNumbers->setAnimate(false);
	mFrame.setPosition(sf::Vector2f((timerPos.x - mFrame.getSprite().getGlobalBounds().width + 5), timerPos.y - 7));
	mFrame.setAnimate(false);
}

void Timer::load()
{
	mNumbers = new Animation("Numbers", 1, 20);
}

void Timer::initialize()
{
	mShow = true;
	mRun = false;

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

	mTimeSave = 0;
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
	mDec = (mTimeSave + mClock.getElapsedTime().asMilliseconds() / 100) % 10;
	mSek = (mTimeSave / 1000) + mClock.getElapsedTime().asSeconds();
	//mMin = (mTimeSave /1000) + mClock.getElapsedTime().asSeconds() / 60;
	//mHour = (mTimeSave / 1000) + mClock.getElapsedTime().asSeconds() / 3600;
	mMin = mSek / 60;
	mHour = mSek / 3600;

	m1Sek = mSek % 10;
	m10Sek = (mSek / 10) % 6;
	m1Min = mMin % 10;
	m10Min = (mMin / 10) % 6;
	m1Hour = mHour % 10;
	m10Hour = (mHour / 10) % 10;

	timerPos = sf::Vector2f(1200, 20);
	if(mShow)
	{
		Window::getWindow().draw(mFrame.getSprite());
		if(mRun)
		{
			mFrame.setCurrentFrame(4);
			//tiondels sekunder
			updateNumbers(mDec);
			setDot();

			//ental sekunder
			updateNumbers(m1Sek);
	
			//tiotal sekunder
			updateNumbers(m10Sek);
			if(m1Min >= 1)
			{
				mFrame.setCurrentFrame(3);
				setColon();

				//ental minuter
				updateNumbers(m1Min);
				if(m10Min >= 1)
				{
					mFrame.setCurrentFrame(2);
					//tiotal minuter
					updateNumbers(m10Min);
					if(m1Hour >= 1)
					{
						mFrame.setCurrentFrame(1);
						setColon();

						//ental timmar
						updateNumbers(m1Hour);

						if(m10Hour >=1)
						{
							mFrame.setCurrentFrame(0);
							//tiotal timmar
							updateNumbers(m10Hour);
						}
					}
				}
			}
		}
		else
		{
			mFrame.setCurrentFrame(4);
			updateNumbers(0);
			setDot();
			updateNumbers(0);
			updateNumbers(0);
		}
		mFrame.update();
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

void Timer::start()
{
	mRun = true;
	restartClock();
	mTimeSave = 0;
}

void Timer::stop()
{
	mRun = false;
	//restartClock();
}

void Timer::pause()
{
	mTimeSave += mClock.getElapsedTime().asMilliseconds();
}

//float Timer::getSaveTime()
//{
//	return mTimeSave;
//}